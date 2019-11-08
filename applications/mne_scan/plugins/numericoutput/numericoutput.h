//=============================================================================================================
/**
* @file     numericoutput.h
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     February, 2013
*
* @section  LICENSE
*
* Copyright (C) 2013, Christoph Dinh and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of MNE-CPP authors nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    Contains the declaration of the NumericOutput class.
*
*/

#ifndef NUMERICOUTPUT_H
#define NUMERICOUTPUT_H


//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "numericoutput_global.h"

#include <scShared/Interfaces/IAlgorithm.h>
#include <utils/generics/circularmatrixbuffer.h>
#include <scMeas/realtimemultisamplearray.h>
#include "FormFiles/numericsetupwidget.h"
#include "FormFiles/numericyourwidget.h"
#include <scMeas/numeric.h>


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QtWidgets>
#include <QtCore/QtPlugin>
#include <QDebug>


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE NumericOutputPlugin
//=============================================================================================================

namespace NUMERICOUTPUTPLUGIN
{


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace SCSHAREDLIB;


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================


//=============================================================================================================
/**
* DECLARE CLASS NumericOutput
*
* @brief The NumericOutput class provides a numeric algorithm structure.
*/
class NUMERICOUTPUTSHARED_EXPORT NumericOutput : public IAlgorithm
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "scsharedlib/1.0" FILE "numericoutput.json") //New Qt5 Plugin system replaces Q_EXPORT_PLUGIN2 macro
    // Use the Q_INTERFACES() macro to tell Qt's meta-object system about the interfaces
    Q_INTERFACES(SCSHAREDLIB::IAlgorithm)

public:
    //=========================================================================================================
    /**
    * Constructs a NumericOutput.
    */
    NumericOutput();

    //=========================================================================================================
    /**
    * Destroys the NumericOutput.
    */
    ~NumericOutput();

    //=========================================================================================================
    /**
    * IAlgorithm functions
    */
    virtual QSharedPointer<IPlugin> clone() const;
    virtual void init();
    virtual void unload();
    virtual bool start();
    virtual bool stop();
    virtual IPlugin::PluginType getType() const;
    virtual QString getName() const;
    virtual QWidget* setupWidget();

    //=========================================================================================================
    /**
    * Udates the pugin with new (incoming) data.
    *
    * @param[in] pMeasurement    The incoming data in form of a generalized Measurement.
    */
    void update(SCMEASLIB::Measurement::SPtr pMeasurement);

protected:
    //=========================================================================================================
    /**
    * IAlgorithm function
    */
    virtual void run();

    void showYourWidget();

private:
    bool                                            m_bIsRunning;           /**< Flag whether thread is running.*/

    FIFFLIB::FiffInfo::SPtr                         m_pFiffInfo;            /**< Fiff measurement info.*/
    QSharedPointer<DummyYourWidget>                 m_pYourWidget;          /**< flag whether thread is running.*/
    QAction*                                        m_pActionShowYourWidget;/**< flag whether thread is running.*/

    IOBUFFER::CircularMatrixBuffer<double>::SPtr    m_pDummyBuffer;         /**< Holds incoming data.*/

    PluginInputData<SCMEASLIB::RealTimeMultiSampleArray>::SPtr      m_pDummyInput;      /**< The RealTimeMultiSampleArray of the NumericOutput input.*/
    PluginOutputData<SCMEASLIB::RealTimeMultiSampleArray>::SPtr     m_pDummyOutput;     /**< The RealTimeMultiSampleArray of the NumericOutput output.*/
    PluginOutputData<SCMEASLIB::Numeric>::SPtr m_SignalOutput;


signals:
    //=========================================================================================================
    /**
    * Emitted when fiffInfo is available
    */
    void fiffInfoAvailable();
};

} // NAMESPACE

#endif // NUMERICOUTPUT_H
