//导入已有的服务器文件

#include "import_server_dialog.h"
#include "ui_import_server_dialog.h"

import_server_dialog::import_server_dialog(QWidget* parent, MainWindow* mainwindow, QFile* file) :
    QDialog(parent),
    ui(new Ui::import_server_dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_cancel,&QPushButton::clicked,this,&import_server_dialog::close);
    connect(ui->pushButton_comfirm,&QPushButton::clicked,[=](){
        QString newServerName = ui->input_server_name->text();
        if(newServerName.isEmpty()){
            QMessageBox::warning(this,"信息不完整","请输入新服务器名称！");
            return;
        }
        else if(mainwindow->HasThisServer(newServerName) != -1){
            QMessageBox::warning(this,"名称冲突","已存在该名称的服务器，请重新输入");
            return;
        }
        //把导入的服务器信息保存在json
        if(mainwindow->json.value("server").isArray()){
            QJsonArray serverArray = mainwindow->json.value("server").toArray();
            QJsonObject newServer;
            newServer.insert("server_name",newServerName);
            serverArray.push_back(newServer);
            mainwindow->json["server"] = serverArray;
            QFile settings_file(mainwindow->config_folder + "settings.json");
            settings_file.open(QIODevice::WriteOnly);
            QJsonDocument doc(mainwindow->json);
            settings_file.write(doc.toJson());
            settings_file.close();
        }
        //将配置文件复制到配置文件夹下
        file->copy(mainwindow->config_folder + newServerName + ".ini");
        //刷新列表
        mainwindow->ReadServerList();
        this->close();
    });
}

import_server_dialog::~import_server_dialog()
{
    delete ui;
}
