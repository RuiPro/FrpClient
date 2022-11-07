#include "set_server_dialog.h"
#include "ui_set_server_dialog.h"
#include "mylabel.h"
#include "import_server_dialog.h"

set_server_dialog::set_server_dialog(QWidget* parent,
                                     Server* a_server,
                                     MainWindow* mainwindow) :
    QDialog(parent),
    ui(new Ui::set_server_dialog)
{
    ui->setupUi(this);
    //对输入框进行数据的限定
    ui->input_server_name->setMaxLength(30);
    QIntValidator * port_range = new QIntValidator(this);
    port_range->setRange(0,65535);
    ui->input_server_port->setValidator(port_range);
    ui->server_log_max_save_days->setMinimum(0);
    //trace, debug, info, warn, error
    ui->server_log_content->addItems(QStringList() << "trace" << "debug" << "info" << "warn" << "error");
    QString oldname;
    //设置下拉框单元高度
    QStyledItemDelegate* delegate03 = new QStyledItemDelegate(this);
    ui->server_log_content->setItemDelegate(delegate03);
    ui->server_log_content->setStyleSheet("QComboBox QAbstractItemView::item {min-height: 20px;}");
    if(a_server->isEmpty()){
        ui->server_log_switch->setChecked(true);
    }

    //如果传入的服务器数据不为空，则为编辑
    if(!a_server->isEmpty()){
        ui->input_server_name->setText(a_server->server_name);
        ui->input_server_IP->setText(a_server->server_IP);
        ui->input_server_port->setText(QString::number(a_server->server_port));
        ui->input_server_token->setText(a_server->server_token);
        oldname = a_server->server_name;
        if(!a_server->server_log_file.isEmpty()){
            ui->server_log_switch->setChecked(true);
            ui->server_log_path->setText(a_server->server_log_file);
            ui->server_log_max_save_days->setValue(a_server->server_log_max_days);
            ui->server_log_content->setCurrentText(a_server->server_log_level);
        }
        else{
            ui->server_log_switch->setChecked(false);
            ui->server_log_path->setEnabled(false);
            ui->server_log_max_save_days->setEnabled(false);
            ui->server_log_content->setEnabled(false);
            ui->server_log_path_select->setEnabled(false);
        }
    }
    else {
        MyLabel * mylabel = new MyLabel(this);
        mylabel->setAlignment(Qt::AlignCenter);
        mylabel->setFixedWidth(132);
        mylabel->setFixedHeight(20);
        mylabel->setStyleSheet("color:red;");
        QPoint pos;
        pos.setX(this->width()/2-mylabel->size().width()/2);
        pos.setY(this->height()-mylabel->size().height());
        mylabel->move(pos);
        mylabel->setText("<u>已经有配置文件？导入>></u>");
        connect(mylabel,&MyLabel::clicked,[=](){
            QString newIni = QFileDialog::getOpenFileName(this,"选择服务器配置文件",QCoreApplication::applicationDirPath(),"*.ini");
            if(newIni.isEmpty()) return;
            QFile file(newIni);
            import_server_dialog* isd = new import_server_dialog(this, mainwindow, &file);
            isd->setAttribute(Qt::WA_DeleteOnClose);
            isd->exec();
            this->close();
        });
    }

    //关闭对话框
    connect(ui->input_server_cancel, &QPushButton::clicked,[=](){
        this->close();
    });


    //确认提交服务器信息
    connect(ui->input_server_comfirm, &QPushButton::clicked,[=](){
        //判断是否留空
        unsigned short port = ui->input_server_port->text().toUtf8().toUShort();
        if(!ui->input_server_name->text().isEmpty() &&
                !ui->input_server_IP->text().isEmpty() &&
                !ui->input_server_port->text().isEmpty() &&
                ((ui->server_log_switch->isChecked() && !ui->server_log_path->text().isEmpty()) ||
                 !ui->server_log_switch->isChecked())
                ){

            //判断端口是否合法
            if(!port){
                QMessageBox::warning(this,"错误","请输入正确的端口号");
                return;
            }
            //如果是新建服务器且已经存在这个名字的服务器
            if(a_server->isEmpty() &&
                    mainwindow->HasThisServer(ui->input_server_name->text()) > 0){
                QMessageBox::warning(this,"新建服务器重名冲突",
                                      "已存在服务器名为" + ui->input_server_name->text() + "的服务器,\n请重新编辑!");
                return;
            }
            //如果只是修改服务器，那么自己和自己重名是没有关系的
            if(!a_server->isEmpty() &&
                    mainwindow->HasThisServer(ui->input_server_name->text()) >= 0 &&
                    mainwindow->HasThisServer(ui->input_server_name->text()) != mainwindow->HasThisServer(oldname)){
                QMessageBox::warning(this,"修改服务器重名冲突",
                                      "已存在服务器名为" + ui->input_server_name->text() + "的服务器,\n请重新编辑!");
                return;
            }

            //如果数据合法，传出输入的服务器信息
            a_server->server_name = ui->input_server_name->text().toUtf8();
            a_server->server_IP = ui->input_server_IP->text();
            a_server->server_port = ui->input_server_port->text().toUShort();
            a_server->server_token = ui->input_server_token->text();
            if(ui->server_log_switch->isChecked()){
                a_server->server_log_file = ui->server_log_path->text();
                a_server->server_log_level = ui->server_log_content->currentText();
                a_server->server_log_max_days = ui->server_log_max_save_days->value();
            }

            this->close();
        }
        else{
            QMessageBox::warning(this,"错误","请补全所有必要信息");
        }
    });

    //是否对日志进行输入
    connect(ui->server_log_switch,&QCheckBox::stateChanged,[=](int stata){
        if(stata){
            ui->server_log_path->setEnabled(true);
            ui->server_log_max_save_days->setEnabled(true);
            ui->server_log_content->setEnabled(true);
            ui->server_log_path_select->setEnabled(true);
        }
        else{
            ui->server_log_path->setEnabled(false);
            ui->server_log_max_save_days->setEnabled(false);
            ui->server_log_content->setEnabled(false);
            ui->server_log_path_select->setEnabled(false);
        }
    });

    connect(ui->server_log_path_select,&QPushButton::clicked,[=](){
        QString folder_path = QFileDialog::getExistingDirectory(this,"选择保存的文件夹",QCoreApplication::applicationDirPath());
        ui->server_log_path->setText(folder_path);
    });

}

set_server_dialog::~set_server_dialog()
{
    delete ui;
}
