#include "src/Headers/mainwindow.h"
#include "src/Headers/set_server_dialog.h"

void MainWindow::AddServer(){
    Server new_server;
    set_server_dialog* ssd = new set_server_dialog(this,&new_server,this);
    ssd->setAttribute(Qt::WA_DeleteOnClose);
    //去掉对话框上的问号
    ssd->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    ssd->exec();
    //如果有新服务器的数据返回，则对新服务器的配置文件进行操作
    if(!new_server.isEmpty()){
        new_server.server_id = server_list.size();
        QString fileName = config_folder + new_server.server_name + ".ini";
        QFile file(fileName);
        QSettings newServerIni(fileName,QSettings::IniFormat,this);

        //判断是否存在目标文件
        if(file.exists()){
            auto res = QMessageBox::question(this,"目标文件冲突","已存在与新建服务器相冲突的文件：\n" +
                                                new_server.server_name + ".ini。是否进行删除？",
                                  QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
            if(res == QMessageBox::Yes){
                if(!file.remove()) {
                    QMessageBox::information(this,"提示","删除失败！");
                    return;
                }
            }
            else if(res == QMessageBox::No){
                return;
            }
        }

        //创建文件并保存信息
        WritePrivateProfileStringW(TEXT("common"),NULL,NULL,fileName.toStdWString().c_str());

        newServerIni.setValue("common/server_addr",new_server.server_IP);
        newServerIni.setValue("common/server_port",new_server.server_port);
        newServerIni.setValue("common/token",new_server.server_token);
        newServerIni.setValue("common/log_file",new_server.server_log_file);
        newServerIni.setValue("common/log_level",new_server.server_log_level);
        newServerIni.setValue("common/log_max_days",new_server.server_log_max_days);
        newServerIni.sync();

        //把新建的服务器信息保存在json
        if(json.value("server").isArray()){
            QJsonArray serverArray = json.value("server").toArray();
            QJsonObject newServer;
            newServer.insert("server_name",new_server.server_name);
            serverArray.push_back(newServer);
            json["server"] = serverArray;
            QFile settings_file(config_folder + "settings.json");
            settings_file.open(QIODevice::WriteOnly);
            QJsonDocument doc(json);
            settings_file.write(doc.toJson());
            settings_file.close();
        }
        ReadServerList();
    }
}
