#ifndef VISUALNF_H
#define VISUALNF_H

#include <QWidget>

namespace Ui {
class VisualNF;
}

class VisualNF : public QWidget
{
    Q_OBJECT

public:
    explicit VisualNF(QWidget *parent = nullptr);
    ~VisualNF();

private:
    Ui::VisualNF *ui;
};

#endif // VISUALNF_H
