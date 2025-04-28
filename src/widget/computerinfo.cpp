#include <widget/computerinfo.h>
#include "ui_computerinfo.h"

#include <QFileDialog>
#include <QDebug>

ComputerInfo::ComputerInfo(QWidget *parent, Computer * com)
    : QDialog(parent)
    , ui(new Ui::computerInfo)
{
    ui->setupUi(this);
    if(nullptr != com)
    {
        ui->WolSpinBox->setValue(com->getWolPort());
        this->setIp(com->getIpAddress());
        this->setMac(com->getMacAddress());
        ui->computerNameLineEdit->setText(com->getName());
        this->privateKeyPath = com->getUser().getPrivateKeyPath();
        ui->privateKeyPathLabel->setText(this->privateKeyPath.split('/').last());
        ui->userNameLineEdit->setText(com->getUser().getUserName());
        ui->sshPortSpinBox->setValue(com->getSshPort());
    }
}

ComputerInfo::~ComputerInfo()
{
    delete ui;
}
Computer * ComputerInfo::getComputerInfo()
{
    return new Computer(User(ui->userNameLineEdit->text(), this->privateKeyPath),
                        this->getIp(), this->getMac(), ui->computerNameLineEdit->text(), ui->WolSpinBox->value(), ui->sshPortSpinBox->value());
}

void ComputerInfo::on_browsePrivateKeyButton_clicked()
{
    this->privateKeyPath = QFileDialog::getOpenFileName(this, tr("Load private key."), "", tr("Key (*.pem)"));
    if(this->privateKeyPath.isEmpty())
    {
        ui->privateKeyPathLabel->setText("No file selected");
    }
    else
    {
        ui->privateKeyPathLabel->setText(this->privateKeyPath.split('/').last());
    }
}
bool ComputerInfo::checkIsOK()
{
    return !this->privateKeyPath.isEmpty() && !ui->computerNameLineEdit->text().isEmpty() && !ui->userNameLineEdit->text().isEmpty();
}


void ComputerInfo::accept()
{
    if(this->checkIsOK())
    {
        QDialog::accept();
    }
}

void ComputerInfo::setIp(const QString & ip)
{
    QStringList ipValues = ip.split(".");
    ui->Ip1spinBox->setValue(ipValues.at(0).toInt());
    ui->Ip2spinBox->setValue(ipValues.at(1).toInt());
    ui->Ip3spinBox->setValue(ipValues.at(2).toInt());
    ui->Ip4spinBox->setValue(ipValues.at(3).toInt());
}
void ComputerInfo::setMac(const QString & mac)
{
    QStringList macValues = mac.split(":");
    bool ok;
    ui->Mac1SpinBox->setValue(macValues.at(0).toInt(&ok, 16));
    ui->Mac2SpinBox->setValue(macValues.at(1).toInt(&ok, 16));
    ui->Mac3SpinBox->setValue(macValues.at(2).toInt(&ok, 16));
    ui->Mac4SpinBox->setValue(macValues.at(3).toInt(&ok, 16));
    ui->Mac5SpinBox->setValue(macValues.at(4).toInt(&ok, 16));
    ui->Mac6SpinBox->setValue(macValues.at(5).toInt(&ok, 16));
}
QString ComputerInfo::getIp() const
{
    return ui->Ip1spinBox->text() + "."
           + ui->Ip2spinBox->text() + "."
           + ui->Ip3spinBox->text() + "."
           + ui->Ip4spinBox->text();
}
QString ComputerInfo::getMac() const
{
    return ui->Mac1SpinBox->text() + ":"
           + ui->Mac2SpinBox->text() + ":"
           + ui->Mac3SpinBox->text() + ":"
           + ui->Mac4SpinBox->text() + ":"
           + ui->Mac5SpinBox->text() + ":"
           + ui->Mac6SpinBox->text();
}

