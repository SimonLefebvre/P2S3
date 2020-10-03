#include "src/MainWindow.h"
#include <iostream>
#include <QApplication>
#include <QFile>

QString loadStyleSheet()
{
    QFile file("styles/stylesheet.css");
    if(file.open(QFile::ReadOnly | QFile::Text))
        return QLatin1String(file.readAll());
    else
        std::cout << "Failed to load application stylesheet" << std::endl;
    return QString();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(loadStyleSheet());

    MainWindow w;
    w.show();

    return a.exec();
}
