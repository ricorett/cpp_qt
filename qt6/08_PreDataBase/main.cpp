#include "mainwindow.h"
#include "dbdata.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    DbData dbData;

    w.show();
    return app.exec();
}
