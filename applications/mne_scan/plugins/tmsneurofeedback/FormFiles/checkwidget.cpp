#include "checkwidget.h"
#include "ui_checkwidget.h"

CheckWidget::CheckWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckWidget)
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

    if (i == 1) {
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

    if (i == 1) {
        ui->readyLabel->setPixmap(yes);
    }
    else {
        ui->readyLabel->setPixmap(no);
    }
}
