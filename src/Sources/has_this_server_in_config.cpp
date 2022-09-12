#include "src/Headers/mainwindow.h"

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
