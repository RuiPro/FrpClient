#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::ReadConfigs(){
    frpcPath = json.value("frpcPath").toString();
    ui->settings_frpc_path->setText(frpcPath);
}
