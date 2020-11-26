#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSerialPort>
#include <QTimer>

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

    QWidget mainWidget;

    CircularGaugeWidget motorRpmWidget;
    CircularGaugeWidget generatorRpmWidget;

    QSerialPort port;
    QTimer *connectionTimer;

};
#endif // MAINWINDOW_H
