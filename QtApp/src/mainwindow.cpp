#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    vLayout(new QVBoxLayout())
{
    mainWidget.setLayout(vLayout);
    vLayout->addWidget(&rpmWidget);
    this->setCentralWidget(&mainWidget);
}

MainWindow::~MainWindow()
{

}

