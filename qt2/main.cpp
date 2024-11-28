#include <QApplication>
#include <QPushButton>
#include <QtSql>
#include <QtNetwork>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QSqlDatabase db;
    QNetworkAccessManager *manager;

    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();

    return QApplication::exec();
}
