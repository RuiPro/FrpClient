#include "mainwindow.h"
#include "set_portal_dialog.h"

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

        MySettings setting;
        setting.Open(fileName);

        setting.SetValue(newPortal.portal_name,"type",newPortal.portal_type);
        setting.SetValue(newPortal.portal_name,"local_ip",newPortal.portal_local_IP);
        setting.SetValue(newPortal.portal_name,"local_port",QString::number(newPortal.portal_local_port));
        setting.SetValue(newPortal.portal_name,"remote_port",QString::number(newPortal.portal_server_port));
        setting.SetValue(newPortal.portal_name,"bandwidth_limit",newPortal.portal_bandiwidth);
        if(newPortal.portal_encryption == true)
            setting.SetValue(newPortal.portal_name,"use_encryption","true");
        if(newPortal.portal_compression == true)
            setting.SetValue(newPortal.portal_name,"use_compression","true");

    }
    ReadServerList();
}
