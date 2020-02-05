#include "keyboarde.h"

#include <QGridLayout>
#include <QNetworkDatagram>

keyboarde::keyboarde (QWidget *parent, keyboarde_cfg *cfg) : QWidget(parent) {
    QGridLayout *l = new QGridLayout(this);
    this->setLayout(l);

    this->server = new QTcpServer(this);
    this->socket = new QTcpSocket(this);

    this->b_meny = new QPushButton("Meny (M)");
    this->b_meny->setFocusPolicy(Qt::NoFocus);
    this->b_up = new QPushButton("Up");
    this->b_up->setFocusPolicy(Qt::NoFocus);
    this->b_return = new QPushButton("Return (R)");
    this->b_return->setFocusPolicy(Qt::NoFocus);
    this->b_left = new QPushButton("Left");
    this->b_left->setFocusPolicy(Qt::NoFocus);
    this->b_enter = new QPushButton("Enter");
    this->b_enter->setFocusPolicy(Qt::NoFocus);
    this->b_right = new QPushButton("Right");
    this->b_right->setFocusPolicy(Qt::NoFocus);
    this->b_down = new QPushButton("Down");
    this->b_down->setFocusPolicy(Qt::NoFocus);

    this->b_volume_up = new QPushButton("+");
    this->b_volume_up->setFocusPolicy(Qt::NoFocus);
    this->b_volume_down = new QPushButton("-");
    this->b_volume_down->setFocusPolicy(Qt::NoFocus);

    l->addWidget(b_meny, 1, 1);
    l->addWidget(b_up, 2, 2);
    l->addWidget(b_return, 1, 3);
    l->addWidget(b_left, 3, 1);
    l->addWidget(b_enter, 3, 2);
    l->addWidget(b_right, 3, 3);
    l->addWidget(b_down, 4, 2);
    l->addWidget(b_volume_up, 1, 4);
    l->addWidget(b_volume_down, 2, 4);

    if (!this->server->listen(QHostAddress::LocalHost, cfg->port)) {
        exit(errno);
    }

    this->installEventFilter(this);

    connect(this->server, SIGNAL(newConnection()), this, SLOT(new_connection()));
}

