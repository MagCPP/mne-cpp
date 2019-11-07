#include "parametersetting.h"
#include "ui_parametersetting.h"

ParameterSetting::ParameterSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterSetting)
{
    ui->setupUi(this);
}

ParameterSetting::~ParameterSetting()
{
    delete ui;
}
