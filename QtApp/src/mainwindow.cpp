#include "MainWindow.h"
#include <iostream>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent):
        QMainWindow(parent),
        vLayout(new QVBoxLayout()),
        hLayout(new QHBoxLayout()),
        controlButtonLayout(new QHBoxLayout()),
        controlHLayout(new QHBoxLayout()),
        pwmVLayout(new QVBoxLayout()),
        buckHLayout(new QHBoxLayout()),
        flybackHLayout(new QHBoxLayout()),
        motorRpmWidget("Motor RPM", 4400),
        generatorRpmWidget("Generator RPM", 15400),
        connectionTimer(new QTimer()),
        controlModeLabel("<b>PID Control "),
        controlModeButton(QColor("#111C33"), QColor("#4D7DDD")),
        buckLabel("<b>PWM Convertisseur Moteur</b>"),
        buckSlider(Qt::Horizontal),
        flybackLabel("<b>PWM Convertisseur Charge</b>"),
        flybackSlider(Qt::Horizontal)
{
    mainWidget.setLayout(vLayout);
    hLayout->addWidget(&motorRpmWidget);
    hLayout->addWidget(&generatorRpmWidget);

    vLayout->addLayout(hLayout, 10);

    vLayout->addLayout(controlButtonLayout);
    vLayout->addLayout(controlHLayout, 3);

    controlButtonLayout->addWidget(&controlModeLabel);
    controlButtonLayout->addWidget(&controlModeButton, 0);
    controlButtonLayout->addStretch(10);

    controlModeButton.setHeight(28);

    buckLabel.setFixedWidth(180);
    flybackLabel.setFixedWidth(180);

    connect(&controlModeButton, &SwitchButton::toggled, this, &MainWindow::changeControls);

    controlHLayout->addLayout(pwmVLayout);

    pwmVLayout->addLayout(buckHLayout);
    pwmVLayout->addLayout(flybackHLayout);

    buckHLayout->addWidget(&buckLabel);
    buckHLayout->addWidget(&buckSlider);
    buckHLayout->addWidget(&buckSpinBox);

    flybackHLayout->addWidget(&flybackLabel);
    flybackHLayout->addWidget(&flybackSlider);
    flybackHLayout->addWidget(&flybackSpinBox);

    buckSlider.setRange(0, 100);
    buckSlider.setTickInterval(10);
    buckSlider.setFixedHeight(32);

    buckSpinBox.setRange(0, 100);
    buckSpinBox.setSuffix("%");

    flybackSlider.setRange(0, 100);
    flybackSlider.setTickInterval(10);
    flybackSlider.setFixedHeight(32);

    flybackSpinBox.setRange(0, 100);
    flybackSpinBox.setSuffix("%");

    buckLabel.setObjectName("ControlLabel");
    flybackLabel.setObjectName("ControlLabel");

    controlModeLabel.setObjectName("ControlLabel");

    connect(&buckSlider, &QSlider::valueChanged, &buckSpinBox, &QSpinBox::setValue);
    connect(&buckSlider, &QSlider::valueChanged, this, &MainWindow::motorControlChanged);

    connect(&flybackSlider, &QSlider::valueChanged, &flybackSpinBox, &QSpinBox::setValue);
    connect(&flybackSlider, &QSlider::valueChanged, this, &MainWindow::chargerControlChanged);

    connect(&buckSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), &buckSlider, &QSlider::setValue);
    connect(&flybackSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), &flybackSlider, &QSlider::setValue);

    this->setCentralWidget(&mainWidget);
    this->resize(1020, 400);

    connect(&port, &QSerialPort::readyRead, this, &MainWindow::receiveSerialData);

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

void MainWindow::receiveSerialData()
{
    static const QMap<QString, uint16_t> infoTypeMap = {

    };

    QByteArray msg = port.readAll();
    std::cout << msg.toStdString() << std::endl;

    auto header = msg.left(1); // Change according to real header length

    switch(infoTypeMap.value(header)){

    }
}

void MainWindow::changeControls(bool pidMode)
{
    if(pidMode) {
        buckLabel.setText("<b>Setpoint RPM Moteur</b>");
        flybackLabel.setText("<b>Setpoint Courant de charge</b>");
        buckSlider.setRange(0, 4400);
        buckSpinBox.setRange(0, 4400);
        flybackSlider.setRange(0, 1000);
        flybackSpinBox.setRange(0, 1000);
        buckSpinBox.setSuffix(" RPM");
        flybackSpinBox.setSuffix(" mA");
    }
    else{
        buckLabel.setText("<b>PWM Convertisseur Moteur</b>");
        flybackLabel.setText("<b>PWM Convertisseur Charge</b>");
        buckSlider.setRange(0, 100);
        buckSpinBox.setRange(0, 100);
        flybackSlider.setRange(0, 100);
        flybackSpinBox.setRange(0, 100);
        buckSpinBox.setSuffix("%");
        flybackSpinBox.setSuffix("%");
    }
}

void MainWindow::motorControlChanged(int value)
{
    if(controlModeButton.isChecked()){
        // PID Mode
    }
    else{
        // PWM Mode
    }
}

void MainWindow::chargerControlChanged(int value)
{
    if(controlModeButton.isChecked()){
        // PID Mode
    }
    else{
        // PWM Mode
    }
}

