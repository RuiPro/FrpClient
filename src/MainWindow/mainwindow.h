#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTextStream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QThread>
#include <QSettings>
#include <QStyledItemDelegate>
#include <QTextCodec>
#include <QProcess>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include "src/MyClass/mylabel/mylabel.h"
#include "src/MyClass/server/server.h"
#include "src/MyClass/portal/portal.h"
#include "src/MyClass/mysettings/mysettings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void FileInit();                    //初始化文件和文件夹
    void WindowInit(Ui::MainWindow *ui);//初始化窗口
    void ReadConfigs();                 //读取setting.ini里的设置

    void ReadServerList();              //读取服务器列表
    void ReadServerConfigs(QFile &serverfile, QString servername);  //读取服务器文件
    void ReadServerPortals(Server &server); //读取服务器相关的隧道

    void AddServer();                   //添加服务器
    void EditServer(Server* server_to_edit);    //修改服务器
    void RemoveServer(Server* server_to_remove);        //移除服务器
    int HasThisServer(QString serverName);      //判断服务器是否在设置中,有则返回在json数组中的位置，无则返回-1

    //隧道设置
    void AddPortal(Server * server_to_add_in);
    void EditPortal(Server * server_to_edit, Portal * portal_to_edit);
    void RemovePortal(Server * server_to_edit, Portal * portal_to_remove);

    void FrpcProcess(Ui::MainWindow *ui);

    //设置
    void SetFrpcPath(); //设置Frpc客户端的位置
    void SetOutPutFont(); //设置输出窗口的字体

    //需全局使用的成员变量
    QJsonObject json;           //读取的设置文件的内容
    QList<Server> server_list;  //服务器列表
    QString config_folder = QCoreApplication::applicationDirPath() + "/config/";    //此软件的设置路径
    QString frpcPath;
    QProcess * frpc = nullptr;
    int current_Server_index = 0, sizeof_server_list = 0;

signals:
    void ReadServerListReady();
    void ReadConfigsReady();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
