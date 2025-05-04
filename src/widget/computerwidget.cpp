#include <widget/computerwidget.h>
#include "ui_computerwidget.h"

#include <widget/computerinfo.h>
#include <widget/collapsable/collapsablewidget.h>

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

    CollapsableWidget * errorsFrame = new CollapsableWidget("Errors", this);
    QScrollArea * errorsArea = new QScrollArea(errorsFrame);
    QVBoxLayout * errorsLayout = new QVBoxLayout(errorsArea);
    this->errorsArea = new QTextEdit(errorsArea);
    this->errorsArea->setReadOnly(true);
    this->errorsArea->setFocusPolicy(Qt::NoFocus);
    errorsLayout->addWidget(this->errorsArea);
    errorsArea->setLayout(errorsLayout);
    errorsFrame->getContent()->addWidget(errorsArea);
    ui->contentLayout->addWidget(errorsFrame);

    CollapsableWidget * logsFrame = new CollapsableWidget("Logs", this);
    QScrollArea * logsArea = new QScrollArea(logsFrame);
    QVBoxLayout * logsLayout = new QVBoxLayout(logsArea);
    this->logsArea = new QTextEdit(logsArea);
    this->logsArea->setReadOnly(true);
    this->logsArea->setFocusPolicy(Qt::NoFocus);
    logsLayout->addWidget(this->logsArea);
    logsArea->setLayout(logsLayout);
    logsFrame->getContent()->addWidget(logsArea);
    ui->contentLayout->addWidget(logsFrame);
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
    this->errorsArea->append(error);
}
void ComputerWidget::on_sshCommandExecuted(const QString & result)
{
    qDebug() << result;
}
void ComputerWidget::on_sshConnectionClosed()
{

}
void ComputerWidget::on_sshConnectionFailed(const QString & error)
{
    this->errorsArea->append(error);
}

