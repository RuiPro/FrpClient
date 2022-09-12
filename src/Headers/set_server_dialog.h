#ifndef SET_SERVER_DIALOG_H
#define SET_SERVER_DIALOG_H

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>
#include <QFileDialog>
#include <QStyledItemDelegate>
#include "src/Headers/mainwindow.h"

namespace Ui {
class set_server_dialog;
}

class set_server_dialog : public QDialog
{
    Q_OBJECT

public:  
    explicit set_server_dialog(QWidget *parent = nullptr,
                               Server* a_server = nullptr,
                               MainWindow * mainwindow = nullptr);
    ~set_server_dialog();

private:
    Ui::set_server_dialog *ui;
};

#endif // SET_SERVER_DIALOG_H
