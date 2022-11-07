//用于找出setting.ini是否存在目标服务器

#include "mainwindow.h"

int MainWindow::HasThisServer(QString serverName){
    QJsonArray ServerList = json.value("server").toArray();
    //遍历找是否有重名冲突
    for(int i = 0; i < ServerList.size(); ++i){
        if(ServerList.at(i).toObject().value("server_name") == serverName){
            return i;
        }
    }
    return -1;
}
