#include "src/Headers/mainwindow.h"

//把ini里面的文件配置读取Server类里
void MainWindow::ReadServerConfigs(QFile &serverfile, QString servername){
    serverfile.open(QIODevice::ReadWrite);
    Server thisServer;
    QSettings thisServerIni(serverfile.fileName(),QSettings::IniFormat,this);
    //ID = 当前服务器列表的数量
    thisServer.server_id = server_list.size();
    //名称
    thisServer.server_name = servername;
    //IP
    thisServer.server_IP = thisServerIni.value("common/server_addr","none").toString();
    //端口
    thisServer.server_port = thisServerIni.value("common/server_port","0").toString().toUShort();
    //token
    thisServer.server_token = thisServerIni.value("common/token","none").toString();
    //log
    thisServer.server_log_file = thisServerIni.value("common/log_file","").toString();
    thisServer.server_log_level = thisServerIni.value("common/log_level","").toString();
    thisServer.server_log_max_days = thisServerIni.value("common/log_max_days","0").toString().toInt();
    //读取隧道
    ReadServerPortals(thisServer);

    //把读取配置完毕的server放进server_list里
    server_list.push_back(thisServer);
}
