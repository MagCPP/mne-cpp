#include "checkwidget.h"
#include "ui_checkwidget.h"

CheckWidget::CheckWidget(TmsNeurofeedback *owner, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckWidget)
//  , m_pMyRapid(owner)
{
    ui->setupUi(this);
    this->owner = owner;
    int error = 0;
//    m_pMyRapid->connect(error);

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

    if (owner->isArmed()) {
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

    if (owner->isReadyToFire()) {
        ui->readyLabel->setPixmap(yes);
    }
    else {
        ui->readyLabel->setPixmap(no);
    }
}

void CheckWidget::on_testButton_clicked()
{
    owner->quickfire();
}
