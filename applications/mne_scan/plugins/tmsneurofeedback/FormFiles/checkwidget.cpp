#include "checkwidget.h"
#include "ui_checkwidget.h"

CheckWidget::CheckWidget(QSharedPointer<Rapid> myRapid, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckWidget),
    m_pMyRapid(myRapid)
{
    ui->setupUi(this);

}

CheckWidget::~CheckWidget()
{
    delete ui;
}

void CheckWidget::on_armedButton_clicked()
{
    QPixmap yes(":/grafics/images/yes.png");
    QPixmap no(":/grafics/images/no.png");
    int i = 2;
    printf("Check is armed: ");

    if (m_pMyRapid->isArmed()) {
        ui->armedLabel->setPixmap(yes);
    }
    else {
        ui->armedLabel->setPixmap(no);
    }
}

void CheckWidget::on_readyfireButton_clicked()
{
    QPixmap yes(":/grafics/images/yes.png");
    QPixmap no(":/grafics/images/no.png");
    int i = 1;

    if (m_pMyRapid->isReadyToFire()) {
        ui->readyLabel->setPixmap(yes);
    }
    else {
        ui->readyLabel->setPixmap(no);
    }
}

void CheckWidget::on_testButton_clicked()
{
    int error = 0;
    m_pMyRapid->ignoreCoilSafetySwitch(error);
    m_pMyRapid->quickFire(error);
    m_pMyRapid->resetQuickFire();
}
