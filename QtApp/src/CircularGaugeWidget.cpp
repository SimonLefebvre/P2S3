//
// Created by Xavier on 2020-11-08.
//

#include "CircularGaugeWidget.h"

#include <QPainter>
#include <QTime>
#include <QTimer>
#include <algorithm>

CircularGaugeWidget::CircularGaugeWidget(QString name, uint32_t maxValue, QWidget *parent) :
    QWidget(parent),
    name(name),
    maxValue(maxValue)
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&CircularGaugeWidget::update));
    timer->start(1000);

    this->setBaseSize(255, 200);
}

void CircularGaugeWidget::paintEvent(QPaintEvent *)
{
    static const QPoint needlePts[3] = {
        {4, 0},
        {-4, 0},
        {0, -95}
    };

    double scaleRatio = (width() * 0.5 < height() * 0.68) ? width() / 1.36 : height();

    QPainter p(this);
    p.setFont(QFont("Bookman Old Style", 4, QFont::Bold));
    p.setRenderHint(QPainter::Antialiasing);
    p.translate(width() * 0.5, height() * 0.68);
    p.scale(scaleRatio / 210.0, scaleRatio / 210.0);
    p.setPen(QPen(QBrush(), 2, Qt::SolidLine, Qt::RoundCap));
    p.setBrush(needleColor);
    p.save();
    p.rotate(needleAngle);
    p.drawConvexPolygon(needlePts, 3);
    p.drawEllipse(QPoint(0, 0), 4, 4);
    p.restore();
    p.setPen(needleColor);

    int adjustedMax = maxValue * numberOfTicks / (numberOfTicks - 1);
    for (int i = 0; i < 360; i ++) {
        if(i % (240 / numberOfTicks) == 0) {
            if (i <= 90 || i >= 330) {  // Draw numbers left side of quadrant
                p.setPen(Qt::black);
                p.drawText(-130, 4, QString::number(((i + 20) % 360) * adjustedMax / 240));
            }
            if (i < 30 || i > 270) {    // Draw numbers right side of quadrant
                p.setPen(Qt::black);
                p.drawText(100, 4, QString::number(((i + 200) % 360) * adjustedMax / 240));
            }
            if (i < 30 || i >= 150) {   // Draw major tick lines
                p.setPen(QColor(142, 11, 11));
                p.drawLine(88, 0, 96, 0);
            }
        }
        else if((i < 20 || i >= 160) && i % (240 / (numberOfTicks * 5)) == 0){ // Draw minor tick lines
            p.setPen(QColor(0x3F, 0x3F, 0x3F));
            p.drawLine(88, 0, 92, 0);
        }
        p.rotate(1);
    }

    QFontMetrics fm(p.font());

    p.setPen(needleColor);
    p.drawText(-fm.horizontalAdvance(name) / 2, 50, name);
    p.setBrush(QColor(0, 0, 0, 0));
    p.drawChord(-140, -140, 140 * 2, 140 * 2, -28 * 16, 236 * 16);
}

void CircularGaugeWidget::setNeedle(uint32_t value)
{
    needleAngle = (value * 360 / maxValue) - 110;
}
