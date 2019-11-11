//=============================================================================================================
/**
* @file     numericoutput.cpp
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
* @brief    Definition of the NumericOutput class.
*
*/

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "numericoutput.h"


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace NUMERICOUTPUTPLUGIN;
using namespace SCSHAREDLIB;
using namespace SCMEASLIB;
using namespace IOBUFFER;


//*************************************************************************************************************
//=============================================================================================================
// DEFINE MEMBER METHODS
//=============================================================================================================

NumericOutput::NumericOutput()
: m_bIsRunning(false)
, m_pDummyInput(NULL)
, m_pSignalOutput(NULL)
, m_pDummyBuffer(CircularMatrixBuffer<double>::SPtr())
{
    //Add action which will be visible in the plugin's toolbar
    m_pActionShowYourWidget = new QAction(QIcon(":/images/options.png"), tr("Your Toolbar Widget"),this);
    m_pActionShowYourWidget->setShortcut(tr("F12"));
    m_pActionShowYourWidget->setStatusTip(tr("Your Toolbar Widget"));
    connect(m_pActionShowYourWidget, &QAction::triggered,
            this, &NumericOutput::showYourWidget);
    addPluginAction(m_pActionShowYourWidget);
}


//*************************************************************************************************************

NumericOutput::~NumericOutput()
{
    if(this->isRunning())
        stop();
}


//*************************************************************************************************************

QSharedPointer<IPlugin> NumericOutput::clone() const
{
    QSharedPointer<NumericOutput> pNumericOutputClone(new NumericOutput);
    return pNumericOutputClone;
}


//*************************************************************************************************************

void NumericOutput::init()
{
    // Input
    m_pDummyInput = PluginInputData<RealTimeMultiSampleArray>::create(this, "DummyIn", "Dummy input data");
    m_inputConnectors.append(m_pDummyInput);

    // Output - Uncomment this if you don't want to send processed data (in form of a matrix) to other plugins.
    // Also, this output stream will generate an online display in your plugin

    m_pSignalOutput = PluginOutputData<Numeric>::create(this, "SignalOut", "Signal output data");
    m_outputConnectors.append(m_pSignalOutput);


    // Register for update
    connect(m_pDummyInput.data(), &PluginInputConnector::notify, this, &NumericOutput::update, Qt::DirectConnection);

    //Delete Buffer - will be initailzed with first incoming data
    if(!m_pDummyBuffer.isNull())
        m_pDummyBuffer = CircularMatrixBuffer<double>::SPtr();
}


//*************************************************************************************************************

void NumericOutput::unload()
{

}


//*************************************************************************************************************

bool NumericOutput::start()
{
    return true;
}


//*************************************************************************************************************

bool NumericOutput::stop()
{
    return true;
}


//*************************************************************************************************************

IPlugin::PluginType NumericOutput::getType() const
{
    return _IAlgorithm;
}


//*************************************************************************************************************

QString NumericOutput::getName() const
{
    return "Numeric Output";
}


//*************************************************************************************************************

QWidget* NumericOutput::setupWidget()
{
    DummySetupWidget* setupWidget = new DummySetupWidget(this);//widget is later distroyed by CentralWidget - so it has to be created everytime new
    return setupWidget;
}


//*************************************************************************************************************

void NumericOutput::update(SCMEASLIB::Measurement::SPtr pMeasurement)
{
    QSharedPointer<Numeric> pRTMSA = pMeasurement.dynamicCast<Numeric>();

    if(pRTMSA) {
        m_pSignalOutput->data()->setValue(0.3);
        m_pSignalOutput->data()->setVisibility(true);
//        //Check if buffer initialized
//        if(!m_pDummyBuffer) {
//            m_pDummyBuffer = CircularMatrixBuffer<double>::SPtr(new CircularMatrixBuffer<double>(64, pRTMSA->getNumChannels(), pRTMSA->getMultiSampleArray()[0].cols()));
//        }

//        //Fiff information
//        if(!m_pFiffInfo) {
//            m_pFiffInfo = pRTMSA->info();

//            //Init output - Unocmment this if you also uncommented the m_pDummyOutput in the constructor above
//            m_pDummyOutput->data()->initFromFiffInfo(m_pFiffInfo);
//            m_pDummyOutput->data()->setMultiArraySize(1);
//            m_pDummyOutput->data()->setVisibility(true);
//        }

//        MatrixXd t_mat;

//        for(unsigned char i = 0; i < pRTMSA->getMultiArraySize(); ++i) {
//            t_mat = pRTMSA->getMultiSampleArray()[i];
//            m_pDummyBuffer->push(&t_mat);
//        }
    }
}



//*************************************************************************************************************

void NumericOutput::run()
{
    //
    // Wait for Fiff Info
    //
//    while(!m_pFiffInfo)
//        msleep(10);// Wait for fiff Info

//    while(m_bIsRunning)
//    {
//        //Dispatch the inputs
//        MatrixXd t_mat = m_pDummyBuffer->pop();

//        //ToDo: Implement your algorithm here

//        //Send the data to the connected plugins and the online display
//        //Unocmment this if you also uncommented the m_pDummyOutput in the constructor above
//        m_pDummyOutput->data()->setValue(t_mat);
//    }
}


//*************************************************************************************************************

void NumericOutput::showYourWidget()
{
    m_pYourWidget = DummyYourWidget::SPtr(new DummyYourWidget());
    m_pYourWidget->show();
}
