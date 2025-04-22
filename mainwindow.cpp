#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet(R"(
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
    )");
}

MainWindow::~MainWindow()
{
    delete ui;
}

