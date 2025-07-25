#ifndef COMPUTERWIDGET_H
#define COMPUTERWIDGET_H

#include <QTextEdit>
#include <QWidget>

#include <core/computer.h>
#include <widget/dial/dialwidget.h>
#include <core/commandspipeline.h>

namespace Ui {
class ComputerWidget;
}

class ComputerWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::ComputerWidget *ui;
    Computer * computer = nullptr;
    CommandsPipeline runner;
    QTextEdit * errorsArea;
    QTextEdit * logsArea;

private slots:
    void on_startButton_clicked();
    void on_rebootButton_clicked();
    void on_shutdownButton_clicked();
    void on_editComputerButton_clicked();

    void on_sshCommandError(const QString &error);
    void on_sshCommandExecuted(const QString & result);
    void on_sshConnectionClosed();
    void on_sshConnectionFailed(const QString & error);



public:
    explicit ComputerWidget(QWidget *parent = nullptr, Computer * c = nullptr);
    ~ComputerWidget();


};

#endif // COMPUTERWIDGET_H
