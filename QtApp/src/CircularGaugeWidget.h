//
// Created by Xavier on 2020-11-08.
//

#ifndef QTAPP_CIRCULARGAUGEWIDGET_H
#define QTAPP_CIRCULARGAUGEWIDGET_H

#include <QWidget>
#include <QColor>

class CircularGaugeWidget : public QWidget
{
    Q_OBJECT

public:
    CircularGaugeWidget(QString name, uint32_t maxValue,  QWidget *parent = nullptr);

    void setNeedle(uint32_t value);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void adjustFontSize(QString strToFit, uint16_t pixelSpace);

    QFont font = {"Bookman Old Style", 4, QFont::Bold};
    const QColor needleColor = {5, 8, 33};
    const uint16_t numberOfTicks = 12;
    const uint32_t maxValue = 4400;
    const QString name;

    float needleAngle = -110.0f;
};


#endif //QTAPP_CIRCULARGAUGEWIDGET_H
