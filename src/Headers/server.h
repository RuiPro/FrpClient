#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include <QList>
#include "src/Headers/portal.h"

class Server
{
public:
    Server();
    int server_id;
    QString server_name;
    QString server_IP;
    unsigned short server_port;
    QString server_token;

    QString server_log_file;
    QString server_log_level;
    unsigned int server_log_max_days;

    QList<Portal> server_portals;

    bool isEmpty();
    bool operator!= (Server another_server);
    bool operator== (Server another_server);
    void printServer();
};

#endif // SERVER_H
