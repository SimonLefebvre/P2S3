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

    QColor hourColor = {5, 8, 33};
    QString name;
    const uint16_t numberOfTicks = 12;
    const uint32_t maxValue = 4400;

    float needleAngle = -110.0f;
};


#endif //QTAPP_CIRCULARGAUGEWIDGET_H
