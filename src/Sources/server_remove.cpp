#include "src/Headers/mainwindow.h"

void MainWindow::RemoveServer(Server* server_to_remove){
    QString fileName = config_folder + server_to_remove->server_name + ".ini";
    QFile file(fileName);
    if(file.exists()){
        qDebug() << "该服务器配置文件存在，进行删除";
        if(file.remove()){
            QMessageBox::about(this,"提示信息",server_to_remove->server_name + "删除成功！");
            }
        else{
            QMessageBox::warning(this,"提示信息",server_to_remove->server_name + "删除失败！");
        }
    }
    //把在json里也对服务器进行删除
    if(json.value("server").isArray()){
                qDebug() << "对服务器" << server_to_remove->server_name << "进行删除";
                QJsonArray serverArray = json.value("server").toArray();
                //遍历找到要删除的对象的位置
                serverArray.removeAt(HasThisServer(server_to_remove->server_name));
                json["server"] = serverArray;
                QFile settings_file(config_folder + "settings.json");
                settings_file.open(QIODevice::WriteOnly);
                QJsonDocument doc(json);
                settings_file.write(doc.toJson());
                settings_file.close();
            }
    ReadServerList();
}
