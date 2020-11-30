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
#include "SwitchButton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void attemptSerialConnection();

    void changeControls(bool pidMode);

    void motorValueChanged(int value);

    void chargerValueChanged(int value);

    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;

    QHBoxLayout *controlButtonLayout;
    QHBoxLayout *controlHLayout;

    QVBoxLayout *pwmVLayout;

    QHBoxLayout *buckHLayout;
    QHBoxLayout *flybackHLayout;

    QWidget mainWidget;

    CircularGaugeWidget motorRpmWidget;
    CircularGaugeWidget generatorRpmWidget;

    QSerialPort port;
    QTimer *connectionTimer;

    QLabel controlModeLabel;
    SwitchButton controlModeButton;

    QLabel buckLabel;
    QSlider buckSlider;
    QSpinBox buckSpinBox;

    QLabel flybackLabel;
    QSlider flybackSlider;
    QSpinBox flybackSpinBox;


};
#endif // MAINWINDOW_H
