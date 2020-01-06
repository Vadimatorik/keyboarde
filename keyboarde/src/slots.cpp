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

    switch (data_in[0]) {
        case KEY_NUM::B_UP:
            state = this->b_up->isDown();
            break;

        case KEY_NUM::B_DOWN:
            state = this->b_down->isDown();
            break;

        case KEY_NUM::B_LEFT:
            state = this->b_left->isDown();
            break;

        case KEY_NUM::B_RIGHT:
            state = this->b_right->isDown();
            break;

        case KEY_NUM::B_ENTER:
            state = this->b_enter->isDown();
            break;

        case KEY_NUM::B_RETURN:
            state = this->b_return->isDown();
            break;

        case KEY_NUM::B_MENU:
            state = this->b_meny->isDown();
            break;
    }

    data_out.append(state);
    this->socket->write(data_out);
}
