#ifndef TMSNEUROFEEDBACK_H
#define TMSNEUROFEEDBACK_H

#include "tmsneurofeedback_global.h"
#include "FormFiles/tmsgui.h"
#include "FormFiles/checkwidget.h"
#include "FormFiles/visualnf.h"

#include <scShared/Interfaces/IAlgorithm.h>

#include <scMeas/realtimemultisamplearray.h>
#include <utils/generics/circularmatrixbuffer.h>
#include <scMeas/numeric.h>

#include <magcpp/devices/magstim.h>
#include <magcpp/devices/rapid.h>

#include <ctime>

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

    int connectionPossible();


    void getParametersFromGUI();

    void update(SCMEASLIB::Measurement::SPtr pMeasurement);
protected:
    virtual void run();
    void showCheck();
    //void showParamSet();

private:
    FIFFLIB::FiffInfo::SPtr m_pFiffInfo;

    PluginInputData<SCMEASLIB::RealTimeMultiSampleArray>::SPtr m_pSignalInput;
    PluginOutputData<SCMEASLIB::RealTimeMultiSampleArray>::SPtr m_pSignalOutput;

    IOBUFFER::CircularMatrixBuffer<double>::SPtr m_pExampleBuffer;

    bool m_bIsRunning;

    QMutex m_qMutex;
    TMSGui *m_pTMSGui;
    // Default Parameters for Rapid Functions
    std::map<QString, std::map<QString, double>> m_pParams;
    int m_pError;
    // Rapid Settings
    Rapid *m_pMyRapid;
    QString m_pUnlockCode;
    QString m_pPort;
    int m_pVoltage;
    int m_pSuperRapid;
    // Fire settings
    bool m_pStaticPower;
    int m_pCurrentPower;
    int m_pPulses;
    double m_pDeadTime;
    int m_pFrequency;
    // Visual settings
    bool m_pPosImage;
    bool m_pNeutImage;
    bool m_pNegImage;
    QString m_pPosImagePath;
    QString m_pNeutImagePath;
    QString m_pNegImagePath;
    double m_pPosImageHighTresh;
    double m_pPosImageLowTresh;
    double m_pNeutImageHighTresh;
    double m_pNeutImageLowTresh;
    double m_pNegImageHighTresh;
    double m_pNegImageLowTresh;


};

#endif // TMSNEUROFEEDBACK_H
