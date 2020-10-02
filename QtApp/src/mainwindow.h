#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BluetoothDeviceFinder.h"
#include "BluetoothClient.h"
#include <QListWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    Bluetooth::DeviceFinder btDeviceFinder;
    Bluetooth::Client client;

    QListWidget listWidget;
};
#endif // MAINWINDOW_H
