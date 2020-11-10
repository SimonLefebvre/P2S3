#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    vLayout(new QVBoxLayout()),
    rpmWidget("Motor RPM", 4400)
{
    mainWidget.setLayout(vLayout);
    vLayout->addWidget(&rpmWidget);
    this->setCentralWidget(&mainWidget);

    this->resize(510, 400);
}

MainWindow::~MainWindow()
{

}

