#ifndef EXAMPLESIGNAL_H
#define EXAMPLESIGNAL_H

#include "examplesignal_global.h"

#include <scShared/Interfaces/ISensor.h>

#include <scMeas/numeric.h>
#include <scMeas/realtimemultisamplearray.h>
#include <utils/generics/circularmatrixbuffer.h>

using namespace SCSHAREDLIB;

class EXAMPLESIGNALSHARED_EXPORT ExampleSignal : public SCSHAREDLIB::ISensor
{

    Q_OBJECT

    Q_PLUGIN_METADATA(IID "scsharedlib/1.0" FILE "examplesignal.json")

    Q_INTERFACES(SCSHAREDLIB::ISensor)


public:
    ExampleSignal();
    ~ExampleSignal();

    virtual QSharedPointer<IPlugin> clone() const;
    virtual void init();
    virtual void unload();
    virtual bool start();
    virtual bool stop();
    virtual PluginType getType() const;
    virtual QString getName() const;
  //  virtual inline bool multiInstanceAllowed() const;
    virtual QWidget* setupWidget();

    void update(SCMEASLIB::Measurement::SPtr pMeasurement);

protected:
    virtual void run();
    void showSettings();

private:
    FIFFLIB::FiffInfo::SPtr m_pFiffInfo;

    PluginInputData<SCMEASLIB::RealTimeMultiSampleArray>::SPtr m_pExampleInput;

    PluginOutputData<SCMEASLIB::RealTimeMultiSampleArray>::SPtr m_pExampleOutput;

    IOBUFFER::CircularMatrixBuffer<double>::SPtr m_pExampleBuffer;

    bool m_bIsRunning;


};

#endif // EXAMPLESIGNAL_H
