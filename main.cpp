#include <QApplication>

#include "keyboarde.h"

int main (int argc, char *argv[]) {
    QApplication app(argc, argv);
    keyboarde *k = new keyboarde();
    k->show();
    return app.exec();
}
