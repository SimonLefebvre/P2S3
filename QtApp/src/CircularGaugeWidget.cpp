//
// Created by Xavier on 2020-11-08.
//

#include "CircularGaugeWidget.h"

#include <QPainter>
#include <QTime>
#include <QTimer>

CircularGaugeWidget::CircularGaugeWidget(QString name, uint32_t maxValue, QWidget *parent) :
    QWidget(parent),
    name(name),
    maxValue(maxValue)
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&CircularGaugeWidget::update));
    timer->start(1000);
}

void CircularGaugeWidget::paintEvent(QPaintEvent *)
{
    static const QPoint needle[3] = {
            QPoint(4, 0),
            QPoint(-4, 0),
            QPoint(0, -95)
    };

    int side = qMin(width(), height());
    QTime time = QTime::currentTime();

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.translate(width() / 2, height() * 0.65);
    p.scale(side / 210.0, side / 210.0);
    p.setPen(QPen(QBrush(), 2, Qt::SolidLine, Qt::RoundCap));
    p.setBrush(hourColor);
    p.save();
    p.rotate(needleAngle);
    p.drawConvexPolygon(needle, 3);
    p.drawEllipse(QPoint(0, 0), 4, 4);
    p.restore();
    p.setPen(hourColor);

    int adjustedMax = maxValue * numberOfTicks / (numberOfTicks - 1);
    for (int i = 0; i < 360; i ++) {
        if(i % (240 / numberOfTicks) == 0) {
            if (i <= 90 || i >= 330) {
                p.setPen(Qt::black);
                p.drawText(-124, 4, QString::number(((i + 20) % 360) * adjustedMax / 240));
            }
            if (i < 30 || i > 270) {
                p.setPen(Qt::black);
                p.drawText(100, 4, QString::number(((i + 200) % 360) * adjustedMax / 240));
            }
            if (i < 30 || i >= 150) {
                p.setPen(QColor(142, 11, 11));
                p.drawLine(88, 0, 96, 0);
            }
        }
        if((i < 20 || i >= 160) && i % (240 / (numberOfTicks * 5)) == 0 && i % (240 / numberOfTicks)){
            p.setPen(QColor(0x3F, 0x3F, 0x3F));
            p.drawLine(88, 0, 92, 0);
        }
        p.rotate(1);
    }

    p.setPen(QColor(0x3F, 0x3F, 0x3F));
    p.drawText(-25, 50, name);
    p.setBrush(QColor(0, 0, 0, 0));
    p.drawChord(-135, -135, 135 * 2, 135 * 2, -30 * 16, 240 * 16);
}

void CircularGaugeWidget::setNeedle(uint32_t value)
{
    needleAngle = (value * 360 / maxValue) - 110;
}
