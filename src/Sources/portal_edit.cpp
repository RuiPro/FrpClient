#include "src/Headers/mainwindow.h"
#include "src/Headers/set_portal_dialog.h"

void MainWindow::EditPortal(Server *server_to_edit, Portal *portal_to_edit){
    Portal editedPortal = * portal_to_edit;
    set_portal_dialog* spd = new set_portal_dialog(this,&editedPortal,server_to_edit);
    spd->setAttribute(Qt::WA_DeleteOnClose);
    //去掉对话框上的问号
    spd->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    spd->exec();

    QString fileName = config_folder + server_to_edit->server_name + ".ini";
    QFile file(fileName);

    UTF8toGBK(file);
    //更改属性
    if(!editedPortal.isEmpty() && editedPortal != *portal_to_edit && file.exists()){
        WritePrivateProfileStringW(portal_to_edit->portal_name.toStdWString().c_str(),TEXT("type"),editedPortal.portal_type.toStdWString().c_str(),fileName.toStdWString().c_str());
        WritePrivateProfileStringW(portal_to_edit->portal_name.toStdWString().c_str(),TEXT("local_ip"),editedPortal.portal_local_IP.toStdWString().c_str(),fileName.toStdWString().c_str());
        WritePrivateProfileStringW(portal_to_edit->portal_name.toStdWString().c_str(),TEXT("local_port"),QString::number(editedPortal.portal_local_port).toStdWString().c_str(),fileName.toStdWString().c_str());
        WritePrivateProfileStringW(portal_to_edit->portal_name.toStdWString().c_str(),TEXT("remote_port"),QString::number(editedPortal.portal_server_port).toStdWString().c_str(),fileName.toStdWString().c_str());
        WritePrivateProfileStringW(portal_to_edit->portal_name.toStdWString().c_str(),TEXT("bandwidth_limit"),editedPortal.portal_bandiwidth.toStdWString().c_str(),fileName.toStdWString().c_str());
        if(editedPortal.portal_encryption == true)
            WritePrivateProfileStringW(portal_to_edit->portal_name.toStdWString().c_str(),TEXT("use_encryption"),TEXT("true"),fileName.toStdWString().c_str());
        if(editedPortal.portal_compression == true)
            WritePrivateProfileStringW(portal_to_edit->portal_name.toStdWString().c_str(),TEXT("use_compression"),TEXT("true"),fileName.toStdWString().c_str());
    }
    GBKtoUTF8(file);
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
