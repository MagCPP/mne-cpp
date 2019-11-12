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

    m_pExampleOutput = PluginOutputData<RealTimeMultiSampleArray>::create(this, "ExampleOut", "Example Plugin's output data");
    m_outputConnectors.append(m_pExampleOutput);

    connect(m_pExampleInput.data(), &PluginInputConnector::notify, this, &ExampleSignal::update, Qt::DirectConnection);

    //Delete Buffer - will be initailzed with first incoming data
    if(!m_pExampleBuffer.isNull())
        m_pExampleBuffer = CircularMatrixBuffer<double>::SPtr();
}

QSharedPointer<IPlugin> ExampleSignal::clone() const
{
    QSharedPointer<ExampleSignal> pointerToExampleSignal(new ExampleSignal);
    return pointerToExampleSignal;
}

void ExampleSignal::unload() {}

// start, stop, run
bool ExampleSignal::start()
{
    this->m_bIsRunning = true;
    QThread::start();
    return true;
}
bool ExampleSignal::stop()
{
    m_bIsRunning = false;
    m_pExampleBuffer->releaseFromPop();
    m_pExampleBuffer->releaseFromPush();
    m_pExampleBuffer->clear();
    return true;
}

void ExampleSignal::run()
{
    //
    // Wait for Fiff Info
    //


    while(!m_pFiffInfo)
        msleep(10);// Wait for fiff Info


    while(m_bIsRunning)
    {
        //Dispatch the inputs
        MatrixXd t_mat = m_pExampleBuffer->pop();

        //ToDo: Implement your algorithm here
        double a = t_mat(316,0);
        double limit = 0.00006;
        double t_matnew;
        // EEG values from fiff Simulator -> changed in Values between 0 and 1
        if(a < limit) {
            t_matnew = 0;
        }
        else {
            t_matnew = a * 10000;
            if(t_matnew > 1.00) {
                t_matnew = 1;
            }
        }
        t_mat(0,0) = t_matnew;
        printf("%fd", t_matnew);

        //Send the data to the connected plugins and the online display
        //Unocmment this if you also uncommented the m_pDummyOutput in the constructor above
        m_pExampleOutput->data()->setValue(t_mat);
    }
}

void ExampleSignal::update(Measurement::SPtr pMeasurement)
{

    QSharedPointer<RealTimeMultiSampleArray> pRTMSA = pMeasurement.dynamicCast<RealTimeMultiSampleArray>();

        if(pRTMSA) {
            //Check if buffer initialized
            if(!m_pExampleBuffer) {
                m_pExampleBuffer = CircularMatrixBuffer<double>::SPtr(new CircularMatrixBuffer<double>(64, pRTMSA->getNumChannels(), pRTMSA->getMultiSampleArray()[0].cols()));
            }

            //Fiff information
            if(!m_pFiffInfo) {
                m_pFiffInfo = pRTMSA->info();

                //Init output - Unocmment this if you also uncommented the m_pDummyOutput in the constructor above
                m_pExampleOutput->data()->initFromFiffInfo(m_pFiffInfo);
                m_pExampleOutput->data()->setMultiArraySize(1);
                m_pExampleOutput->data()->setVisibility(true);
            }

            MatrixXd t_mat;

            for(unsigned char i = 0; i < pRTMSA->getMultiArraySize(); ++i) {
                t_mat = pRTMSA->getMultiSampleArray()[i];
                m_pExampleBuffer->push(&t_mat);
            }
        }
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

