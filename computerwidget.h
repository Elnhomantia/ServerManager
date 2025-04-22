#ifndef COMPUTERWIDGET_H
#define COMPUTERWIDGET_H

#include <QWidget>

#include "computer.h"
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

private slots:
    void on_startButton_clicked();
    void on_rebootButton_clicked();
    void on_shutdownButton_clicked();

private:
    Ui::ComputerWidget *ui;
    Computer * computer = nullptr;
};

#endif // COMPUTERWIDGET_H
