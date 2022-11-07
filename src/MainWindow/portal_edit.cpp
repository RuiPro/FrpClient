#include "mainwindow.h"
#include "set_portal_dialog.h"

void MainWindow::EditPortal(Server *server_to_edit, Portal *portal_to_edit){
    Portal editedPortal = * portal_to_edit;
    set_portal_dialog* spd = new set_portal_dialog(this,&editedPortal,server_to_edit);
    spd->setAttribute(Qt::WA_DeleteOnClose);
    //去掉对话框上的问号
    spd->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    spd->exec();

    QString fileName = config_folder + server_to_edit->server_name + ".ini";
    QFile file(fileName);

    if(!editedPortal.isEmpty() && editedPortal != *portal_to_edit && file.exists()){
        MySettings setting;
        setting.Open(fileName);
        setting.SetValue(editedPortal.portal_name,"type",editedPortal.portal_type);
        setting.SetValue(editedPortal.portal_name,"local_ip",editedPortal.portal_local_IP);
        setting.SetValue(editedPortal.portal_name,"local_port",QString::number(editedPortal.portal_local_port));
        setting.SetValue(editedPortal.portal_name,"remote_port",QString::number(editedPortal.portal_server_port));
        setting.SetValue(editedPortal.portal_name,"bandwidth_limit",editedPortal.portal_bandiwidth);
        if(editedPortal.portal_encryption == true)
            setting.SetValue(editedPortal.portal_name,"use_encryption","true");
        if(editedPortal.portal_compression == true)
            setting.SetValue(editedPortal.portal_name,"use_compression","true");
    }

    //改名要放在最后
    if(editedPortal.portal_name != portal_to_edit->portal_name){
        file.open(QIODevice::ReadOnly);
        QByteArray all = file.readAll();
        file.close();
        QString str(all);
        str.replace("[" + portal_to_edit->portal_name + "]", "[" + editedPortal.portal_name + "]");
        file.open(QIODevice::WriteOnly);
        file.write(str.toUtf8());
        file.close();
    }
    ReadServerList();
}
