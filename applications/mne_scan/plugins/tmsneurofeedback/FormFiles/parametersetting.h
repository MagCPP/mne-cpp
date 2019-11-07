#ifndef PARAMETERSETTING_H
#define PARAMETERSETTING_H

#include <QWidget>

namespace Ui {
class ParameterSetting;
}

class ParameterSetting : public QWidget
{
    Q_OBJECT

public:
    explicit ParameterSetting(QWidget *parent = nullptr);
    ~ParameterSetting();

private:
    Ui::ParameterSetting *ui;
};

#endif // PARAMETERSETTING_H
