#include "MainWindow.h"
#include <iostream>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent):
        QMainWindow(parent),
        vLayout(new QVBoxLayout()),
        hLayout(new QHBoxLayout()),
        motorRpmWidget("Motor RPM", 4400),
        generatorRpmWidget("Generator RPM", 15400),
        connectionTimer(new QTimer())
{
    mainWidget.setLayout(hLayout);
    hLayout->addWidget(&motorRpmWidget);
    hLayout->addWidget(&generatorRpmWidget);
    this->setCentralWidget(&mainWidget);

    this->resize(1020, 400);

    motorRpmWidget.setValue(4400);

    connectionTimer->setInterval(1000);
    connect(connectionTimer, &QTimer::timeout, this, &MainWindow::attemptSerialConnection);
    connectionTimer->start();
}

MainWindow::~MainWindow()
{

}

void MainWindow::attemptSerialConnection()
{
    auto ports = QSerialPortInfo::availablePorts();

    if(!port.isOpen()) {
        for (auto &it : ports) {
            if (it.description() == "Silicon Labs CP210x USB to UART Bridge") {
                port.setPort(it);
                port.setBaudRate(115200);
                port.setDataBits(QSerialPort::Data8);
                port.setStopBits(QSerialPort::OneStop);
                if (port.open(QIODevice::ReadWrite)) {
                    connect(&port, &QSerialPort::readyRead, [&]{ std::cout << port.readAll().toStdString() << std::endl;});
                    std::cout << "Successfully connected to serial port " << it.portName().toStdString() << std::endl;
                }
            }
        }
    }
    else{
        for(auto& it : ports){
            if(it.portName() == port.portName())
                return;
        }
        port.close();
        std::cout << "Serial port disconnected" << std::endl;
    }
}

