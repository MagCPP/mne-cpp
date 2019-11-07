#include "tmsneurofeedback.h"

using namespace SCSHAREDLIB;
using namespace SCMEASLIB;
using namespace IOBUFFER;

// Constructor and Destructor

TmsNeurofeedback::TmsNeurofeedback()
    : m_bIsRunning(false)
    , m_pExampleInput(NULL)
    , m_pExampleOutput(NULL)
    , m_pExampleBuffer(CircularMatrixBuffer<double>::SPtr())
{
    QAction* showCheckWidgetAction = new QAction(QIcon(":/grafics/images/Control.png"), tr("Toolbar Widget"), this);  // C:/Users/opper/Desktop/Control.png
    showCheckWidgetAction->setShortcut(tr("F12"));
    showCheckWidgetAction->setStatusTip(tr("Check Window"));
    addPluginAction(showCheckWidgetAction);
    connect(showCheckWidgetAction, &QAction::triggered, this, &TmsNeurofeedback::showCheck);
}
TmsNeurofeedback::~TmsNeurofeedback() {}

// Init, clone, unload
void TmsNeurofeedback::init() {
    m_pExampleInput = PluginInputData<RealTimeMultiSampleArray>::create(this,"ExampleInput", "Example Plugin's input data");
    m_inputConnectors.append(m_pExampleInput);

    m_pExampleOutput = PluginOutputData<RealTimeMultiSampleArray>::create(this, "ExampleOutput", "Example Plugin's output data");
    m_outputConnectors.append(m_pExampleOutput);

    connect(m_pExampleInput.data(), &PluginInputConnector::notify, this, &TmsNeurofeedback::update, Qt::DirectConnection);

}
void TmsNeurofeedback::unload(){}

QSharedPointer<IPlugin> TmsNeurofeedback::clone() const
{
    QSharedPointer<TmsNeurofeedback> pointerToTmsNeurofeedback(new TmsNeurofeedback);
    return pointerToTmsNeurofeedback;
}

// start, stop, run
bool TmsNeurofeedback::start() {return true;}
bool TmsNeurofeedback::stop() {return true;}
void TmsNeurofeedback::run() {}

void TmsNeurofeedback::update(SCMEASLIB::Measurement::SPtr pMeasurement) {
    printf("update/n");
}

// 'const' means that this function won't modify the object
// Ctrl + Click in PLuginType to see a list of options
IPlugin::PluginType TmsNeurofeedback::getType() const
{
    return _IAlgorithm;
}

QString TmsNeurofeedback::getName() const
{
    return "TmsNeurofeedback Plugin";
}

QWidget* TmsNeurofeedback::setupWidget()
{
    TMSGui* setupWidget = new TMSGui();
    return setupWidget;
}

void TmsNeurofeedback::showCheck()
{
    CheckWidget* checkWidget = new CheckWidget();
    checkWidget->show();
}


