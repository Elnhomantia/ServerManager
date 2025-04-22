#include "computerwidget.h"
#include "ui_computerwidget.h"

#include "computerinfo.h"

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

void ComputerWidget::setComputer(Computer * c)
{
    this->computer = c;
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


void ComputerWidget::on_editComputerButton_clicked()
{
    ComputerInfo window(this);
    int ret = window.exec();
    if(QDialog::Accepted == ret)
    {
        if(nullptr != this->computer)
        {
            delete this->computer;
        }
        this->computer = window.getComputerInfo();
        ui->computerGroupBox->setTitle(this->computer->getName());
    }
}

