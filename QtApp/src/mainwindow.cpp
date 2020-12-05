#include "MainWindow.h"
#include <iostream>
#include <QSerialPortInfo>
#include <QJsonDocument>
#include <QJsonObject>

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

    controlModeButton.setHeight(32);

    QFontMetrics fm(buckLabel.font());
    buckLabel.setFixedWidth(fm.horizontalAdvance(flybackLabel.text()));
    flybackLabel.setFixedWidth(fm.horizontalAdvance(flybackLabel.text()));

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
    buckSlider.setTracking(false);

    buckSpinBox.setRange(0, 100);
    buckSpinBox.setSuffix("%");

    flybackSlider.setRange(0, 100);
    flybackSlider.setTickInterval(10);
    flybackSlider.setFixedHeight(32);
    flybackSlider.setTracking(false);

    flybackSpinBox.setRange(0, 100);
    flybackSpinBox.setSuffix("%");

    connect(&buckSlider, &QSlider::valueChanged, &buckSpinBox, &QSpinBox::setValue);
    connect(&buckSlider, &QSlider::valueChanged, this, &MainWindow::motorControlChanged);

    connect(&flybackSlider, &QSlider::valueChanged, &flybackSpinBox, &QSpinBox::setValue);
    connect(&flybackSlider, &QSlider::valueChanged, this, &MainWindow::chargerControlChanged);

    connect(&buckSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), &buckSlider, &QSlider::setValue);
    connect(&flybackSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), &flybackSlider, &QSlider::setValue);

    this->setCentralWidget(&mainWidget);
    this->resize(1520, 700);

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
                    buckSlider.setValue(0);
                    flybackSlider.setValue(0);
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
    enum InfoId{
        Motor_RPM = 1,
        Generator_RPM,
        Buck_Temperature,
        Flyback_Temperature,
        Buck_Voltage,
        Flyback_Voltage
    };
    while(port.bytesAvailable()) {
        auto c = port.read(1);
        if(c.front() != '\0') {
            msg.append(c);
        }
        else{
            std::cout << msg.toStdString() << std::endl;
            uint8_t id = static_cast<uint8_t>(msg.front()) - 0x30;
            msg.remove(0, 1);
            switch(id)
            {
                case Motor_RPM:
                    motorRpmWidget.setValue(QString(msg).toUInt());
                    break;
                case Generator_RPM:
                    generatorRpmWidget.setValue(QString(msg).toUInt());
                    break;
                case Buck_Temperature:
                    // TODO
                    break;
                case Flyback_Temperature:
                    // TODO
                    break;
                case Buck_Voltage:
                    // TODO
                    break;
                case Flyback_Voltage:
                    // TODO
                    break;
            }
            msg.clear();
        }
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
        QJsonObject obj
                {
                        {"Vitesse Moteur", value}
                };
        QJsonDocument doc(obj);
        port.write(doc.toJson());
    }
    else{
        // PWM Mode
        QString str = 'a' + QString::number(value) + '\0';

        port.write(str.toUtf8());

        std::cout << "String sent: " << str.toStdString() << std::endl;
    }
}

void MainWindow::chargerControlChanged(int value)
{
    if(controlModeButton.isChecked()){
        // PID Mode
    }
    else{
        // PWM Mode
        QString str = 'b' + QString::number(value) + '\0';

        port.write(str.toUtf8());

        std::cout << "String sent: " << str.toStdString() << std::endl;
    }
}

