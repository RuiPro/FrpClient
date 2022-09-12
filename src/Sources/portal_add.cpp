#include "src/Headers/mainwindow.h"
#include "src/Headers/set_portal_dialog.h"

void MainWindow::AddPortal(Server * server_to_add_in){
    Portal newPortal;
    set_portal_dialog* spd = new set_portal_dialog(this,&newPortal,server_to_add_in);
    spd->setAttribute(Qt::WA_DeleteOnClose);
    //去掉对话框上的问号
    spd->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    spd->exec();

    if(!newPortal.isEmpty()){
        newPortal.portal_id = server_to_add_in->server_portals.size();
        QString fileName = config_folder + server_to_add_in->server_name + ".ini";
        //把文件由utf8格式转成gbk
        QFile file(fileName);
        UTF8toGBK(file);
        //用QSettings写ini文件会导致除0~9\a~z\A~Z\-\_\.之外的字符会被转义，所以使用winAPI
        WritePrivateProfileStringW(newPortal.portal_name.toStdWString().c_str(),TEXT("type"),newPortal.portal_type.toStdWString().c_str(),fileName.toStdWString().c_str());
        WritePrivateProfileStringW(newPortal.portal_name.toStdWString().c_str(),TEXT("local_ip"),newPortal.portal_local_IP.toStdWString().c_str(),fileName.toStdWString().c_str());
        WritePrivateProfileStringW(newPortal.portal_name.toStdWString().c_str(),TEXT("local_port"),QString::number(newPortal.portal_local_port).toStdWString().c_str(),fileName.toStdWString().c_str());
        WritePrivateProfileStringW(newPortal.portal_name.toStdWString().c_str(),TEXT("remote_port"),QString::number(newPortal.portal_server_port).toStdWString().c_str(),fileName.toStdWString().c_str());
        WritePrivateProfileStringW(newPortal.portal_name.toStdWString().c_str(),TEXT("bandwidth_limit"),newPortal.portal_bandiwidth.toStdWString().c_str(),fileName.toStdWString().c_str());
        if(newPortal.portal_encryption == true)
            WritePrivateProfileStringW(newPortal.portal_name.toStdWString().c_str(),TEXT("use_encryption"),TEXT("true"),fileName.toStdWString().c_str());
        if(newPortal.portal_compression == true)
            WritePrivateProfileStringW(newPortal.portal_name.toStdWString().c_str(),TEXT("use_compression"),TEXT("true"),fileName.toStdWString().c_str());

        //把文件由gbk格式转成utf8
        GBKtoUTF8(file);

    }
    ReadServerList();
}
