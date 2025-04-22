#include "computerwidget.h"
#include "ui_computerwidget.h"

ComputerWidget::ComputerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ComputerWidget)
{
    ui->setupUi(this);
}

ComputerWidget::~ComputerWidget()
{
    delete ui;
}

void ComputerWidget::on_startButton_clicked()
{
    if(nullptr == this->computer)
    {

        return;
    }
    this->computer->wakeup();
}
void ComputerWidget::on_rebootButton_clicked()
{
    if(nullptr == this->computer)
    {

        return;
    }
    this->computer->reboot();
}
void ComputerWidget::on_shutdownButton_clicked()
{
    if(nullptr == this->computer)
    {

        return;
    }
    this->computer->shutdown();
}

