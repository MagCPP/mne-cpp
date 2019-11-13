#include "tmsgui.h"
#include "ui_tmsgui.h"
#include "QMessageBox"
#include <QThread>
#include  "visualnf.h"

TMSGui::TMSGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TMSGui)
{
    ui->setupUi(this);

    // Advanced Setup menu is not visible at the beginning
    ui->groupBox_unlockCode->setVisible(false);
    ui->groupBox_opVoltage->setVisible(false);
    ui->groupBox_superRapid->setVisible(false);
    // make sure that freq and duration can't be changed with the default settings
    ui->spinBox_frequency->setEnabled(false);
    ui->label_frequency->setEnabled(false);
    ui->doubleSpinBox_duration->setEnabled(false);
    ui->label_duration->setEnabled(false);
    // Operating Voltage per default to 240V
    ui->comboBox_opVoltage->setCurrentIndex(1);
    // default visual NF
    ui->checkBox_visPos->setChecked(true);
    ui->checkBox_visNeg->setChecked(true);
    ui->checkBox_visNeut->setChecked(true);
}

TMSGui::~TMSGui()
{
    delete ui;
}

QString TMSGui::getUnlockCode()
{
    return ui->lineEdit_unlock->text();
}

QString TMSGui::getPort()
{
    return ui->lineEdit_port->text();
}

int TMSGui::getVoltage()
{
    return ui->comboBox_opVoltage->currentText().toInt();
}

int TMSGui::getSuperRapid()
{
    return ui->comboBox_superRapid->currentText().toInt();
}

bool TMSGui::getStaticPower()
{
    if(ui->comboBox_power->currentText() == "Static")
        return true;
    else
        return false;
}

int TMSGui::getPulses()
{
    return ui->spinBox_pulses->value();
}

double TMSGui::getDeadTime()
{
    return ui->spinBox_dtime->value();
}

int TMSGui::getFrequency()
{
    return ui->spinBox_frequency->value();
}

bool TMSGui::getPosImage()
{
    return ui->checkBox_visPos->isChecked();
}

bool TMSGui::getNeutImage()
{
    return ui->checkBox_visNeut->isChecked();
}

bool TMSGui::getNegImage()
{
    return ui->checkBox_visNeg->isChecked();
}

QString TMSGui::getPosImagePath()
{
    return ui->lineEdit_positiv->text();
}

QString TMSGui::getNeutImagePath()
{
    return ui->lineEdit_neutral->text();
}

QString TMSGui::getNegImagePath()
{
    return ui->lineEdit_negative->text();
}

double TMSGui::getPosImageHighTresh()
{
    return ui->doubleSpinBox_highPos->value();
}

double TMSGui::getPosImageLowTresh()
{
    return ui->doubleSpinBox_lowPos->value();
}

double TMSGui::getNeutImageHighTresh()
{
    return ui->doubleSpinBox_highNeut->value();
}

double TMSGui::getNeutImageLowTresh()
{
    return ui->doubleSpinBox_lowNeut->value();
}

double TMSGui::getNegImageHighTresh()
{
    return ui->doubleSpinBox_highNeg->value();
}

double TMSGui::getNegImageLowTresh()
{
    return ui->doubleSpinBox_lowNeg->value();
}

double TMSGui::getWait()
{
    return ui->doubleSpinBox_visualwait->value();
}






void TMSGui::on_checkBox_advanced_clicked(bool checked)
{
    // make sure to make the advanced setup menu visible if needed
    if(checked == true) {
        ui->groupBox_unlockCode->setVisible(true);
        ui->groupBox_opVoltage->setVisible(true);
        ui->groupBox_superRapid->setVisible(true);
    }
    if(checked == false) {
        ui->groupBox_unlockCode->setVisible(false);
        ui->groupBox_opVoltage->setVisible(false);
        ui->groupBox_superRapid->setVisible(false);
    }
}

void TMSGui::on_comboBox_mode_currentIndexChanged(int index)
{
    if(index == 0) {
        ui->spinBox_pulses->setMinimum(1);
        ui->spinBox_pulses->setValue(1);
        ui->spinBox_frequency->setEnabled(true);
        ui->label_frequency->setEnabled(true);
        ui->spinBox_pulses->setEnabled(true);
        ui->label_pulses->setEnabled(true);
        ui->doubleSpinBox_duration->setEnabled(false);
        ui->label_duration->setEnabled(false);
        ui->spinBox_dtime->setEnabled(true);
        ui->label_dtime->setEnabled(true);
        ui->spinBox_power->setEnabled(true);
        ui->label_power->setEnabled(true);
        ui->label_power1->setEnabled(true);
        ui->comboBox_power->setEnabled(true);
        ui->pushButton_resettms->setEnabled(true);
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("The rTMS mode is not yet initialized!");
        msgBox.exec();

        ui->spinBox_pulses->setMinimum(2);
        ui->spinBox_frequency->setEnabled(false);
        ui->label_frequency->setEnabled(false);
        ui->spinBox_pulses->setEnabled(false);
        ui->label_pulses->setEnabled(false);
        ui->doubleSpinBox_duration->setEnabled(false);
        ui->label_duration->setEnabled(false);
        ui->spinBox_dtime->setEnabled(false);
        ui->label_dtime->setEnabled(false);
        ui->spinBox_power->setEnabled(false);
        ui->label_power->setEnabled(false);
        ui->label_power1->setEnabled(false);
        ui->comboBox_power->setEnabled(false);
        ui->pushButton_resettms->setEnabled(false);
    }
}

void TMSGui::on_pushButton_resettms_clicked()
{
    ui->spinBox_pulses->setValue(1);
    ui->spinBox_frequency->setValue(10);
    ui->doubleSpinBox_duration->setValue(1);
    ui->spinBox_dtime->setValue(15);
    ui->comboBox_mode->setCurrentIndex(0);
}

void TMSGui::on_spinBox_pulses_valueChanged(int arg1)
{
    if(arg1 == 1) {
        ui->spinBox_frequency->setEnabled(false);
        ui->label_frequency->setEnabled(false);
    }
    else {
        ui->spinBox_frequency->setEnabled(true);
        ui->label_frequency->setEnabled(true);
    }

}

void TMSGui::on_comboBox_power_currentIndexChanged(int index)
{
    if(index == 1)  {
        ui->spinBox_power->setEnabled(false);
        ui->label_power->setEnabled(false);
    }
    else {
        ui->spinBox_power->setEnabled(true);
        ui->label_power->setEnabled(true);
    }
}

void TMSGui::on_doubleSpinBox_lowPos_valueChanged(double arg1)
{
    ui->doubleSpinBox_highNeut->setValue(arg1);
}

void TMSGui::on_doubleSpinBox_highNeut_valueChanged(double arg1)
{
    ui->doubleSpinBox_lowPos->setValue(arg1);
    if(ui->doubleSpinBox_lowNeut->value() > arg1) {
        QMessageBox msgBox;
        msgBox.setText("There must be a positive difference between the values of the neutral feedback!");
        msgBox.exec();
    }
}

void TMSGui::on_doubleSpinBox_lowNeut_valueChanged(double arg1)
{
    ui->doubleSpinBox_highNeg->setValue(arg1);
    if(ui->doubleSpinBox_highNeut->value() < arg1) {
        QMessageBox msgBox;
        msgBox.setText("There must be a positive difference between the values of the neutral feedback!");
        msgBox.exec();
    }
}


void TMSGui::on_doubleSpinBox_highNeg_valueChanged(double arg1)
{
    ui->doubleSpinBox_lowNeut->setValue(arg1);
}

void TMSGui::on_pushButton_default_clicked()
{
    ui->lineEdit_port->setText("COM1");
    ui->lineEdit_unlock->setText("");
    ui->comboBox_opVoltage->setCurrentIndex(1);
    ui->comboBox_superRapid->setCurrentIndex(0);
    ui->checkBox_advanced->setChecked(false);
    ui->groupBox_unlockCode->setVisible(false);
    ui->groupBox_opVoltage->setVisible(false);
    ui->groupBox_superRapid->setVisible(false);
}




void TMSGui::on_checkBox_visNeut_clicked(bool checked)
{
    if(checked == false) {
        ui->lineEdit_neutral->setEnabled(false);
        ui->doubleSpinBox_highNeut->setEnabled(false);
        ui->doubleSpinBox_lowNeut->setEnabled(false);
    }
    if(checked == true) {
        ui->lineEdit_neutral->setEnabled(true);
        ui->doubleSpinBox_highNeut->setEnabled(true);
        ui->doubleSpinBox_lowNeut->setEnabled(true);
    }
}

void TMSGui::on_pushButton_example_clicked()
{

}

void TMSGui::on_pushButton_connect_clicked()
{
    int error = 0;
    int error2 = 0;
    // Prepare Rapid
    QSerialPort porto;
    porto.setPortName(getPort());

    if (porto.open(QIODevice::ReadWrite)) {
        porto.close();
        Rapid myRapid(getPort(),getSuperRapid(), getUnlockCode(), getVoltage(), std::make_tuple(7,2,0));
        myRapid.connect(error);
        myRapid.disconnect(error2);
//        delete myRapid;
    } else {
        error = 1;
    }

    QString message;
    switch (error) {
    case 0:
        message = "Connection established. No need to change device settings anymore.";
        break;
    default:
        message = "Connection failed. Please change device settings.";
        break;
    }

    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();

}
