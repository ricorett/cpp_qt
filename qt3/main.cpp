#include "DbConnectionDialog.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    DbConnectionDialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        qDebug() << "Host Name:" << dialog.getHostName();
        qDebug() << "Database Name:" << dialog.getDatabaseName();
        qDebug() << "Username:" << dialog.getUsername();
        qDebug() << "Password:" << dialog.getPassword();
        qDebug() << "Port:" << dialog.getPort();
    } else {
        qDebug() << "Connection dialog cancelled.";
    }

    return a.exec();
}