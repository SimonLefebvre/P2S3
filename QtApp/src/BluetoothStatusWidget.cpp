//
// Created by Xavier on 2020-10-03.
//

#include "BluetoothStatusWidget.h"

using namespace Bluetooth;

StatusWidget::StatusWidget(QWidget *parent) :
        QGroupBox("Connexion Bluetooth"),
        hLayout(new QHBoxLayout()),
        iconsHLayout(new QHBoxLayout()),
        textVLayout(new QVBoxLayout()),
        iconsVLayout(new QVBoxLayout())
{
    hLayout->addLayout(textVLayout);
    hLayout->addLayout(iconsVLayout);
    this->setLayout(hLayout);

    textVLayout->addWidget(&nameLabel);
    textVLayout->addWidget(&addressLabel);

    iconsVLayout->addWidget(&signalStrengthIcon);
    iconsVLayout->addLayout(iconsHLayout);
    iconsHLayout->addWidget(&downloadIcon);
    iconsHLayout->addWidget(&uploadIcon);

    downloadTimer.setInterval(1000);
    uploadTimer.setInterval(1000);
    connect(&downloadTimer, &QTimer::timeout, [&]{ showDownload(false); });
    connect(&uploadTimer, &QTimer::timeout, [&]{ showDownload(true); });

    setDisconnected();
    this->setFixedSize(200, 100);
}

void StatusWidget::setConnected(ClientInformation clientInfo)
{
    setObjectName("StatusGroupBoxGreen");
    setStyleSheet(this->styleSheet());

    nameLabel.setText(clientInfo.name);
    addressLabel.setText(clientInfo.address);
    // TODO: set signal strength icon

}

void StatusWidget::setDisconnected()
{
    setObjectName("StatusGroupBoxRed");
    setStyleSheet(this->styleSheet());
}

void StatusWidget::showUpload(bool active)
{
    if(active){
        //uploadIcon.setPixmap();
    }
    else{

    }
}

void Bluetooth::StatusWidget::showDownload(bool active)
{
    if(active){
        //downloadIcon.setPixmap();
    }
    else{

    }
}
