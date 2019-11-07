#include "visualnf.h"
#include "ui_visualnf.h"

VisualNF::VisualNF(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualNF)
{
    ui->setupUi(this);
    QPixmap yes(":/grafics/images/no.png");
    ui->label_visualNF->setPixmap(yes);
}

VisualNF::~VisualNF()
{
    delete ui;
}
