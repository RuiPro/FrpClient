#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WindowInit(ui);

    //添加服务器
    connect(ui->server_add_pushButton,&QPushButton::clicked,this,&MainWindow::AddServer);

    //修改服务器
    connect(ui->server_edit_pushButton,&QPushButton::clicked,[=](){
        auto item = ui->server_list_table->selectedItems();
        if(!item.empty()){
            int row = ui->server_list_table->row(item.at(0));
            EditServer(&(server_list[row]));
        }
    });

    //删除服务器
    connect(ui->server_remove_pushButton,&QPushButton::clicked,[=](){
        auto item = ui->server_list_table->selectedItems();
        if(!item.empty()){
            int row = ui->server_list_table->row(item.at(0));
            RemoveServer(&(server_list[row]));
        }
    });

    //刷新服务器
    connect(ui->server_refresh_pushButton,&QPushButton::clicked,this,&MainWindow::ReadServerList);

    //将server_list内的服务器配置输出到服务器列表/启动页的服务器下拉框/隧道页的服务器下拉框
    connect(this,&MainWindow::ReadServerListReady,[=](){
        if(sizeof_server_list != server_list.size()){
            sizeof_server_list = server_list.size();
            current_Server_index = 0;
        }
        else{
            current_Server_index = ui->portal_choose_server->currentIndex();
        }
        //初始化
        ui->server_list_table->clearContents();
        ui->server_list_table->setRowCount(server_list.size());
        ui->portal_choose_server->clear();
        ui->frpc_choose_server->clear();

        //设置内容
        for(int i = 0; i < server_list.size(); ++i){
            //服务器列表ID
            ui->server_list_table->setItem(i,0,new QTableWidgetItem(QString::number(server_list.at(i).server_id)));
            //服务器列表名字
            ui->server_list_table->setItem(i,1,new QTableWidgetItem(server_list.at(i).server_name));
            //服务器列表IP
            ui->server_list_table->setItem(i,2,new QTableWidgetItem(server_list.at(i).server_IP));
            //服务器列表端口
            ui->server_list_table->setItem(i,3,new QTableWidgetItem(QString::number(server_list.at(i).server_port)));
            //服务器列表Token
            ui->server_list_table->setItem(i,4,new QTableWidgetItem(server_list.at(i).server_token));
            //启动页的服务器下拉框
            ui->frpc_choose_server->addItem(server_list.at(i).server_name + " [" + server_list.at(i).server_IP +
                                            ":" + QString::number(server_list.at(i).server_port) +"]");
            //隧道页的服务器下拉框
            ui->portal_choose_server->addItem(server_list.at(i).server_name + " [" + server_list.at(i).server_IP +
                                            ":" + QString::number(server_list.at(i).server_port) +"]");
        }
        //设置表格居中
        for (int j = 0; j<ui->server_list_table->rowCount(); ++j){
            for (int k = 0; k<ui->server_list_table->columnCount(); ++k){
                ui->server_list_table->item(j,k)->setTextAlignment(Qt::AlignCenter);
            }
        }
        ui->portal_choose_server->setCurrentIndex(current_Server_index);
    });

    //将server_list内的服务器配置的隧道输出到两个表格
    connect(this,&MainWindow::ReadServerListReady,[=](){
        if(server_list.size() <= 0){
            return;
        }
        Server selected_server = server_list.at(ui->frpc_choose_server->currentIndex());

        //初始化
        ui->frpc_portal_list_table->clearContents();
        ui->frpc_portal_list_table->setRowCount(selected_server.server_portals.size());
        ui->portal_list_table->clearContents();
        ui->portal_list_table->setRowCount(selected_server.server_portals.size());

        //设置内容
        for(int i = 0; i < selected_server.server_portals.size(); ++i){
            //启动页隧道ID
            ui->frpc_portal_list_table->setItem(i,0,new QTableWidgetItem(QString::number(selected_server.server_portals.at(i).portal_id)));
            //启动页隧道名称
            ui->frpc_portal_list_table->setItem(i,1,new QTableWidgetItem(selected_server.server_portals.at(i).portal_name));
            //启动页隧道本地IP
            ui->frpc_portal_list_table->setItem(i,2,new QTableWidgetItem(selected_server.server_portals.at(i).portal_local_IP));
            //启动页隧道本地端口
            ui->frpc_portal_list_table->setItem(i,3,new QTableWidgetItem(QString::number(selected_server.server_portals.at(i).portal_local_port)));
            //启动页隧道远程端口
            ui->frpc_portal_list_table->setItem(i,4,new QTableWidgetItem(QString::number(selected_server.server_portals.at(i).portal_server_port)));
            //启动页隧道类型
            ui->frpc_portal_list_table->setItem(i,5,new QTableWidgetItem(selected_server.server_portals.at(i).portal_type));

            //隧道页隧道ID
            ui->portal_list_table->setItem(i,0,new QTableWidgetItem(QString::number(selected_server.server_portals.at(i).portal_id)));
            //隧道页隧道名称
            ui->portal_list_table->setItem(i,1,new QTableWidgetItem(selected_server.server_portals.at(i).portal_name));
            //隧道页隧道本地IP
            ui->portal_list_table->setItem(i,2,new QTableWidgetItem(selected_server.server_portals.at(i).portal_local_IP));
            //隧道页隧道本地端口
            ui->portal_list_table->setItem(i,3,new QTableWidgetItem(QString::number(selected_server.server_portals.at(i).portal_local_port)));
            //隧道页隧道远程端口
            ui->portal_list_table->setItem(i,4,new QTableWidgetItem(QString::number(selected_server.server_portals.at(i).portal_server_port)));
            //隧道页隧道类型
            ui->portal_list_table->setItem(i,5,new QTableWidgetItem(selected_server.server_portals.at(i).portal_type));
            //隧道页隧道加密
            if(selected_server.server_portals.at(i).portal_encryption == true)
                ui->portal_list_table->setItem(i,6,new QTableWidgetItem("true"));
            else
                ui->portal_list_table->setItem(i,6,new QTableWidgetItem("false"));
            //隧道页隧道压缩
            if(selected_server.server_portals.at(i).portal_compression == true)
                ui->portal_list_table->setItem(i,7,new QTableWidgetItem("true"));
            else
                ui->portal_list_table->setItem(i,7,new QTableWidgetItem("false"));
            //隧道页隧道带宽
            ui->portal_list_table->setItem(i,8,new QTableWidgetItem(selected_server.server_portals.at(i).portal_bandiwidth));
        }
        //设置表格居中
        for (int j = 0; j<ui->frpc_portal_list_table->rowCount(); ++j){
            for (int k = 0; k<ui->frpc_portal_list_table->columnCount(); ++k){
                ui->frpc_portal_list_table->item(j,k)->setTextAlignment(Qt::AlignCenter);
            }
        }
        for (int j = 0; j<ui->portal_list_table->rowCount(); ++j){
            for (int k = 0; k<ui->portal_list_table->columnCount(); ++k){
                ui->portal_list_table->item(j,k)->setTextAlignment(Qt::AlignCenter);
            }
        }
    });

    //切换服务器时在隧道列表输出
    connect(ui->frpc_choose_server,&QComboBox::currentTextChanged,[=](){
        ui->portal_choose_server->setCurrentIndex(ui->frpc_choose_server->currentIndex());
    });
    connect(ui->portal_choose_server,&QComboBox::currentTextChanged,[=](){
        ui->frpc_choose_server->setCurrentIndex(ui->portal_choose_server->currentIndex());
    });

    connect(ui->portal_choose_server,&QComboBox::currentTextChanged,[=](){
        qDebug() << ui->portal_choose_server->currentText();

        //清空
        ui->frpc_portal_list_table->clearContents();
        ui->portal_list_table->clearContents();

        if(ui->frpc_choose_server->currentIndex() < 0 || ui->frpc_choose_server->currentIndex() >= server_list.size()){
            return;
        }
        Server selected_server = server_list.at(ui->frpc_choose_server->currentIndex());

        ui->frpc_portal_list_table->setRowCount(selected_server.server_portals.size());
        ui->portal_list_table->setRowCount(selected_server.server_portals.size());

        //设置内容
        for(int i = 0; i < selected_server.server_portals.size(); ++i){
            //启动页隧道ID
            ui->frpc_portal_list_table->setItem(i,0,new QTableWidgetItem(QString::number(selected_server.server_portals.at(i).portal_id)));
            //启动页隧道名称
            ui->frpc_portal_list_table->setItem(i,1,new QTableWidgetItem(selected_server.server_portals.at(i).portal_name));
            //启动页隧道本地IP
            ui->frpc_portal_list_table->setItem(i,2,new QTableWidgetItem(selected_server.server_portals.at(i).portal_local_IP));
            //启动页隧道本地端口
            ui->frpc_portal_list_table->setItem(i,3,new QTableWidgetItem(QString::number(selected_server.server_portals.at(i).portal_local_port)));
            //启动页隧道远程端口
            ui->frpc_portal_list_table->setItem(i,4,new QTableWidgetItem(QString::number(selected_server.server_portals.at(i).portal_server_port)));
            //启动页隧道类型
            ui->frpc_portal_list_table->setItem(i,5,new QTableWidgetItem(selected_server.server_portals.at(i).portal_type));

            //隧道页隧道ID
            ui->portal_list_table->setItem(i,0,new QTableWidgetItem(QString::number(selected_server.server_portals.at(i).portal_id)));
            //隧道页隧道名称
            ui->portal_list_table->setItem(i,1,new QTableWidgetItem(selected_server.server_portals.at(i).portal_name));
            //隧道页隧道本地IP
            ui->portal_list_table->setItem(i,2,new QTableWidgetItem(selected_server.server_portals.at(i).portal_local_IP));
            //隧道页隧道本地端口
            ui->portal_list_table->setItem(i,3,new QTableWidgetItem(QString::number(selected_server.server_portals.at(i).portal_local_port)));
            //隧道页隧道远程端口
            ui->portal_list_table->setItem(i,4,new QTableWidgetItem(QString::number(selected_server.server_portals.at(i).portal_server_port)));
            //隧道页隧道类型
            ui->portal_list_table->setItem(i,5,new QTableWidgetItem(selected_server.server_portals.at(i).portal_type));
            //隧道页隧道加密
            if(selected_server.server_portals.at(i).portal_encryption == true)
                ui->portal_list_table->setItem(i,6,new QTableWidgetItem("true"));
            else
                ui->portal_list_table->setItem(i,6,new QTableWidgetItem("false"));
            //隧道页隧道压缩
            if(selected_server.server_portals.at(i).portal_compression == true)
                ui->portal_list_table->setItem(i,7,new QTableWidgetItem("true"));
            else
                ui->portal_list_table->setItem(i,7,new QTableWidgetItem("false"));
            //隧道页隧道带宽
            ui->portal_list_table->setItem(i,8,new QTableWidgetItem(selected_server.server_portals.at(i).portal_bandiwidth));
        }
        //设置表格居中
        for (int j = 0; j<ui->frpc_portal_list_table->rowCount(); ++j){
            for (int k = 0; k<ui->frpc_portal_list_table->columnCount(); ++k){
                ui->frpc_portal_list_table->item(j,k)->setTextAlignment(Qt::AlignCenter);
            }
        }
        for (int j = 0; j<ui->portal_list_table->rowCount(); ++j){
            for (int k = 0; k<ui->portal_list_table->columnCount(); ++k){
                ui->portal_list_table->item(j,k)->setTextAlignment(Qt::AlignCenter);
            }
        }
    });

    //刷新隧道
    connect(ui->portal_refresh_pushButton,&QPushButton::clicked,this,&MainWindow::ReadServerList);

    //添加隧道
    connect(ui->portal_add_pushButton,&QPushButton::clicked,[=](){
        if(ui->portal_choose_server->count() > 0){
            this->AddPortal(&server_list[ui->portal_choose_server->currentIndex()]);
        }
    });

    //修改隧道
    connect(ui->portal_edit_pushButton,&QPushButton::clicked,[=](){
        auto item = ui->portal_list_table->selectedItems();
        if(!item.empty()){
            int row = ui->portal_list_table->row(item.at(0));
            EditPortal(&(server_list[ui->portal_choose_server->currentIndex()]),
                    &(server_list[ui->portal_choose_server->currentIndex()].server_portals[row]));
        }
    });

    //删除隧道
    connect(ui->portal_remove_pushButton,&QPushButton::clicked,[=](){
        auto item = ui->portal_list_table->selectedItems();
        if(!item.empty()){
            int row = ui->portal_list_table->row(item.at(0));
            RemovePortal(&(server_list[ui->portal_choose_server->currentIndex()]),
                    &(server_list[ui->portal_choose_server->currentIndex()].server_portals[row]));
        }
    });

    //启动/关闭Frpc
    connect(ui->frpc_switch,&QPushButton::clicked,[=](){
        FrpcProcess(ui);
    });

    //设置frpc路径
    connect(ui->set_Frpc_path_pushbutton,&QPushButton::clicked,this,&MainWindow::SetFrpcPath);


    //设置页面关于
    connect(ui->about,&MyLabel::clicked,[=](){
        QMessageBox::information(this,"关于本软件","这是一个Frpc客户端。需要依赖frpc才能运行。\n"
                                              "本软件使用MIT协议开源。\n"
                                              "作者：RuiPro(GitHub)");
    });
    connect(ui->go_to_github,&MyLabel::clicked,[=](){
        QDesktopServices::openUrl(QUrl(QString("https://github.com/RuiPro/FrpClient")));
    });
}

MainWindow::~MainWindow()
{
    if(frpc != nullptr){
        delete frpc;
    }
    delete ui;
}
