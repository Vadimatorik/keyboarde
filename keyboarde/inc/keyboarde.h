#pragma once

#include <QWidget>
#include <QTcpServer>
#include <QByteArray>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QList>
#include <QTcpSocket>
#include <QPushButton>

class keyboarde : public QWidget {
Q_OBJECT

public:
    explicit keyboarde (QWidget *parent = nullptr);

private slots:
    void new_connection ();
    void server_read ();
    void client_disconnected ();

private:
    QTcpServer *server = nullptr;
    QTcpSocket *socket = nullptr;

private:
    QPushButton *b_meny;
    QPushButton *b_up;
    QPushButton *b_return;
    QPushButton *b_left;
    QPushButton *b_enter;
    QPushButton *b_right;
    QPushButton *b_down;

};