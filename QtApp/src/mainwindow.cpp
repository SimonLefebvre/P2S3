#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    vLayout(new QVBoxLayout()),
    btWidget()
{
    connect(&btDeviceFinder, &Bluetooth::DeviceFinder::serviceAvailable,
            [&](auto &info){
        listWidget.addItem(info.device().name());
        btClient.start(info);
    });

    btDeviceFinder.search("Jabra Elite 75t", 20000);

    connect(&btClient, &Bluetooth::Client::connected, &btWidget, &Bluetooth::StatusWidget::setConnected);
    connect(&btClient, &Bluetooth::Client::disconnected, &btWidget, &Bluetooth::StatusWidget::setDisconnected);

    mainWidget.setLayout(vLayout);
    vLayout->addWidget(&listWidget);
    vLayout->addWidget(&btWidget);
    this->setCentralWidget(&mainWidget);
}

MainWindow::~MainWindow()
{

}

