#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent):
        QMainWindow(parent),
        vLayout(new QVBoxLayout()),
        hLayout(new QHBoxLayout()),
        motorRpmWidget("Motor RPM", 4400),
        generatorRpmWidget("Generator RPM", 15400)
{
    mainWidget.setLayout(hLayout);
    hLayout->addWidget(&motorRpmWidget);
    hLayout->addWidget(&generatorRpmWidget);
    this->setCentralWidget(&mainWidget);

    this->resize(1020, 400);

    motorRpmWidget.setValue(4000);
}

MainWindow::~MainWindow()
{

}

