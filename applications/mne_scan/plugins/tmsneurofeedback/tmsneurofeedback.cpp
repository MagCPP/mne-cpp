#include "tmsneurofeedback.h"

using namespace SCSHAREDLIB;
using namespace SCMEASLIB;
using namespace IOBUFFER;

// Constructor and Destructor

TmsNeurofeedback::TmsNeurofeedback()
    : m_bIsRunning(false)
    , m_pSignalInput(NULL)
    , m_pExampleBuffer(CircularMatrixBuffer<double>::SPtr())    // TODO: change because of numeric?!
    , m_pmyRapid(new Rapid("COM1"))
{
    QAction* showCheckWidgetAction = new QAction(QIcon(":/grafics/images/Control.png"), tr("Toolbar Widget"), this);  // C:/Users/opper/Desktop/Control.png
    showCheckWidgetAction->setShortcut(tr("F12"));
    showCheckWidgetAction->setStatusTip(tr("Check Window"));
    addPluginAction(showCheckWidgetAction);
    connect(showCheckWidgetAction, &QAction::triggered, this, &TmsNeurofeedback::showCheck);
}

//*************************************************************************************************************

TmsNeurofeedback::~TmsNeurofeedback()
{
    if(this->isRunning())
        stop();
}

//*************************************************************************************************************

void TmsNeurofeedback::init() {
    // Add an input
    m_pSignalInput = PluginInputData<Numeric>::create(this, "SignalInput", "TMSNFPlugin's input data");
    m_inputConnectors.append(m_pSignalInput);

    // Register for updates
//    connect(m_pSignalInput.data(), &PluginInputConnector::notify, this, &TmsNeurofeedback::update, Qt::DirectConnection);

}

//*************************************************************************************************************

void TmsNeurofeedback::unload()
{

}

//*************************************************************************************************************

QSharedPointer<IPlugin> TmsNeurofeedback::clone() const
{
    QSharedPointer<TmsNeurofeedback> pointerToTmsNeurofeedback(new TmsNeurofeedback);
    return pointerToTmsNeurofeedback;
}

//*************************************************************************************************************

bool TmsNeurofeedback::start()
{
    m_pError = 0;
    m_pMyRapid = new Rapid(m_pPort,m_pSuperRapid, m_pUnlockCode, m_pVoltage, std::make_tuple(7,2,0));
    m_pMyRapid->connect(m_pError);
    m_pMyRapid->arm(false, m_pParams, m_pError);
    m_pMyRapid->ignoreCoilSafetySwitch(m_pError);
    if (m_pError)
        return false;
    else
        return true;
}

//*************************************************************************************************************

bool TmsNeurofeedback::stop()
{
    m_pError = 0;
    m_pMyRapid->disconnect(m_pError);
    if (m_pError)
        return false;
    else
        return true;
}

//*************************************************************************************************************

void TmsNeurofeedback::run()
{
    // Be ready to start directly
    double TimeNextShotPossible = clock();
    m_pError = 0;

    while (true) {
        {
            // Check if still active
            QMutexLocker locker(&m_qMutex);
            if (!m_bIsRunning)
                break;

            // Check for Fire Command
            // StaticPower: everything about 0 is meant to Fire
            // DynamicPower: change Power between [0; 1] in scale to [0%; 100%]
            bool fire = false; // TODO
            int newPower = 30; // TODO

            // In case of dynamic power and a changed setting, change power
            if (!m_pStaticPower & (newPower != m_pCurrentPower)) {
                m_pMyRapid->disarm(m_pParams,m_pError);
                m_pMyRapid->setPower(newPower,true, m_pParams, m_pError);
                m_pMyRapid->arm(false, m_pParams, m_pError);
                m_pMyRapid->ignoreCoilSafetySwitch(m_pError);
                // just in case, dont know if needed
                m_pMyRapid->resetQuickFire();
            }

            // Fire if not in DeadTime after last Shot
            if (fire & (TimeNextShotPossible < clock())) {
                TimeNextShotPossible = clock() + m_pDeadTime * CLOCKS_PER_SEC;
                for (int shots = 1; shots <= m_pPulses; ++shots) {
                    m_pMyRapid->quickFire(m_pError);
                    m_pMyRapid->resetQuickFire();
                    double sleep = 1 / m_pFrequency;
                    QThread::msleep(sleep * 1000);
                }
            }
        }

    }
}

//*************************************************************************************************************

void TmsNeurofeedback::update(SCMEASLIB::Measurement::SPtr pMeasurement) {
    printf("###############################update/n");
}

//*************************************************************************************************************

// 'const' means that this function won't modify the object
// Ctrl + Click in PLuginType to see a list of options
IPlugin::PluginType TmsNeurofeedback::getType() const
{
    return _IAlgorithm;
}

//*************************************************************************************************************

QString TmsNeurofeedback::getName() const
{
    return "TmsNeurofeedback Plugin";
}

//*************************************************************************************************************

QWidget* TmsNeurofeedback::setupWidget()
{
    TMSGui* setupWidget = new TMSGui();
    return setupWidget;
}

//*************************************************************************************************************

void TmsNeurofeedback::showCheck()
{
    CheckWidget* checkWidget = new CheckWidget();
    checkWidget->show();
}


