#include "src/Headers/mainwindow.h"

void MainWindow::FileInit(){
    //创建config和logs文件夹
    if(!QDir(config_folder).exists()){
        if(QDir().mkdir(config_folder)){
            qDebug() << "config文件夹已创建";
        }
        else{
            QMessageBox::warning(this,"警告","config文件夹创建失败！");
        }
    }
    if(!QDir(QCoreApplication::applicationDirPath() + "/logs/").exists()){
        if(QDir().mkdir(QCoreApplication::applicationDirPath() + "/logs/")){
            qDebug() << "logs文件夹已创建";
        }
        else{
            QMessageBox::warning(this,"警告","logs文件夹创建失败！");
        }
    }

    //创建settings.json文件
    QFile file(config_folder + "settings.json");
    if(file.exists()){
        qDebug() << "settings文件已经存在";
        file.open(QIODevice::ReadWrite);
        QByteArray fileAll,line;
        while(!file.atEnd()){
            line = file.readLine();
            if(line.at(0) != '#'){
               fileAll += line;
            }
        }
        QJsonDocument jsonfile = QJsonDocument::fromJson(fileAll);
        if(jsonfile.isObject()){
            qDebug() << "已经识别到设置文件为json格式";
            this->json = jsonfile.object();
        }
    }
    else{
        this->json = QJsonObject({});
        this->json.insert("server", QJsonArray());
        this->json.insert("frpcPath", "");
        QFile settings_file(config_folder + "settings.json");
        settings_file.open(QIODevice::WriteOnly);
        QJsonDocument doc(this->json);
        settings_file.write(doc.toJson());
        settings_file.close();

        qDebug() << "setting文件已创建";
        file.close();
    }
}
