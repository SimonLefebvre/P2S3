//
// Created by Xavier on 2020-11-08.
//

#include "CircularGaugeWidget.h"

#include <QPainter>

CircularGaugeWidget::CircularGaugeWidget(QString name, uint32_t maxValue, QWidget *parent) :
    QWidget(parent),
    name(std::move(name)),
    maxValue(maxValue),
    animation(std::make_unique<QVariantAnimation>())
{
    animation->setEasingCurve(QEasingCurve(QEasingCurve::Type::InOutCubic));

    connect(animation.get(), &QVariantAnimation::valueChanged,
            [&](const QVariant &value){ setNeedle(value.toUInt());});
}

void CircularGaugeWidget::paintEvent(QPaintEvent *)
{
    static const QPoint needlePts[3] = {
        {4, 0},
        {-4, 0},
        {0, -95}
    };

    double scaleRatio = (width() * 0.5 < height() * 0.68) ? width() / 1.36 : height();

    adjustFontSize(QString::number(maxValue), 38);

    QPainter p(this);
    p.setFont(font);
    QFontMetrics fm(p.font());

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

    uint32_t adjustedMax = maxValue * numberOfTicks / (numberOfTicks - 1);
    for (int i = 0; i < 360; i ++) {
        if(i % (240 / numberOfTicks) == 0) {
            if (i <= 90 || i >= 330) {  // Draw numbers left side of quadrant
                p.setPen(Qt::black);
                p.drawText(-(100 + fm.horizontalAdvance(QString::number(((i + 20) % 360) * adjustedMax / 240))), (fm.ascent() / 2) - 1,
                           QString::number(((i + 20) % 360) * adjustedMax / 240));
            }
            if (i < 30 || i > 270) {    // Draw numbers right side of quadrant
                p.setPen(Qt::black);
                p.drawText(100, (fm.ascent() / 2) - 1, QString::number(((i + 200) % 360) * adjustedMax / 240));
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

    p.setPen(needleColor);
    p.drawText(-fm.horizontalAdvance(name) / 2, 50, name);
    p.setBrush(QColor(0, 0, 0, 0));
    p.drawChord(-140, -140, 140 * 2, 140 * 2, -28 * 16, 236 * 16);
}

void CircularGaugeWidget::setValue(uint32_t value)
{
    animation->setDuration(static_cast<int32_t>(value * 1000 / maxValue));
    animation->setStartValue(currentValue);
    animation->setEndValue(value);
    animation->start();
}

void CircularGaugeWidget::setNeedle(uint32_t value)
{
    currentValue = value;
    needleAngle = ((static_cast<float>(value * 220) / maxValue) - 110);
    repaint();
}

void CircularGaugeWidget::adjustFontSize(QString strToFit, uint16_t pixelSpace)
{
    for(;;)
    {
        QFontMetrics fm(font);
        if(fm.horizontalAdvance(strToFit) < pixelSpace && font.pointSize() < 10) {
            font.setPointSize(font.pointSize() + 1);
        }
        else{
            font.setPointSize(font.pointSize() - 1);
            return;
        }
    }
}
