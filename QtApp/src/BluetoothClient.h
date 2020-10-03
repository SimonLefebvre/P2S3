#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtBluetooth/QBluetoothServiceInfo>
#include <QtBluetooth/QBluetoothSocket>
#include "BluetoothData.h"

namespace Bluetooth
{
    class Client : public QObject
    {
        Q_OBJECT
    public:
        explicit Client(QObject *parent = nullptr);
        ~Client();

        void start(const QBluetoothServiceInfo &info);

        void sendData(const QByteArray &data);

    signals:
        void dataReceived(const QByteArray &data);

        void connected(ClientInformation information);
        void disconnected();

    private slots:

        void read();

    private:
        std::unique_ptr<QBluetoothSocket> socket;
    };

}

#endif // CLIENT_H
