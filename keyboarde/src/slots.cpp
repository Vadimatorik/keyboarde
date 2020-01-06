#include "keyboarde.h"

void keyboarde::new_connection () {
    this->socket = server->nextPendingConnection();
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(server_read()));
    connect(this->socket, SIGNAL(disconnected()), this, SLOT(client_disconnected()));
}

void keyboarde::client_disconnected () {
    this->server->close();
}

void keyboarde::server_read () {
    QByteArray data_in = this->socket->read(1);
    QByteArray data_out;
    uint8_t state = 0;
    data_out.append(state);
    this->socket->write(data_out);
}
