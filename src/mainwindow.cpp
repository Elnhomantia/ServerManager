#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <widget/computerwidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*this->setStyleSheet(R"(
    QWidget {
        background-color: #2b2b2b;
        color: #d3d3d3;
    }
    QPushButton {
        background-color: #d3d3d3;
        color: #2b2b2b;
    }
    QPushButton:hover {
        background-color: #eeeeee;
        color: #2b2b2b;
    }
    QPushButton:pressed {
        background-color: #b0b0b0;
        color: #d3d3d3;
    }
    )");*/

    ComputerWidget * cWidget = new ComputerWidget(this, new Computer(User("sshadmin", "C:/Users/gloub/.ssh/id_ed25519.pem"), "192.168.1.150", "ff:ff:ff:ff:ff:ff", "myPC", 9, 22));
    //QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
    //ui->centralwidget->setLayout(layout);
    //ui->centralwidget->layout()->addWidget(cWidget);
    setCentralWidget(cWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

