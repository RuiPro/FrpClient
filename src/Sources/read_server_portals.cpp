#include "src/Headers/mainwindow.h"

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

            QFile file(fileName);
            UTF8toGBK(file);
            TCHAR buf[30] = {0};
            GetPrivateProfileString(section.at(i).toStdWString().c_str(),
                                    TEXT("local_ip"),
                                    TEXT("空IP"),
                                    buf,30,fileName.toStdWString().c_str());
            portal.portal_local_IP = QString::fromStdWString(buf);
            buf[30] = {0};
            GetPrivateProfileString(section.at(i).toStdWString().c_str(),
                                    TEXT("local_port"),
                                    TEXT("空本地端口"),
                                    buf,30,fileName.toStdWString().c_str());
            portal.portal_local_port = QString::fromStdWString(buf).toUShort();
            buf[30] = {0};
            GetPrivateProfileString(section.at(i).toStdWString().c_str(),
                                    TEXT("remote_port"),
                                    TEXT("空服务器端口"),
                                    buf,30,fileName.toStdWString().c_str());
            portal.portal_server_port = QString::fromStdWString(buf).toUShort();
            buf[30] = {0};
            GetPrivateProfileString(section.at(i).toStdWString().c_str(),
                                    TEXT("type"),
                                    TEXT("未知类型!"),
                                    buf,30,fileName.toStdWString().c_str());
            portal.portal_type = QString::fromStdWString(buf);
            buf[30] = {0};
            GetPrivateProfileString(section.at(i).toStdWString().c_str(),
                                    TEXT("use_encryption"),
                                    TEXT("--"),
                                    buf,30,fileName.toStdWString().c_str());
            portal.portal_encryption = (QString::fromStdWString(buf) == "true");
            buf[30] = {0};
            GetPrivateProfileString(section.at(i).toStdWString().c_str(),
                                    TEXT("use_compression"),
                                    TEXT("--"),
                                    buf,30,fileName.toStdWString().c_str());
            portal.portal_compression = (QString::fromStdWString(buf) == "true");
            buf[30] = {0};
            GetPrivateProfileString(section.at(i).toStdWString().c_str(),
                                    TEXT("bandwidth_limit"),
                                    TEXT("--"),
                                    buf,30,fileName.toStdWString().c_str());
            portal.portal_bandiwidth = QString::fromStdWString(buf);

            GBKtoUTF8(file);

            server.server_portals.push_back(portal);
        }
    }
    else{
        QMessageBox::warning(this,"警告","找不到此服务器的文件：/n" + server.server_name + ".ini /n请刷新服务器列表");
    }
}
