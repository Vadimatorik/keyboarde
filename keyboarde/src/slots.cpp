#include "keyboarde.h"

#include <QKeyEvent>

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

        case KEY_NUM::B_VOLUME_UP:
            state = this->b_volume_up->isDown();
            break;

        case KEY_NUM::B_VOLUME_DOWN:
            state = this->b_volume_down->isDown();
            break;
    }

    data_out.append(state);
    this->socket->write(data_out);
}

void keyboarde::key_handler (QKeyEvent *e, bool state) {
    switch (e->key()) {
        case Qt::Key_Up:
            this->b_up->setDown(state);
            break;

        case Qt::Key_Down:
            this->b_down->setDown(state);
            break;

        case Qt::Key_Left:
            this->b_left->setDown(state);
            break;

        case Qt::Key_Right:
            this->b_right->setDown(state);
            break;

        case Qt::Key_Enter:
        case Qt::Key_Return:
            this->b_enter->setDown(state);
            break;

        case Qt::Key_M:
            this->b_meny->setDown(state);
            break;

        case Qt::Key_R:
            this->b_return->setDown(state);
            break;

        case Qt::Key_Plus:
            this->b_volume_up->setDown(state);
            break;

        case Qt::Key_Minus:
            this->b_volume_down->setDown(state);
            break;
    }
}

bool keyboarde::eventFilter (QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        volatile uint64_t ddd = key->key();

        if ((key->key() == Qt::Key_Enter) ||
            (key->key() == Qt::Key_Return) ||
            (key->key() == Qt::Key_Up) ||
            (key->key() == Qt::Key_Down) ||
            (key->key() == Qt::Key_Right) ||
            (key->key() == Qt::Key_Left) ||
            (key->key() == Qt::Key_M) ||
            (key->key() == Qt::Key_R) ||
            (key->key() == Qt::Key_Plus) ||
            (key->key() == Qt::Key_Minus)) {
            this->key_handler(key, true);
            return true;
        } else {
            return QObject::eventFilter(obj, event);
        }
    } else if (event->type() == QEvent::KeyRelease) {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        if ((key->key() == Qt::Key_Enter) ||
            (key->key() == Qt::Key_Return) ||
            (key->key() == Qt::Key_Up) ||
            (key->key() == Qt::Key_Down) ||
            (key->key() == Qt::Key_Right) ||
            (key->key() == Qt::Key_Left) ||
            (key->key() == Qt::Key_M) ||
            (key->key() == Qt::Key_R) ||
            (key->key() == Qt::Key_Plus) ||
            (key->key() == Qt::Key_Minus)) {
            this->key_handler(key, false);
            return true;
        } else {
            return QObject::eventFilter(obj, event);
        }
    }

    return QObject::eventFilter(obj, event);
}