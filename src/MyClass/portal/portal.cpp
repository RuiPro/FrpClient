#include "portal.h"
#include <QDebug>

Portal::Portal(){

}

bool Portal::isEmpty(){
    if(this->portal_name.isEmpty() &&
            this->portal_local_IP.isEmpty() &&
            this->portal_type.isEmpty()) return true;
    else return false;
}

bool Portal::operator!=(Portal another_portal){
    if(this->portal_local_IP != another_portal.portal_local_IP ||
            this->portal_local_port != another_portal.portal_local_port ||
            this->portal_server_port != another_portal.portal_server_port ||
            this->portal_type != another_portal.portal_type ||
            this->portal_encryption != another_portal.portal_encryption ||
            this->portal_compression != another_portal.portal_compression ||
            this->portal_bandiwidth != another_portal.portal_bandiwidth)
        return true;
    else return false;
}


void Portal::printPortal(){
    qDebug() << "是否为空：" << this->isEmpty() <<
                this->portal_name << this->portal_id <<
                this->portal_local_IP << this->portal_local_port <<
                this->portal_server_port << this->portal_type <<
                this->portal_bandiwidth << this->portal_compression <<
                this->portal_encryption;
}
