#include <widget/computerwidget.h>
#include "ui_computerwidget.h"

#include <widget/computerinfo.h>

ComputerWidget::ComputerWidget(QWidget *parent, Computer *c)
    : QWidget(parent)
    , ui(new Ui::ComputerWidget)
    , runner(CommandsPipeline(*c, this))
{
    ui->setupUi(this);
    this->computer = c;

    QProcess::connect(&(this->runner.getClient()), &SshClient::commandError,
                      this, &ComputerWidget::on_sshCommandError);
    QProcess::connect(&(this->runner.getClient()), &SshClient::commandResult,
                      this, &ComputerWidget::on_sshCommandExecuted);
    QProcess::connect(&(this->runner.getClient()), &SshClient::connectionClosed,
                      this, &ComputerWidget::on_sshConnectionClosed);
    QProcess::connect(&(this->runner.getClient()), &SshClient::connectionFailed,
                      this, &ComputerWidget::on_sshConnectionFailed);
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
    this->computer->sendWolPacket();
}
void ComputerWidget::on_rebootButton_clicked()
{
    if(nullptr == this->computer)
    {

        return;
    }
    this->runner.run("sudo reboot");
}
void ComputerWidget::on_shutdownButton_clicked()
{
    if(nullptr == this->computer)
    {

        return;
    }
    this->runner.run("sudo shutdown");
}


void ComputerWidget::on_editComputerButton_clicked()
{
    ComputerInfo window(this, this->computer);
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

void ComputerWidget::on_sshCommandError(const QString & error)
{
    qDebug() << "on_sshCommandError : " + error;
}
void ComputerWidget::on_sshCommandExecuted(const QString & result)
{
    qDebug() << "on_sshCommandExecuted" + result;
}
void ComputerWidget::on_sshConnectionClosed()
{

}
void ComputerWidget::on_sshConnectionFailed()
{

}

