#include "mainwindow.h"
#include "set_portal_dialog.h"

void MainWindow::RemovePortal(Server *server_to_edit, Portal *portal_to_remove){
    QString fileName = config_folder + server_to_edit->server_name + ".ini";
    QFile file(fileName);
    if(file.exists()){
        MySettings setting;
        setting.Open(fileName);
        setting.RemoveSection(portal_to_remove->portal_name);
    }
    ReadServerList();
}
