#include "BluetoothClient.h"
#include <iostream>
#include <QBluetoothDeviceInfo>

using namespace Bluetooth;

static const QMap<QBluetoothSocket::SocketState, std::string> clientStateDescriptor
{
    {QBluetoothSocket::UnconnectedState, "Disconnected"},
    {QBluetoothSocket::ServiceLookupState, "Querying connection parameters"},
    {QBluetoothSocket::ConnectingState, "Connecting"},
    {QBluetoothSocket::ConnectedState, "Connected successfully"},
    {QBluetoothSocket::BoundState, "Bound to a local address & port"},
    {QBluetoothSocket::ClosingState, "Closing once pending data is sent"},
    {QBluetoothSocket::ListeningState, "Listening to incoming connections"},
};

Client::Client(QObject *parent) : QObject(parent)
{

}

Client::~Client()
{
    if(socket && socket->isOpen())
        socket->close();
}

void Client::start(const QBluetoothServiceInfo &info)
{
    if(socket && socket->isOpen())
        socket->close();

    socket = std::make_unique<QBluetoothSocket>(QBluetoothServiceInfo::RfcommProtocol);

    connect(socket.get(), &QBluetoothSocket::readyRead, this, &Client::read);
    connect(socket.get(), &QBluetoothSocket::connected, [&]{
        emit connected({info.device().name(), info.device().address().toString(), info.device().rssi()});
    });
    connect(socket.get(), &QBluetoothSocket::disconnected, this, &Client::disconnected);
    connect(socket.get(), &QBluetoothSocket::stateChanged, [&](auto state){
        std::cout << "BT Client state changed: " << clientStateDescriptor.value(state) << std::endl;});
    socket->connectToService(info);
}

void Client::read()
{
    emit dataReceived(socket->readAll());
}

void Client::sendData(const QByteArray& data)
{
    socket->write(data);
}
