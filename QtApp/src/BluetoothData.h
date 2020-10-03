//
// Created by Xavier on 2020-10-03.
//

#ifndef QTAPP_BLUETOOTHDATA_H
#define QTAPP_BLUETOOTHDATA_H

#include <QString>

namespace Bluetooth
{
    struct ClientInformation
    {
        QString name;
        QString address;
        int16_t rssi;
    };
}

#endif //QTAPP_BLUETOOTHDATA_H
