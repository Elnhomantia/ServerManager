#ifndef COMPUTERINFO_H
#define COMPUTERINFO_H

#include "computer.h"
#include <QDialog>

namespace Ui {
class computerInfo;
}

class ComputerInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ComputerInfo(QWidget *parent = nullptr, Computer *com = nullptr);
    //ComputerInfo(QWidget *parent = nullptr, Computer *com = nullptr);
    ~ComputerInfo();
    Computer * getComputerInfo();

private slots:
    void on_browsePrivateKeyButton_clicked();


    void accept() override;

private:
    Ui::computerInfo *ui;
    QString privateKeyPath;
    bool checkIsOK();
};

#endif // COMPUTERINFO_H
