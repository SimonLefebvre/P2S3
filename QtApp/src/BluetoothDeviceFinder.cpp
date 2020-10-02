#include "BluetoothDeviceFinder.h"
#include <iostream>
#include <QTimer>

using namespace Bluetooth;

DeviceFinder::DeviceFinder(QObject *parent) :
    QObject(parent)
{}

void DeviceFinder::search(QString deviceName, int32_t timeOutMs)
{
    queries.emplace_back(deviceName);
    auto& query = queries.back();
    connect(query.agent.get(), &QBluetoothServiceDiscoveryAgent::serviceDiscovered,this, &DeviceFinder::discovered);

    if(timeOutMs > 0){
        QTimer::singleShot(timeOutMs, [&] {
            std::cout << "Device \"" << query.deviceName.toStdString() << "\" was not serviceAvailable." << std::endl;
            queries.remove(query);
        });
    }
    query.agent->start();
}

void DeviceFinder::discovered(const QBluetoothServiceInfo &info)
{
    if(queries.erase(std::find(queries.begin(), queries.end(), info.device().name())) != queries.end()){
        std::cout << "Device \"" << info.device().name().toStdString() << "\" serviceAvailable." << std::endl;
        emit serviceAvailable(info);
    }
}

DeviceFinder::Query::Query(QString deviceName) :
    deviceName(deviceName),
    agent(std::make_unique<QBluetoothServiceDiscoveryAgent>())
{}
