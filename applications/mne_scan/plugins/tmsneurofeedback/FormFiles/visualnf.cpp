#include "visualnf.h"
#include "ui_visualnf.h"

VisualNF::VisualNF(double updatetime, QString negImagePath, QString neutImagePath, QString posImagePath, QWidget *parent) :
    m_updateTime(updatetime),
    QWidget(parent),
    ui(new Ui::VisualNF)
{
    ui->setupUi(this);
    QPixmap Negative(negImagePath);
    QPixmap Positive(posImagePath);
    QPixmap Neutral(neutImagePath);

    ui->label_visualnegNF->setPixmap(Negative);
    ui->label_visualposNF->setPixmap(Positive);
    ui->label_visualneutNF->setPixmap(Neutral);

    ui->label_visualnegNF->setVisible(true);
    ui->label_visualposNF->setVisible(false);
    ui->label_visualneutNF->setVisible(false);

    m_nextUpdateTime = clock();

}

VisualNF::~VisualNF()
{
    delete ui;
}

void VisualNF::showNegFB()
{
    if (!m_showNeg & (clock() > m_nextUpdateTime)) {
        ui->label_visualposNF->setVisible(false);
        ui->label_visualneutNF->setVisible(false);
        ui->label_visualnegNF->setVisible(true);
        m_showNeg = true;
        m_showPos = false;
        m_showNeut = false;
        m_nextUpdateTime = clock()  + m_updateTime * CLOCKS_PER_SEC;
    }
}

void VisualNF::showPosFB()
{
    if (!m_showPos & (clock() > m_nextUpdateTime)) {
        ui->label_visualnegNF->setVisible(false);
        ui->label_visualneutNF->setVisible(false);
        ui->label_visualposNF->setVisible(true);
        m_showNeg = false;
        m_showPos = true;
        m_showNeut = false;
        m_nextUpdateTime = clock()  + m_updateTime * CLOCKS_PER_SEC;
    }
}

void VisualNF::showNeutFB()
{
    if (!m_showNeut & (clock() > m_nextUpdateTime)) {
        ui->label_visualposNF->setVisible(false);
        ui->label_visualnegNF->setVisible(false);
        ui->label_visualneutNF->setVisible(true);
        m_showNeg = false;
        m_showPos = false;
        m_showNeut = true;
        m_nextUpdateTime = clock()  + m_updateTime * CLOCKS_PER_SEC;
    }
}

void VisualNF::example()
{
    double time = clock() + m_updateTime * CLOCKS_PER_SEC;
    showPosFB();
    while(clock() < time) {

    }
    time = clock() + m_updateTime * CLOCKS_PER_SEC;
    showNeutFB();
    while(clock() < time) {

    }
    time = clock() + m_updateTime * CLOCKS_PER_SEC;
    showNegFB();
    while(clock() < time) {

    }
    time = clock() + m_updateTime * CLOCKS_PER_SEC;
}
