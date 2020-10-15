#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    vLayout(new QVBoxLayout()),
    btWidget()
{
    connect(&btDeviceFinder, &Bluetooth::DeviceFinder::serviceAvailable, [&](auto &info){ btClient.start(info); });
    connect(&btClient, &Bluetooth::Client::connected, &btWidget, &Bluetooth::StatusWidget::setConnected);
    connect(&btClient, &Bluetooth::Client::disconnected, &btWidget, &Bluetooth::StatusWidget::setDisconnected);

    btDeviceFinder.search("MyEsp32", 20000);

    mainWidget.setLayout(vLayout);
    vLayout->addWidget(&btWidget);
    this->setCentralWidget(&mainWidget);
}

MainWindow::~MainWindow()
{

}

