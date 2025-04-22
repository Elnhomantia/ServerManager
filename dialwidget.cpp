#include "dialwidget.h"
#include <qboxlayout>
#include <QPainter>

DialWidget::DialWidget(QWidget *parent) : QDial(parent), color(QColor(Qt::green))
{
    connect(this, &QDial::valueChanged, this, &DialWidget::onValueChanged);
    this->setRange(0, 100);

    //this->setFocusPolicy(Qt::NoFocus);
    //this->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->setNotchesVisible(false);

}
DialWidget::~DialWidget() {}

void DialWidget::onValueChanged(int val)
{
    if (val < 50)
    {
        this->setColor(QColor(Qt::green));
    }
    else if (val < 80)
    {
        this->setColor(QColor(QColorConstants::Svg::orange));
    }
    else
    {
        this->setColor(QColor(Qt::red));
    }
    this->update();
}
void DialWidget::setColor(QColor color)
{
    this->color = color;
    this->update();
}

void DialWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int side = qMin(width(), height());
    QRectF outerRect((width() - side) / 2.0, (height() - side) / 2.0, side, side);
    outerRect.adjust(5, 5, -5, -5);

    // Camembert (fond + portion remplie)
    int angleSpan = static_cast<int>(360.0 * value() / 100.0);

    // Background
    painter.setBrush(this->palette().window().color());
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(outerRect);

    // Outer ring
    painter.setBrush(this->color);
    painter.drawPie(outerRect, 90 * 16, -angleSpan * 16);

    // Inner ring
    float holeSize = 0.1;
    QRectF innerRect = outerRect.adjusted(side * holeSize, side * holeSize, -side * holeSize, -side * holeSize);
    painter.setBrush(QColor(0xe0e0e0));
    painter.drawEllipse(innerRect);

    // Percentage
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", side / 6.0, QFont::Bold));
    painter.drawText(outerRect, Qt::AlignCenter, QString("%1%").arg(value()));
}
