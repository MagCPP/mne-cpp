#ifndef CHECKWIDGET_H
#define CHECKWIDGET_H

#include <QWidget>

#include <magcpp/devices/magstim.h>
#include <magcpp/devices/rapid.h>

#include "../tmsneurofeedback.h"

class TmsNeurofeedback;

namespace Ui {
class CheckWidget;
}

class CheckWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CheckWidget(TmsNeurofeedback *owner, QWidget *parent = nullptr);
    ~CheckWidget();

private:
//    QSharedPointer<Rapid> m_pMyRapid;

private slots:
    void on_armedButton_clicked();

    void on_readyfireButton_clicked();

    void on_testButton_clicked();

private:
    Ui::CheckWidget *ui;

    TmsNeurofeedback *owner;
};

#endif // CHECKWIDGET_H
