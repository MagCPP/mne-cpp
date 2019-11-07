#ifndef CHECKWIDGET_H
#define CHECKWIDGET_H

#include <QWidget>

namespace Ui {
class CheckWidget;
}

class CheckWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CheckWidget(QWidget *parent = nullptr);
    ~CheckWidget();

private slots:
    void on_armedButton_clicked();

    void on_readyfireButton_clicked();

private:
    Ui::CheckWidget *ui;
};

#endif // CHECKWIDGET_H
