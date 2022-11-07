//这个头文件定义了一个隧道类
//用于保存隧道的相关数据

#ifndef PORTAL_H
#define PORTAL_H

#include <QString>
#include <QIntValidator>

class Portal
{
public:
    Portal();
    int portal_id;
    QString portal_name;
    QString portal_local_IP;
    unsigned short portal_local_port;
    unsigned short portal_server_port;
    QString portal_type;
    bool portal_encryption;
    bool portal_compression;
    QString portal_bandiwidth;

    bool isEmpty();
    bool operator!= (Portal another_portal);
    void printPortal();
};

#endif // PORTAL_H
