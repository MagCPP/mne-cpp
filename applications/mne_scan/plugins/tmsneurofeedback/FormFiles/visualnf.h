#ifndef VISUALNF_H
#define VISUALNF_H

#include <QWidget>
#include "tmsgui.h"

#include <ctime>

namespace Ui {
class VisualNF;
}

class VisualNF : public QWidget
{
    Q_OBJECT

public:
    explicit VisualNF(double updatetime, QString negImagePath, QString neutImagePath, QString posImagePath, QWidget *parent = nullptr);
    ~VisualNF();
    void showNegFB();
    void showPosFB();
    void showNeutFB();

private:
    double m_updateTime;
    double m_nextUpdateTime;

    bool m_showNeg = false;
    bool m_showNeut = false;
    bool m_showPos = false;

    Ui::VisualNF *ui;
};

#endif // VISUALNF_H
