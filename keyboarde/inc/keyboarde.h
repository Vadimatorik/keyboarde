#pragma once

#include <QWidget>
#include <QTcpServer>
#include <QByteArray>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QList>
#include <QTcpSocket>
#include <QPushButton>

struct keyboarde_cfg {
    uint16_t port;
};

class keyboarde : public QWidget {
Q_OBJECT

public:
    explicit keyboarde (QWidget *parent, keyboarde_cfg *cfg);

private slots:
    void new_connection ();
    void server_read ();
    void client_disconnected ();

private:
    bool eventFilter (QObject *obj, QEvent *event);

private:
    void key_handler (QKeyEvent *e, bool state);

private:
    QTcpServer *server = nullptr;
    QTcpSocket *socket = nullptr;

private:
    enum KEY_NUM {
        B_UP = 0,
        B_DOWN = 1,
        B_LEFT = 2,
        B_RIGHT = 3,
        B_ENTER = 4,
        B_RETURN = 5,
        B_MENU = 6
    };

private:
    QPushButton *b_meny;
    QPushButton *b_up;
    QPushButton *b_return;
    QPushButton *b_left;
    QPushButton *b_enter;
    QPushButton *b_right;
    QPushButton *b_down;

};