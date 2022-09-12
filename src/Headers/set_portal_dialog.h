#ifndef SET_PORTAL_DIALOG_H
#define SET_PORTAL_DIALOG_H

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>
#include <QFileDialog>
#include <QStyledItemDelegate>
#include "src/Headers/portal.h"
#include "src/Headers/server.h"

namespace Ui {
class set_portal_dialog;
}

class set_portal_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit set_portal_dialog(QWidget *parent = nullptr,
                               Portal *a_portal = nullptr,
                               Server *a_server = nullptr);
    ~set_portal_dialog();

private:
    Ui::set_portal_dialog *ui;
};

#endif // SET_PORTAL_DIALOG_H
