#include "src/Headers/mainwindow.h"

void MainWindow::UTF8toGBK(QFile &file){
    //用UTF8读取全部内容转为GBK
    file.open(QIODevice::ReadOnly);
    QByteArray all = file.readAll();
    QByteArray data = QTextCodec::codecForName("GBK")->fromUnicode(QTextCodec::codecForName("UTF8")->toUnicode(all));
    file.close();
    //覆盖写入
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();
}

void MainWindow::GBKtoUTF8(QFile &file){
    //用GBK读取全部内容转为UTF8
    file.open(QIODevice::ReadOnly);
    QByteArray all = file.readAll();
    QByteArray data = QTextCodec::codecForName("UTF8")->fromUnicode(QTextCodec::codecForName("GBK")->toUnicode(all));
    file.close();
    //覆盖写入
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();
}
