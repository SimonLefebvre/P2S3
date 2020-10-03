#include "BluetoothDeviceFinder.h"
#include <iostream>
#include <QTimer>

using namespace Bluetooth;

DeviceFinder::DeviceFinder(QObject *parent) :
    QObject(parent),
    agent(std::make_unique<QBluetoothServiceDiscoveryAgent>())
{
    connect(agent.get(), &QBluetoothServiceDiscoveryAgent::serviceDiscovered,this, &DeviceFinder::onDiscovery);
}

void DeviceFinder::search(QString deviceName, int32_t timeOutMs)
{
    for(auto &it : agent->discoveredServices()){
        if(it.device().name() == deviceName) {
            emit serviceAvailable(it);
            return;
        }
    }
    pending.append(deviceName);

    if(timeOutMs > 0){
        QTimer::singleShot(timeOutMs, [&, deviceName] {
            if(pending.contains(deviceName)){
                std::cout << "Device \"" << deviceName.toStdString() << "\" was not found." << std::endl;
                pending.removeOne(deviceName);
            }
        });
    }
    agent->start();
}

void DeviceFinder::onDiscovery(const QBluetoothServiceInfo &info)
{
    for(auto it : pending){
        if(it == info.device().name()){
            std::cout << "Device \"" << it.toStdString() << "\" found." << std::endl;
            emit serviceAvailable(info);
            pending.removeOne(it);
        }
    }
}