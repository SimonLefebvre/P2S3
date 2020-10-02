#ifndef DEVICEFINDER_H
#define DEVICEFINDER_H

#include <QObject>
#include <QtBluetooth/QBluetoothServiceDiscoveryAgent>
#include <memory>
#include <list>
#include <utility>

namespace Bluetooth
{
    class DeviceFinder : public QObject
    {
        Q_OBJECT
    public:
        explicit DeviceFinder(QObject *parent = nullptr);

        void search(QString deviceName, int32_t timeOutMs = -1);

    signals:
        void serviceAvailable(const QBluetoothServiceInfo &devInfo);

    private slots:
        void discovered(const QBluetoothServiceInfo &devInfo);

    private:
        struct Query
        {
            Query(QString deviceName);
            std::unique_ptr<QBluetoothServiceDiscoveryAgent> agent;
            QString deviceName;
            bool operator==(const Query& rhs){ return deviceName == rhs.deviceName; }
            bool operator==(const QString& rhs){ return deviceName == rhs; }
        };

        std::list<Query> queries;
    };
}

#endif // DEVICEFINDER_H
