#include "src/Headers/server.h"
#include <QDebug>

Server::Server()
{
    this->server_port = NULL;
    this->server_log_max_days = NULL;
}

bool Server::isEmpty(){
    if(server_name.isEmpty() &&
            server_IP.isEmpty() &&
            server_token.isEmpty()) return true;
    else return false;
}

bool Server::operator !=(Server another_server){
    if(this->server_IP != another_server.server_IP ||
            this->server_name != another_server.server_name ||
            this->server_port != another_server.server_port ||
            this->server_token != another_server.server_token ||
            this->server_log_file != another_server.server_log_file ||
            this->server_log_level != another_server.server_log_level ||
            this->server_log_max_days != another_server.server_log_max_days)
        return true;
    else return false;
}

bool Server::operator ==(Server another_server){
    if(this->server_IP == another_server.server_IP &&
            this->server_name == another_server.server_name &&
            this->server_port == another_server.server_port &&
            this->server_token == another_server.server_token &&
            this->server_log_file == another_server.server_log_file &&
            this->server_log_level == another_server.server_log_level &&
            this->server_log_max_days == another_server.server_log_max_days)
        return true;
    else return false;
}

void Server::printServer(){
    qDebug() << "是否为空：" << this->isEmpty()
             << "id:" << this->server_id
             << "name:" << this->server_name
             << "IP:" << this->server_IP
             << "port:" << this->server_port
             << "token:" << this->server_token;
    return;
}
