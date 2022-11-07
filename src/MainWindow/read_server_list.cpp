#include "mainwindow.h"

//读取setting.json文件中保存的服务器列表，并保存到server_list里面
void MainWindow::ReadServerList(){
    if(json.value("server").isArray()){
        server_list.clear();
        QJsonArray serverArray = json.value("server").toArray();
        for(int i = 0; serverArray.size() >0 && i < serverArray.size(); ++i){
            if(serverArray.at(i).isObject()){
                QJsonObject server = serverArray.at(i).toObject();
                //打开对应的服务器文件
                QFile serverFile(config_folder + server.value("server_name").toString() + ".ini");
                if(serverFile.exists()){
                    qDebug() << "调用ReadServerConfigs";
                    ReadServerConfigs(serverFile,server.value("server_name").toString());
                }
                else{
                    QString text = "未找到服务器的配置文件:" + server.value("server_name").toString() + "\n是否删除此服务器？";
                    QMessageBox::StandardButton res =
                            QMessageBox::question(this,"文件丢失",text,QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
                    if(res == QMessageBox::Yes){
                        serverArray.removeAt(i);
                        --i;
                        json["server"] = serverArray;
                        QFile settings_file(config_folder + "settings.json");
                        settings_file.open(QIODevice::WriteOnly);
                        QJsonDocument doc(json);
                        settings_file.write(doc.toJson());
                        settings_file.close();
                    }
                    else{
                        serverFile.open(QIODevice::ReadWrite);
                        serverFile.write("; 此文件由软件自动补全");
                        serverFile.write("; 使用\";\"号来进行注释，\";\"号必须在每行的行首，表示该行是注释 \n");
                        serverFile.close();
                        ReadServerConfigs(serverFile,server.value("server_name").toString());
                    }
                }
            }
        }
        qDebug() << "读取服务器信息完毕";
        emit ReadServerListReady();
    }
}
