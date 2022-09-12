#ifndef IMPORT_SERVER_DIALOG_H
#define IMPORT_SERVER_DIALOG_H

#include <QDialog>
#include "src/Headers/mainwindow.h"

namespace Ui {
class import_server_dialog;
}

class import_server_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit import_server_dialog(QWidget * parent = nullptr,
                         MainWindow * mainwindow = nullptr,
                         QFile * file = nullptr);
    ~import_server_dialog();

private:
    Ui::import_server_dialog *ui;
};

#endif // IMPORT_SERVER_DIALOG_H
