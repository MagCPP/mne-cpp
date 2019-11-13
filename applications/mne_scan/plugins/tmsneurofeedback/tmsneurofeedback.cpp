#include "tmsneurofeedback.h"

using namespace SCSHAREDLIB;
using namespace SCMEASLIB;
using namespace IOBUFFER;

// Constructor and Destructor

TmsNeurofeedback::TmsNeurofeedback()
    : m_bIsRunning(false)
    , m_pSignalInput(NULL)
    , m_pExampleBuffer(CircularMatrixBuffer<double>::SPtr())
    , m_pMyRapid(new Rapid("COM1"))
    , m_pTMSGui (new TMSGui())
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
    m_pMyRapid->disconnect(m_pError);
    delete m_pMyRapid;
}

//*************************************************************************************************************

void TmsNeurofeedback::init() {
    // Add an input
    m_pSignalInput = PluginInputData<RealTimeMultiSampleArray>::create(this, "SignalInput", "TMSNFPlugin's input data");
    m_inputConnectors.append(m_pSignalInput);

    m_pSignalOutput = PluginOutputData<RealTimeMultiSampleArray>::create(this, "SignalOutput", "TMSNFPlugin's output data");
    m_outputConnectors.append(m_pSignalOutput);

    // Register for updates - inputData = outputData
    connect(m_pSignalInput.data(), &PluginInputConnector::notify, this, &TmsNeurofeedback::update, Qt::DirectConnection);

    //Delete Buffer - will be initailzed with first incoming data
    if(!m_pExampleBuffer.isNull())
        m_pExampleBuffer = CircularMatrixBuffer<double>::SPtr();
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
    m_bIsRunning = true;
    QThread::start();

    getParametersFromGUI();

    return true;
}

//*************************************************************************************************************

bool TmsNeurofeedback::stop()
{
    // Make the run loop exit by setting isRunning to False
    m_bIsRunning = false;

    m_pExampleBuffer->releaseFromPop();
    m_pExampleBuffer->releaseFromPush();
    m_pExampleBuffer->clear();

    // Disconnect from Rapid
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
    while(!m_pFiffInfo)
        msleep(10);// Wait for fiff Info

    // Initialise
    double TimeNextShotPossible = clock();
    m_pError = 0;
    bool fire = false;
    int newPower = 0;
    // Prepare Rapid
    m_pMyRapid = new Rapid(m_pPort,m_pSuperRapid, m_pUnlockCode, m_pVoltage, std::make_tuple(7,2,0));
    m_pMyRapid->connect(m_pError);
    // get current Power
    std::map<QString, std::map<QString, double>> settings;
    settings = m_pMyRapid->getParameters(m_pError);
    m_pCurrentPower = settings["rapidParam"]["power"];
    // get ready
    m_pMyRapid->arm(false, m_pParams, m_pError);
    m_pMyRapid->ignoreCoilSafetySwitch(m_pError);

    while (true) {
        {
            // Check if still active
            QMutexLocker locker(&m_qMutex);
            if (!m_bIsRunning)
                break;
        }
        //TODO visual NF

        // Check for Fire Command
        // StaticPower: everything about 0 is meant to Fire
        // DynamicPower: change Power between [0; 1] in scale to [0%; 100%]
        MatrixXd t_mat = m_pExampleBuffer->pop();
        if ( t_mat(0,0) > 0 ) {
            fire = true;
            newPower = int(t_mat(0,0)*100);
        }

        // In case of dynamic power and a changed setting, change power
        if (!m_pStaticPower & (newPower != m_pCurrentPower)) {
            m_pMyRapid->disarm(m_pParams,m_pError);
            m_pMyRapid->setPower(newPower,true, m_pParams, m_pError);
            m_pMyRapid->arm(false, m_pParams, m_pError);
            m_pMyRapid->ignoreCoilSafetySwitch(m_pError);
            m_pCurrentPower = newPower;
            // just in case, dont know if needed
            m_pMyRapid->resetQuickFire();
        }

        // Fire
        if (fire) {
            fire = false;
            // Fire only if not in Deadtime after the last shot
            if (TimeNextShotPossible < clock()) {
                printf("~~~ Fire in the hole! ~~~\n");
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

    QSharedPointer<RealTimeMultiSampleArray> pRTMSA = pMeasurement.dynamicCast<RealTimeMultiSampleArray>();

    if(pRTMSA) {
        //Check if buffer initialized
        if(!m_pExampleBuffer) {
            m_pExampleBuffer = CircularMatrixBuffer<double>::SPtr(new CircularMatrixBuffer<double>(64, pRTMSA->getNumChannels(), pRTMSA->getMultiSampleArray()[0].cols()));
        }

        //Fiff information
        if(!m_pFiffInfo) {
            m_pFiffInfo = pRTMSA->info();

//            //Init output - Unocmment this if you also uncommented the m_pDummyOutput in the constructor above
//            m_pSignalOutput->data()->initFromFiffInfo(m_pFiffInfo);
//            m_pSignalOutput->data()->setMultiArraySize(1);
//            m_pSignalOutput->data()->setVisibility(true);
        }

        MatrixXd t_mat;

        for(unsigned char i = 0; i < pRTMSA->getMultiArraySize(); ++i) {
            t_mat = pRTMSA->getMultiSampleArray()[i];
            m_pExampleBuffer->push(&t_mat);
        }
    }
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
//    TMSGui* setupWidget = new TMSGui();
//    return setupWidget;
    m_pTMSGui = new TMSGui();
    return m_pTMSGui;
}

int TmsNeurofeedback::connectionPossible()
{
    getParametersFromGUI();
    int error = 0;
    int error2 = 0;
    // Prepare Rapid
    m_pMyRapid = new Rapid(m_pPort,m_pSuperRapid, m_pUnlockCode, m_pVoltage, std::make_tuple(7,2,0));
    m_pMyRapid->connect(error);
    m_pMyRapid->disconnect(error2);

    return error;
}

//*************************************************************************************************************

void TmsNeurofeedback::getParametersFromGUI()
{
    m_pUnlockCode           = m_pTMSGui->getUnlockCode();
    m_pPort                 = m_pTMSGui->getPort();
    m_pVoltage              = m_pTMSGui->getVoltage();
    m_pSuperRapid           = m_pTMSGui->getSuperRapid();
    // Fire settings
    m_pStaticPower          = m_pTMSGui->getStaticPower();
    m_pCurrentPower         = 30;
    m_pPulses               = m_pTMSGui->getPulses();
    m_pDeadTime             = m_pTMSGui->getDeadTime();
    m_pFrequency            = m_pTMSGui->getFrequency();
    // Visual settings
    m_pPosImage             = m_pTMSGui->getPosImage();
    m_pNeutImage            = m_pTMSGui->getNeutImage();
    m_pNegImage             = m_pTMSGui->getNegImage();
    m_pPosImagePath         = m_pTMSGui->getPosImagePath();
    m_pNeutImagePath        = m_pTMSGui->getNeutImagePath();
    m_pNegImagePath         = m_pTMSGui->getNegImagePath();
    m_pPosImageHighTresh    = m_pTMSGui->getPosImageHighTresh();
    m_pPosImageLowTresh     = m_pTMSGui->getPosImageLowTresh();
    m_pNeutImageHighTresh   = m_pTMSGui->getNeutImageHighTresh();
    m_pNeutImageLowTresh    = m_pTMSGui->getNeutImageLowTresh();
    m_pNegImageHighTresh    = m_pTMSGui->getNegImageHighTresh();
    m_pNegImageLowTresh     = m_pTMSGui->getNegImageLowTresh();
}

//*************************************************************************************************************

void TmsNeurofeedback::showCheck()
{
    CheckWidget* checkWidget = new CheckWidget(m_pMyRapid);
    checkWidget->show();
}


