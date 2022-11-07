QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/MainWindow/file_init.cpp \
    src/MainWindow/frpc_process.cpp \
    src/MainWindow/has_this_server_in_config.cpp \
    src/MyClass/dialog_import_server/import_server_dialog.cpp \
    src/MainWindow/main.cpp \
    src/MainWindow/mainwindow.cpp \
    src/MyClass/mylabel/mylabel.cpp \
    src/MyClass/mysettings/mysettings.cpp \
    src/MyClass/portal/portal.cpp \
    src/MainWindow/portal_add.cpp \
    src/MainWindow/portal_edit.cpp \
    src/MainWindow/portal_remove.cpp \
    src/MainWindow/read_configs.cpp \
    src/MainWindow/read_server_configs.cpp \
    src/MainWindow/read_server_list.cpp \
    src/MainWindow/read_server_portals.cpp \
    src/MyClass/server/server.cpp \
    src/MainWindow/server_add.cpp \
    src/MainWindow/server_edit.cpp \
    src/MainWindow/server_remove.cpp \
    src/MainWindow/set_configs.cpp \
    src/MyClass/dialog_set_portal/set_portal_dialog.cpp \
    src/MyClass/dialog_set_server/set_server_dialog.cpp \
    src/MainWindow/window_init.cpp

INCLUDEPATH += 	./src/MainWindow \
				./src/MyClass/dialog_import_server \
				./src/MyClass/mylabel \
				./src/MyClass/mysettings \
				./src/MyClass/portal \
				./src/MyClass/server \
				./src/MyClass/dialog_set_portal \
				./src/MyClass/dialog_set_server
				
HEADERS += \
    src/MyClass/dialog_import_server/import_server_dialog.h \
    src/MainWindow/mainwindow.h \
    src/MyClass/mylabel/mylabel.h \
    src/MyClass/mysettings/mysettings.h \
    src/MyClass/portal/portal.h \
    src/MyClass/server/server.h \
    src/MyClass/dialog_set_portal/set_portal_dialog.h \
    src/MyClass/dialog_set_server/set_server_dialog.h

FORMS += \
    src/MyClass/dialog_import_server/import_server_dialog.ui \
    src/MainWindow/mainwindow.ui \
    src/MyClass/dialog_set_portal/set_portal_dialog.ui \
    src/MyClass/dialog_set_server/set_server_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
