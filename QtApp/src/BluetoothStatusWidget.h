//
// Created by Xavier on 2020-10-03.
//

#ifndef QTAPP_BLUETOOTHSTATUSWIDGET_H
#define QTAPP_BLUETOOTHSTATUSWIDGET_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QTimer>
#include "BluetoothData.h"

namespace Bluetooth
{

    class StatusWidget : public QGroupBox
    {
        Q_OBJECT
    public:
        StatusWidget(QWidget *parent = nullptr);

    public slots:

        void setConnected(ClientInformation information);
        void setDisconnected();

        void showUpload(bool active);
        void showDownload(bool active);

    private:
        QTimer uploadTimer;
        QTimer downloadTimer;

        QHBoxLayout *hLayout;
        QHBoxLayout *iconsHLayout;
        QVBoxLayout *textVLayout;
        QVBoxLayout *iconsVLayout;

        QLabel nameLabel;
        QLabel addressLabel;
        QLabel uploadIcon;
        QLabel downloadIcon;
    };

}
#endif //QTAPP_BLUETOOTHSTATUSWIDGET_H
