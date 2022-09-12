#include "src/Headers/set_portal_dialog.h"
#include "ui_set_portal_dialog.h"

set_portal_dialog::set_portal_dialog(QWidget *parent, Portal * a_portal, Server * a_server) :
    QDialog(parent),
    ui(new Ui::set_portal_dialog)
{
    ui->setupUi(this);

    ui->input_portal_name->setMaxLength(30);
    QIntValidator * port_range = new QIntValidator(this);
    port_range->setRange(0,65535);
    ui->input_portal_local_port->setValidator(port_range);
    ui->input_portal_server_port->setValidator(port_range);
    ui->input_portal_bandwidth->setMinimum(0);
    //设置类型下拉框
    ui->input_portal_type->addItems(QStringList() << "tcp" << "udp" << "http" << "https");
    ui->input_portal_bandwidth_type->addItems(QStringList() << "KB" << "MB");
    QString oldname;
    QStyledItemDelegate* delegate04 = new QStyledItemDelegate(this);
    ui->input_portal_type->setItemDelegate(delegate04);
    ui->input_portal_type->setStyleSheet("QComboBox QAbstractItemView::item {min-height: 20px;}");

    //如果传入的隧道数据不为空，则为编辑
    if(!a_portal->isEmpty()){
        oldname = a_portal->portal_name;
        ui->input_portal_name->setText(a_portal->portal_name);
        ui->input_portal_local_ip->setText(a_portal->portal_local_IP);
        ui->input_portal_local_port->setText(QString::number(a_portal->portal_local_port));
        ui->input_portal_server_port->setText(QString::number(a_portal->portal_server_port));
        ui->input_portal_type->setCurrentText(a_portal->portal_type); 
        if(a_portal->portal_bandiwidth.size() >= 3){
            QString str = a_portal->portal_bandiwidth;
            QString bandwidth = str.remove(a_portal->portal_bandiwidth.size() - 2, 2);
            str = a_portal->portal_bandiwidth;
            QString bandwidthType = str.remove(0, bandwidth.size());
            ui->input_portal_bandwidth->setValue(bandwidth.toUInt());
            ui->input_portal_bandwidth_type->setCurrentText(bandwidthType);
        }
        if(a_portal->portal_encryption == true){
            ui->input_portal_encryption->setChecked(true);
        }
        if(a_portal->portal_compression == true){
            ui->input_portal_compression->setChecked(true);
        }
    }

    connect(ui->input_portal_cancel, &QPushButton::clicked,[=](){
        this->close();
    });

    connect(ui->input_portal_comfirm,&QPushButton::clicked,[=](){
        unsigned short local_port = ui->input_portal_local_port->text().toUtf8().toUShort();
        unsigned short server_port = ui->input_portal_server_port->text().toUtf8().toUShort();
        if(!ui->input_portal_name->text().isEmpty() &&
                !ui->input_portal_local_ip->text().isEmpty() &&
                !ui->input_portal_local_port->text().isEmpty() &&
                !ui->input_portal_server_port->text().isEmpty()){
            //判断端口是否合法
            if(!local_port){
                QMessageBox::warning(this,"错误","请输入正确的本地端口号");
                return;
            }
            if(!server_port){
                QMessageBox::warning(this,"错误","请输入正确的服务器端口号");
                return;
            }
            //如果是新建隧道且已经存在这个名字的隧道
            if(a_portal->isEmpty()){
                for(int i = 0; i < a_server->server_portals.size(); ++i){
                    if(ui->input_portal_name->text() == a_server->server_portals.at(i).portal_name){
                        QMessageBox::warning(this,"新建隧道重名冲突",
                                              "已存在隧道名为" + ui->input_portal_name->text() + "的隧道,\n请重新编辑!");
                        return;
                    }
                }
            }
            //如果只是修改隧道，那么自己和自己重名是没有关系的
            if(!a_portal->isEmpty() && ui->input_portal_name->text() != oldname){
                for(int i = 0; i < a_server->server_portals.size(); ++i){
                    if(ui->input_portal_name->text() == a_server->server_portals.at(i).portal_name){
                        QMessageBox::warning(this,"修改隧道重名冲突",
                                              "已存在隧道名为" + ui->input_portal_name->text() + "的其他隧道,\n请重新编辑!");
                        return;
                    }
                }
            }

            //如果数据合法，传出输入的隧道信息
            a_portal->portal_name = ui->input_portal_name->text().toUtf8();
            a_portal->portal_local_IP = ui->input_portal_local_ip->text();
            a_portal->portal_local_port = ui->input_portal_local_port->text().toUShort();
            a_portal->portal_server_port = ui->input_portal_server_port->text().toUShort();
            a_portal->portal_type = ui->input_portal_type->currentText();
            a_portal->portal_compression = ui->input_portal_compression->isChecked();
            a_portal->portal_encryption = ui->input_portal_encryption->isChecked();
            if(ui->input_portal_bandwidth->text().toInt() > 0){
                a_portal->portal_bandiwidth =
                        ui->input_portal_bandwidth->text() + ui->input_portal_bandwidth_type->currentText();
            }
            this->close();
        }
        else{
            QMessageBox::warning(this,"错误","请补全所有必要信息");
        }
    });
}

set_portal_dialog::~set_portal_dialog()
{
    delete ui;
}
