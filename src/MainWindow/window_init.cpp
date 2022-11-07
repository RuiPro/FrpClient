#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::WindowInit(Ui::MainWindow *ui){
    ui->page->setCurrentIndex(0);

    //服务器列表
    ui->server_list_table->setColumnCount(5);     //设置列数
    ui->server_list_table->setHorizontalHeaderLabels(QStringList() << "ID" << "名称" << "IP" << "端口" << "token");  //设置表头
    //ui->server_list_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //设置自动列宽
    ui->server_list_table->verticalHeader()->setHidden(true);       //隐藏左边的行号
    ui->server_list_table->setSelectionBehavior(QTableWidget::SelectRows);
    ui->server_list_table->setSelectionMode(QTableWidget::SingleSelection);
    //设置列宽且固定
    ui->server_list_table->setColumnWidth(0, 38);
    ui->server_list_table->setColumnWidth(1, 162);
    ui->server_list_table->setColumnWidth(2, 162);
    ui->server_list_table->setColumnWidth(3, 162);
    ui->server_list_table->setColumnWidth(4, 162);
    ui->server_list_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    //启动页隧道列表
    ui->frpc_portal_list_table->setColumnCount(6);     //设置列数
    ui->frpc_portal_list_table->setHorizontalHeaderLabels(QStringList() << "ID" << "名称" << "本地IP" << "本地端口" << "远程端口"
                                                    << "类型" );  //设置表头
    ui->frpc_portal_list_table->verticalHeader()->setHidden(true);       //隐藏左边的行号
    ui->frpc_portal_list_table->setSelectionBehavior(QTableWidget::SelectRows);
    ui->frpc_portal_list_table->setSelectionMode(QTableWidget::SingleSelection);
    ui->frpc_portal_list_table->setColumnWidth(0, 40);
    ui->frpc_portal_list_table->setColumnWidth(1, 198);
    ui->frpc_portal_list_table->setColumnWidth(2, 198);
    ui->frpc_portal_list_table->setColumnWidth(3, 100);
    ui->frpc_portal_list_table->setColumnWidth(4, 100);
    ui->frpc_portal_list_table->setColumnWidth(5, 70);
    ui->frpc_portal_list_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    //隧道页列表
    ui->portal_list_table->setColumnCount(9);     //设置列数
    ui->portal_list_table->setHorizontalHeaderLabels(QStringList() << "ID" << "名称" << "本地IP" << "本地端口" << "远程端口"
                                                    << "类型" << "加密" << "压缩" << "带宽(MB)");  //设置表头
    ui->portal_list_table->setSelectionBehavior(QTableWidget::SelectRows);
    ui->portal_list_table->setSelectionMode(QTableWidget::SingleSelection);
    ui->portal_list_table->setColumnWidth(0, 40);
    ui->portal_list_table->setColumnWidth(1, 200);
    ui->portal_list_table->setColumnWidth(2, 200);
    ui->portal_list_table->setColumnWidth(3, 100);
    ui->portal_list_table->setColumnWidth(4, 100);
    ui->portal_list_table->setColumnWidth(5, 70);
    ui->portal_list_table->setColumnWidth(6, 40);
    ui->portal_list_table->setColumnWidth(7, 40);
    ui->portal_list_table->setColumnWidth(8, 100);
    ui->portal_list_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    //设置下拉框单元高度
    QStyledItemDelegate* delegate01 = new QStyledItemDelegate(this);
    ui->frpc_choose_server->setItemDelegate(delegate01);
    ui->frpc_choose_server->setStyleSheet("QComboBox QAbstractItemView::item {min-height: 20px;}");

    QStyledItemDelegate* delegate02 = new QStyledItemDelegate(this);
    ui->portal_choose_server->setItemDelegate(delegate02);
    ui->portal_choose_server->setStyleSheet("QComboBox QAbstractItemView::item {min-height: 20px;}");
}
