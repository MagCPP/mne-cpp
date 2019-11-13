#include "visualnf.h"
#include "ui_visualnf.h"

VisualNF::VisualNF(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualNF)
{
    ui->setupUi(this);
//    QPixmap yes(":/grafics/images/no.png");
//    ui->label_visualNF->setPixmap(yes);
}

VisualNF::~VisualNF()
{
    delete ui;
}

void VisualNF::showNegFB()
{
//    ui->label_visualNF->clear();
    QPixmap Negative(":/grafics/images/Bild2");
    ui->label_visualNF->setPixmap(Negative);
}

void VisualNF::showPosFB()
{
    ui->label_visualNF->clear();
    QPixmap Positive(":/grafics/images/Bild1");
    ui->label_visualNF->setPixmap(Positive);
}

void VisualNF::showNeutFB()
{
    ui->label_visualNF->clear();
    QPixmap Neutral(":/grafics/images/Bild3");
    ui->label_visualNF->setPixmap(Neutral);
}
