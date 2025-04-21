#ifndef DIALWIDGET_H
#define DIALWIDGET_H

#include <QLabel>
#include <QDial>
#include <QWidget>

class DialWidget : public QDial
{
    Q_OBJECT

public:
    DialWidget(QWidget *parent = nullptr);
    ~DialWidget();
    void setColor(QColor color);

private slots:
    void onValueChanged(int val);


protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QColor color;
};

#endif // DIALWIDGET_H
