#include "src/Headers/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::FrpcProcess(Ui::MainWindow *ui){
    if(ui->frpc_switch->text() == "开启" && !server_list.empty()){
        if(!QFile(frpcPath).exists()){
            QMessageBox::warning(this,"Frpc未找到","程序Frpc未找到");
            return;
        }
        ui->frpc_output->clear();
        ui->frpc_output->append("Frpc客户端已开启~");
        ui->frpc_switch->setDisabled(true);
        QStringList frpcArgv;
        frpcArgv << "-c" << config_folder + server_list[ui->frpc_choose_server->currentIndex()].server_name + ".ini";
        frpc = new QProcess(this);
        frpc->start(frpcPath, frpcArgv, QProcess::ReadWrite);
        if(frpc->waitForStarted(500)){
            qDebug() << "程序启动完毕！" ;
        }
        else{
            qDebug() << "程序启动失败！" ;
        }

        connect(frpc,&QProcess::readyReadStandardOutput,[=](){
            QString output = frpc->readAllStandardOutput();
            QStringList outputList = output.split("\n",QString::SkipEmptyParts);
            for(auto o : outputList){
                ui->frpc_output->append("■" + o);
            }
        });

        ui->frpc_switch->setEnabled(true);
        ui->frpc_choose_server->setDisabled(true);
        ui->frpc_switch->setText("关闭");
    }
    else if(ui->frpc_switch->text() == "关闭"){
        ui->frpc_switch->setDisabled(true);
        if(frpc != nullptr){
            frpc->close();
            delete frpc;
            frpc = nullptr;
        }
        ui->frpc_output->append("Frpc客户端已关闭~");
        ui->frpc_switch->setEnabled(true);
        ui->frpc_choose_server->setEnabled(true);
        ui->frpc_switch->setText("开启");
    }
}
