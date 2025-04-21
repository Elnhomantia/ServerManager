#include "computerwidget.h"
#include "ui_computerwidget.h"

ComputerWidget::ComputerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ComputerWidget)
{
    ui->setupUi(this);
    //ui->statsFrame;
}

ComputerWidget::~ComputerWidget()
{
    delete ui;
}
