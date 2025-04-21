#ifndef COMPUTERWIDGET_H
#define COMPUTERWIDGET_H

#include <QWidget>

#include "dialwidget.h"

namespace Ui {
class ComputerWidget;
}

class ComputerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ComputerWidget(QWidget *parent = nullptr);
    ~ComputerWidget();

private:
    Ui::ComputerWidget *ui;
};

#endif // COMPUTERWIDGET_H
