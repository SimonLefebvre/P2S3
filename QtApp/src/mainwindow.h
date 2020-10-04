#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BluetoothDeviceFinder.h"
#include "BluetoothClient.h"
#include "BluetoothStatusWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QVBoxLayout *vLayout;

    QWidget mainWidget;

    Bluetooth::DeviceFinder btDeviceFinder;
    Bluetooth::Client btClient;
    Bluetooth::StatusWidget btWidget;
};
#endif // MAINWINDOW_H
