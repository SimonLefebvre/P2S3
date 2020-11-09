//
// Created by Xavier on 2020-11-08.
//

#include "CircularGaugeWidget.h"

#include <QPainter>
#include <QTime>
#include <QTimer>

CircularGaugeWidget::CircularGaugeWidget(QWidget *parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&CircularGaugeWidget::update));
    timer->start(1000);

    resize(200, 200);
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
    p.scale(side / 200.0, side / 200.0);
    p.setPen(Qt::NoPen);
    p.setBrush(hourColor);
    p.save();
    p.rotate( time.second());
    p.drawConvexPolygon(needle, 3);
    p.drawEllipse(QPoint(0, 0), 4, 4);
    p.restore();
    p.setPen(hourColor);

    for (int i = 0; i < 360; i += (240 / numberOfTicks)) {
        if(i <= 90 || i >= 330){
            p.drawText(-124, 4, QString::number(((i + 30) % 360) * maxValue / 240 - 100));
        }
        if(i < 30 || i > 270){
            p.drawText(100, 4, QString::number(((i + 210) % 360) * maxValue / 240 - 100));
        }
        if(i < 30 || i >= 150) {
            p.drawLine(88, 0, 96, 0);
        }
        p.rotate(240 / numberOfTicks);
    }
}