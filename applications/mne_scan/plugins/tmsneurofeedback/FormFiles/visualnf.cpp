#include "visualnf.h"
#include "ui_visualnf.h"

VisualNF::VisualNF(QWidget *parent) :
    QWidget(parent),
    m_pTMSGui (new TMSGui()),
    ui(new Ui::VisualNF)
{
    ui->setupUi(this);
    QPixmap Negative(m_pTMSGui->getNegImagePath());
    QPixmap Positive(m_pTMSGui->getPosImagePath());
    QPixmap Neutral(m_pTMSGui->getNeutImagePath());

    ui->label_visualnegNF->setPixmap(Negative);
    ui->label_visualposNF->setPixmap(Positive);
    ui->label_visualneutNF->setPixmap(Neutral);

    ui->label_visualnegNF->setVisible(true);
    ui->label_visualposNF->setVisible(false);
    ui->label_visualneutNF->setVisible(false);


}

VisualNF::~VisualNF()
{
    delete ui;
}

void VisualNF::showNegFB()
{
    ui->label_visualposNF->setVisible(false);
    ui->label_visualneutNF->setVisible(false);
    ui->label_visualnegNF->setVisible(true);
}

void VisualNF::showPosFB()
{
    ui->label_visualnegNF->setVisible(false);
    ui->label_visualneutNF->setVisible(false);
    ui->label_visualposNF->setVisible(true);
}

void VisualNF::showNeutFB()
{
    ui->label_visualposNF->setVisible(false);
    ui->label_visualnegNF->setVisible(false);
    ui->label_visualneutNF->setVisible(true);
}
