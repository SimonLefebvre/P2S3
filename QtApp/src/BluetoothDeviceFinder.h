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
        void onDiscovery(const QBluetoothServiceInfo &info);

    private:
        std::unique_ptr<QBluetoothServiceDiscoveryAgent> agent;

        QList<QString> pending;
    };
}

#endif // DEVICEFINDER_H
