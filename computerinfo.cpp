#include "computerinfo.h"
#include "ui_computerinfo.h"

#include <QFileDialog>
#include <QDebug>

ComputerInfo::ComputerInfo(QWidget *parent, Computer * com)
    : QDialog(parent)
    , ui(new Ui::computerInfo)
{
    ui->setupUi(this);
}

ComputerInfo::~ComputerInfo()
{
    delete ui;
}
Computer * ComputerInfo::getComputerInfo()
{
    QString ip = ui->Ip1spinBox->text() + "." + ui->Ip2spinBox->text() + "." + ui->Ip3spinBox->text() + "." + ui->Ip4spinBox->text();
    QString mac = ui->Mac1SpinBox->text() + ui->Mac2SpinBox->text() + ui->Mac3SpinBox->text() + ui->Mac4SpinBox->text() + ui->Mac5SpinBox->text() + ui->Mac6SpinBox->text();
    return new Computer(User(ui->userNameLineEdit->text(), this->privateKeyPath), ip, mac, ui->computerNameLineEdit->text(), ui->WolSpinBox->text().toShort());
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
    qDebug() << checkIsOK();
    if(this->checkIsOK())
    {
        QDialog::accept();
    }
}

