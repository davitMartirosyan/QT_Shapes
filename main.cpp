#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "parser/Parser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = MainWindow::GetInstance();
    w->show();

    auto retValue = a.exec();

    delete w;
    return retValue;
}
