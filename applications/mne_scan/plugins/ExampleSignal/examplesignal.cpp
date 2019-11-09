#include "examplesignal.h"

using namespace SCSHAREDLIB;
using namespace SCMEASLIB;
using namespace IOBUFFER;

// Constructor and destructor
ExampleSignal::ExampleSignal()
    : m_bIsRunning(false)
    , m_pExampleInput(NULL)
    , m_pExampleOutput(NULL)
    , m_pExampleBuffer(CircularMatrixBuffer<double>::SPtr())
{

}

ExampleSignal::~ExampleSignal() {}

// Init, clone, unload
void ExampleSignal::init() {

    m_pExampleInput = PluginInputData<RealTimeMultiSampleArray>::create(this, "ExampleInput", "Example Plugins's input data");
    m_inputConnectors.append(m_pExampleInput);

    m_pExampleOutput = PluginOutputData<Numeric>::create(this, "ExampleOut", "Example Plugin's output data");
    m_outputConnectors.append(m_pExampleOutput);

    connect(m_pExampleInput.data(), &PluginInputConnector::notify, this, &ExampleSignal::update, Qt::DirectConnection);

}
void ExampleSignal::unload() {}

QSharedPointer<IPlugin> ExampleSignal::clone() const
{
    QSharedPointer<ExampleSignal> pointerToExampleSignal(new ExampleSignal);
    return pointerToExampleSignal;
}

// start, stop, run
bool ExampleSignal::start() {return true;}
bool ExampleSignal::stop() {return true;}
void ExampleSignal::run() {}

void ExampleSignal::update(Measurement::SPtr pMeasurement)
{

}
// 'const' means that this function won't modify the object
// Ctrl - Click on PLuginType to see a list of options
IPlugin::PluginType ExampleSignal::getType() const
{
    return _ISensor;
}

QString ExampleSignal::getName() const
{
    return "Example Signal";
}

QWidget* ExampleSignal::setupWidget()
{
    // Placeholder. This is where the UI will be setup later
    QWidget* setupWidget = new QWidget();
    return setupWidget;
}

