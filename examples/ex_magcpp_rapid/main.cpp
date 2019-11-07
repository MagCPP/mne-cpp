//=============================================================================================================
/**
* @file     main.cpp
* @author   Hannes Oppermann; Felix Wichum <hannes.oppermann@tu-ilmenau.de; felix.wichum@tu-ilmenau.de>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     November, 2019
*
* @section  LICENSE
*
* Copyright (C) 2019, Hannes Oppermann; Felix Wichum and Matti Hamalainen. All rights reserved.
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
* @brief     Example for testing MagCPP library with Rapid unit.
*
*/

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include <magcpp/devices/magstim.h>
#include <magcpp/devices/rapid.h>

#include <iostream>

//*************************************************************************************************************
//=============================================================================================================
// Eigen
//=============================================================================================================


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QApplication>
#include <QCommandLineParser>


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================


//*************************************************************************************************************
//=============================================================================================================
// MAIN
//=============================================================================================================

//=============================================================================================================
/**
* The function main marks the entry point of the program.
* By default, main has the storage class extern.
*
* @param [in] argc (argument count) is an integer that indicates how many arguments were entered on the command line when the program was started.
* @param [in] argv (argument vector) is an array of pointers to arrays of character objects. The array objects are null-terminated strings, representing the arguments that were entered on the command line when the program was started.
* @return the value that was set to exit() (which is 0 if exit() is called via quit()).
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Command Line Parser
    QCommandLineParser parser;
    parser.setApplicationDescription("Example name");
    parser.addHelpOption();

    QCommandLineOption parameterOption("parameter", "The first parameter description.");

    parser.addOption(parameterOption);

    parser.process(a);

    // Add exampel code here
    Rapid myMag("COM20",0,"",240,std::make_tuple(7,2,0)); // COM1
    int error = 0;

    myMag.connect(error);

    std::map<QString, std::map<QString, double> > xyz;
    xyz = myMag.getParameters(error);
    std::cout << "Power : " << xyz["rapidParam"]["power"] << std::endl;
    std::cout << "Frequency : " << xyz["rapidParam"]["frequency"] << std::endl;
    std::cout << "nPulses : " << xyz["rapidParam"]["nPulses"] << std::endl;
    std::cout << "Duration : " << xyz["rapidParam"]["duration"] << std::endl;
    std::cout << "Wait : " << xyz["rapidParam"]["wait"] << std::endl;


    myMag.setPower(20, false, xyz, error);

    myMag.arm(false,xyz, error);

    std::cout << "Armed, underControll, ReadyToFire : " << myMag.isArmed() << myMag.isUnderControl() << myMag.isReadyToFire() << std::endl;

    myMag.ignoreCoilSafetySwitch(error);

    QThread::sleep(1);

    myMag.quickFire(error);
    myMag.resetQuickFire();
    QThread::msleep(20);
    myMag.quickFire(error);
    myMag.resetQuickFire();

    QThread::sleep(2);

    myMag.disconnect(error);

    std::cout << "---------------------------" << std::endl;
    std::cout << "Termination error :" << error << std::endl;

    return a.exec();
}
