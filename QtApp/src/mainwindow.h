#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSerialPort>
#include <QTimer>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>

#include "CircularGaugeWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void attemptSerialConnection();

    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;

    QHBoxLayout *controlHLayout;

    QVBoxLayout *pwmVLayout;

    QHBoxLayout *buckHLayout;
    QHBoxLayout *flybackHLayout;

    QWidget mainWidget;

    CircularGaugeWidget motorRpmWidget;
    CircularGaugeWidget generatorRpmWidget;

    QSerialPort port;
    QTimer *connectionTimer;

    QLabel buckLabel;
    QSlider buckPwmSlider;
    QSpinBox buckPwmSpinBox;

    QLabel flybackLabel;
    QSlider flybackPwmSlider;
    QSpinBox flybackPwmSpinBox;


};
#endif // MAINWINDOW_H
