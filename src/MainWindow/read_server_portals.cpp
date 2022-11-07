#include "mainwindow.h"

void MainWindow::ReadServerPortals(Server &server){
    server.printServer();
    QString fileName = config_folder + server.server_name + ".ini";
    QFile serverFile(fileName);
    if(serverFile.exists()){
        //读取ini文件中的节，忽略[common]节
        QStringList section;
        serverFile.open(QIODevice::ReadOnly);
        QString line;
        while(!serverFile.atEnd()){
            line = serverFile.readLine();
            line.remove("\r\n");
            if(line.size() > 2 && line.at(0) == "[" && line.at(line.size() - 1) == "]" && line != "[common]"){
                line.remove(line.size() - 1,1);
                line.remove(0,1);
                qDebug() << "解析到了节:" << line;
                section.push_back(line);
            }
        }
        //读取到节之后，读取节对应的隧道配置并保存到server的server_portals成员变量里
        server.server_portals.clear();
        for(int i = 0; i < section.size(); ++i){
            Portal portal;
            portal.portal_id = server.server_portals.size();
            portal.portal_name = section.at(i);

            MySettings setting;
            setting.Open(fileName);
            portal.portal_local_IP = setting.GetValues(portal.portal_name,"local_ip");
            portal.portal_local_port = setting.GetValues(portal.portal_name,"local_port").toShort();
            portal.portal_server_port = setting.GetValues(portal.portal_name,"remote_port").toShort();
            portal.portal_type = setting.GetValues(portal.portal_name,"type");
            if(setting.GetValues(portal.portal_name,"use_encryption") == "true")
                portal.portal_encryption = true;
            if(setting.GetValues(portal.portal_name,"use_compression") == "true")
                portal.portal_compression = true;
            portal.portal_bandiwidth = setting.GetValues(portal.portal_name,"bandwidth_limit");

            server.server_portals.push_back(portal);
        }
    }
    else{
        QMessageBox::warning(this,"警告","找不到此服务器的文件：/n" + server.server_name + ".ini /n请刷新服务器列表");
    }
}
