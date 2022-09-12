#include "src/Headers/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::SetFrpcPath(){
    QString path = QFileDialog::getOpenFileName(this,"选择Frpc客户端",QCoreApplication::applicationDirPath(),"*.exe");
    if(frpc == nullptr){
        frpcPath = path;
        json["frpcPath"] = path;
        QFile settings_file(config_folder + "settings.json");
        settings_file.open(QIODevice::WriteOnly);
        QJsonDocument doc(json);
        settings_file.write(doc.toJson());
        settings_file.close();
        ui->settings_frpc_path->setText(frpcPath);
    }
    else{
        QMessageBox::warning(this,"Frpc正在运行","Frpc客户端已在运行\n请停止后再更改路径");
    }
}

