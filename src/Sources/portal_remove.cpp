#include "src/Headers/mainwindow.h"
#include "src/Headers/set_portal_dialog.h"

void MainWindow::RemovePortal(Server *server_to_edit, Portal *portal_to_remove){
    QString fileName = config_folder + server_to_edit->server_name + ".ini";
    QFile file(fileName);
    if(file.exists()){
        UTF8toGBK(file);
        //传入两个NULL即可删除整个节
        WritePrivateProfileStringW(portal_to_remove->portal_name.toStdWString().c_str(),NULL,NULL,fileName.toStdWString().c_str());
        GBKtoUTF8(file);
    }
    ReadServerList();
}
