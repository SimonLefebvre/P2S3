#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

#include "CircularGaugeWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QVBoxLayout *vLayout;

    QWidget mainWidget;

    CircularGaugeWidget rpmWidget;

};
#endif // MAINWINDOW_H
