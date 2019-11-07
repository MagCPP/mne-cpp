#include "tmsguiparameter.h"
#include "ui_tmsguiparameter.h"

TMSGuiParameter::TMSGuiParameter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TMSGuiParameter)
{
    ui->setupUi(this);
}

TMSGuiParameter::~TMSGuiParameter()
{
    delete ui;
}
