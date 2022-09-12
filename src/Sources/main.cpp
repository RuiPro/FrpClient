#include "src/Headers/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.FileInit();
    w.show();
    w.ReadConfigs();
    w.ReadServerList();

    return a.exec();
}
