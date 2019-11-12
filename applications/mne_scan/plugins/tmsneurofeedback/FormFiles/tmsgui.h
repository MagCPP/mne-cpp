#ifndef TMSGUI_H
#define TMSGUI_H

#include <QWidget>

namespace Ui {
class TMSGui;
}

class TMSGui : public QWidget
{
    Q_OBJECT

public:
    explicit TMSGui(QWidget *parent = nullptr);
    ~TMSGui();

    QString getUnlockCode();
    QString getPort();
    int getVoltage();
    int getSuperRapid();
    //
    bool getStaticPower();
    int getPulses();
    double getDeadTime();
    int getFrequency();
    //
    bool getPosImage();
    bool getNeutImage();
    bool getNegImage();
    QString getPosImagePath();
    QString getNeutImagePath();
    QString getNegImagePath();
    double getPosImageHighTresh();
    double getPosImageLowTresh();
    double getNeutImageHighTresh();
    double getNeutImageLowTresh();
    double getNegImageHighTresh();
    double getNegImageLowTresh();

private slots:


    void on_checkBox_advanced_clicked(bool checked);

    void on_pushButton_resettms_clicked();

    void on_spinBox_pulses_valueChanged(int arg1);

    void on_comboBox_mode_currentIndexChanged(int index);

    void on_comboBox_power_currentIndexChanged(int index);

    void on_doubleSpinBox_lowPos_valueChanged(double arg1);

    void on_doubleSpinBox_highNeut_valueChanged(double arg1);

    void on_doubleSpinBox_lowNeut_valueChanged(double arg1);

    void on_doubleSpinBox_highNeg_valueChanged(double arg1);

    void on_pushButton_default_clicked();

    void on_checkBox_visNeut_clicked(bool checked);

    void on_pushButton_example_clicked();

private:
    Ui::TMSGui *ui;
};

#endif // TMSGUI_H
