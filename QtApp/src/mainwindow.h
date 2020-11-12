#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "CircularGaugeWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;

    QWidget mainWidget;

    CircularGaugeWidget motorRpmWidget;
    CircularGaugeWidget generatorRpmWidget;

};
#endif // MAINWINDOW_H
