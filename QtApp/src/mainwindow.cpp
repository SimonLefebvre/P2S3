#include "MainWindow.h"
#include <iostream>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent):
        QMainWindow(parent),
        vLayout(new QVBoxLayout()),
        hLayout(new QHBoxLayout()),
        controlHLayout(new QHBoxLayout()),
        pwmVLayout(new QVBoxLayout()),
        buckHLayout(new QHBoxLayout()),
        flybackHLayout(new QHBoxLayout()),
        motorRpmWidget("Motor RPM", 4400),
        generatorRpmWidget("Generator RPM", 15400),
        connectionTimer(new QTimer()),
        buckLabel("<b>PWM Convertisseur Moteur</b>"),
        buckPwmSlider(Qt::Horizontal),
        flybackLabel("<b>PWM Convertisseur Charge</b>"),
        flybackPwmSlider(Qt::Horizontal)
{
    mainWidget.setLayout(vLayout);
    hLayout->addWidget(&motorRpmWidget);
    hLayout->addWidget(&generatorRpmWidget);

    vLayout->addLayout(hLayout, 10);
    vLayout->addLayout(controlHLayout, 3);

    controlHLayout->addLayout(pwmVLayout);

    pwmVLayout->addLayout(buckHLayout);
    pwmVLayout->addLayout(flybackHLayout);

    buckHLayout->addWidget(&buckLabel);
    buckHLayout->addWidget(&buckPwmSlider);
    buckHLayout->addWidget(&buckPwmSpinBox);

    flybackHLayout->addWidget(&flybackLabel);
    flybackHLayout->addWidget(&flybackPwmSlider);
    flybackHLayout->addWidget(&flybackPwmSpinBox);

    buckPwmSlider.setRange(0, 100);
    buckPwmSlider.setTickInterval(1);

    buckPwmSpinBox.setRange(0, 100);

    flybackPwmSlider.setRange(0, 100);
    flybackPwmSlider.setTickInterval(1);

    flybackPwmSpinBox.setRange(0, 100);

    connect(&buckPwmSlider, &QSlider::valueChanged, &buckPwmSpinBox, &QSpinBox::setValue);
    connect(&flybackPwmSlider, &QSlider::valueChanged, &flybackPwmSpinBox, &QSpinBox::setValue);

    connect(&buckPwmSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), &buckPwmSlider, &QSlider::setValue);
    connect(&flybackPwmSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), &flybackPwmSlider, &QSlider::setValue);

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

