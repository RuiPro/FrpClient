QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Sources/file_init.cpp \
    src/Sources/file_transcoding.cpp \
    src/Sources/frpc_process.cpp \
    src/Sources/has_this_server_in_config.cpp \
    src/Sources/import_server_dialog.cpp \
    src/Sources/main.cpp \
    src/Sources/mainwindow.cpp \
    src/Sources/mylabel.cpp \
    src/Sources/portal.cpp \
    src/Sources/portal_add.cpp \
    src/Sources/portal_edit.cpp \
    src/Sources/portal_remove.cpp \
    src/Sources/read_configs.cpp \
    src/Sources/read_server_configs.cpp \
    src/Sources/read_server_list.cpp \
    src/Sources/read_server_portals.cpp \
    src/Sources/server.cpp \
    src/Sources/server_add.cpp \
    src/Sources/server_edit.cpp \
    src/Sources/server_remove.cpp \
    src/Sources/set_configs.cpp \
    src/Sources/set_portal_dialog.cpp \
    src/Sources/set_server_dialog.cpp \
    src/Sources/window_init.cpp

HEADERS += \
    src/Headers/import_server_dialog.h \
    src/Headers/mainwindow.h \
    src/Headers/mylabel.h \
    src/Headers/portal.h \
    src/Headers/server.h \
    src/Headers/set_portal_dialog.h \
    src/Headers/set_server_dialog.h

FORMS += \
    src/Forms/import_server_dialog.ui \
    src/Forms/mainwindow.ui \
    src/Forms/set_portal_dialog.ui \
    src/Forms/set_server_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
