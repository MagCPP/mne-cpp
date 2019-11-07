#ifndef TMSNEUROFEEDBACK_H
#define TMSNEUROFEEDBACK_H

#include "tmsneurofeedback_global.h"
#include "FormFiles/tmsgui.h"
#include "FormFiles/checkwidget.h"
#include "FormFiles/visualnf.h"

#include <scShared/Interfaces/IAlgorithm.h>
#include <scShared/Interfaces/ISensor.h>

#include <scMeas/realtimemultisamplearray.h>
#include <utils/generics/circularmatrixbuffer.h>

using namespace SCSHAREDLIB;

class TMSNEUROFEEDBACKSHARED_EXPORT TmsNeurofeedback : public SCSHAREDLIB::IAlgorithm
{

    Q_OBJECT

    Q_PLUGIN_METADATA(IID "scsharedllib/1.0" FILE "tmsneurofeedback.json")

    Q_INTERFACES(SCSHAREDLIB::IAlgorithm)

public:
    TmsNeurofeedback();
    ~TmsNeurofeedback();

    // IAlgorithm functions
    virtual QSharedPointer<IPlugin> clone() const;
    virtual void init();
    virtual void unload();
    virtual bool start();
    virtual bool stop();
    virtual IPlugin::PluginType getType() const;
    virtual QString getName() const;
    virtual QWidget* setupWidget();
    void showParamSet();


    void update(SCMEASLIB::Measurement::SPtr pMeasurement);
protected:
    virtual void run();
    void showCheck();
    //void showParamSet();

private:
    FIFFLIB::FiffInfo::SPtr m_pFiffInfo;

    PluginInputData<SCMEASLIB::RealTimeMultiSampleArray>::SPtr m_pExampleInput;

    PluginOutputData<SCMEASLIB::RealTimeMultiSampleArray>::SPtr m_pExampleOutput;

    IOBUFFER::CircularMatrixBuffer<double>::SPtr m_pExampleBuffer;

    bool m_bIsRunning;

};

#endif // TMSNEUROFEEDBACK_H
