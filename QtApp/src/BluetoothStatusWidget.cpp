//
// Created by Xavier on 2020-10-03.
//

#include "BluetoothStatusWidget.h"
#include <QStyle>
#include <iostream>

using namespace Bluetooth;

StatusWidget::StatusWidget(QWidget *parent) :
        QGroupBox("Connexion Bluetooth", parent),
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

    connect(&downloadTimer, &QTimer::timeout, [&]{ showDownload(false); });
    connect(&uploadTimer, &QTimer::timeout, [&]{ showUpload(false); });

    setDisconnected();
}

void StatusWidget::setConnected(ClientInformation clientInfo)
{
    setObjectName("StatusGroupBoxGreen");
    style()->unpolish(this);
    style()->polish(this);

    nameLabel.setText(clientInfo.name);
    addressLabel.setText(clientInfo.address);
}

void StatusWidget::setDisconnected()
{
    setObjectName("StatusGroupBoxRed");
    style()->unpolish(this);
    style()->polish(this);

    nameLabel.setText("Not connected");
    addressLabel.setText("");
}

void StatusWidget::showUpload(bool active)
{
    if(active){
        //uploadIcon.setPixmap();
        uploadTimer.start(1000);
    }
    else{

    }
}

void Bluetooth::StatusWidget::showDownload(bool active)
{
    if(active){
        //downloadIcon.setPixmap();
        downloadTimer.start(1000);
    }
    else{

    }
}
