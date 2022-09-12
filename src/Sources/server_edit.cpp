#include "src/Headers/mainwindow.h"
#include "src/Headers/set_server_dialog.h"
#include "src/Headers/server.h"

void MainWindow::EditServer(Server* server_to_edit){
    Server origin_server = *server_to_edit;
    set_server_dialog* ssd = new set_server_dialog(this,server_to_edit,this);
    ssd->setAttribute(Qt::WA_DeleteOnClose);
    //去掉对话框上的问号
    ssd->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    ssd->exec();

    //先判断一下原文件还在不
    if(!QFile(config_folder + origin_server.server_name + ".ini").exists()){
        QMessageBox::warning(this,"文件丢失","服务器文件丢失，请刷新服务器列表");
        return;
    }

    //原文件还在，且对服务器信息有进行修改
    if(*server_to_edit != origin_server){
        //判断是否有和目标名字冲突的服务器文件，并询问用户操作
        if(server_to_edit->server_name != origin_server.server_name &&
                QFile(config_folder + server_to_edit->server_name + ".ini").exists()){
            auto res = QMessageBox::question(this,"目标文件冲突","已存在与新建服务器相冲突的文件：\n" +
                                                server_to_edit->server_name + ".ini。是否进行删除？",
                                  QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
            if (res == QMessageBox::Yes){
                if(QFile(config_folder + server_to_edit->server_name + ".ini").remove()){
                    QMessageBox::information(this,"提示","删除失败！");
                    return;
                }
            }
            if(res == QMessageBox::No){
                QMessageBox::information(this,"提示","无法修改此服务器为目标名字。");
                return;
            }
        }

        //如果修改了服务器名字，对原文件进行重命名
        if(origin_server.server_name != server_to_edit->server_name){
            if(!QFile(config_folder + origin_server.server_name + ".ini").rename(config_folder + server_to_edit->server_name + ".ini")){
                QMessageBox::information(this,"提示","对服务器文件进行重命名失败！");
                return;
            }
        }

        //保存服务器信息
        QSettings editedServerIni(config_folder + server_to_edit->server_name + ".ini",QSettings::IniFormat,this);
        editedServerIni.setValue("common/server_addr",server_to_edit->server_IP);
        editedServerIni.setValue("common/server_port",server_to_edit->server_port);
        editedServerIni.setValue("common/token",server_to_edit->server_token);
        qDebug() << "common/log_file = " << server_to_edit->server_log_file;
        editedServerIni.setValue("common/log_file",server_to_edit->server_log_file);
        editedServerIni.setValue("common/log_level",server_to_edit->server_log_level);
        editedServerIni.setValue("common/log_max_days",server_to_edit->server_log_max_days);
        editedServerIni.sync();

        //把修改后的服务器信息在json里保存一下
        if(json.value("server").isArray()){
            qDebug() << "对服务器" << server_to_edit->server_name << "进行修改";
            QJsonArray serverArray = json.value("server").toArray();
            //新JsonObject对象
            QJsonObject editedServer;
            editedServer.insert("server_name",server_to_edit->server_name);
            //找到旧对象的位置并使用新对象替换
            serverArray[HasThisServer(origin_server.server_name)] = editedServer;
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
