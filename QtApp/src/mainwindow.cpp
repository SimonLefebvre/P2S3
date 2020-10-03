#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setCentralWidget(&listWidget);

    connect(&btDeviceFinder, &Bluetooth::DeviceFinder::serviceAvailable,
            [&](auto &info){
        listWidget.addItem(info.device().name());
        client.start(info);
    });

    btDeviceFinder.search("Jabra Elite 75t", 20000);
}

MainWindow::~MainWindow()
{

}

