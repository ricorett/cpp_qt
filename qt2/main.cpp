//#include <QApplication>
//#include <QPushButton>
//
//int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);
//
//    QPushButton button("Нажми меня");
//    QObject::connect(&button, &QPushButton::clicked, &app, &QApplication::quit);
//
//    button.show();
//    return app.exec();
//}
#include <QApplication>
#include <QPushButton>
#include <QtSql>
#include <QtNetwork>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    
    return QApplication::exec();
}
