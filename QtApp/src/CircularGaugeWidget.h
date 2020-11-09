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
    CircularGaugeWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:

    QColor hourColor = {5, 8, 33};

    const int numberOfTicks = 20;
    const int maxValue = 4000;
};


#endif //QTAPP_CIRCULARGAUGEWIDGET_H
