#ifndef DATABASE_H
#define DATABASE_H

#include <QTableWidget>
#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QTableWidgetItem>
#include <QSqlDatabase>

#define POSTGRE_DRIVER "QPSQL"
#define DB_NAME "MyDB"

//Количество полей данных необходимых для подключения к БД
#define NUM_DATA_FOR_CONNECT_TO_DB 5

//Перечисление полей данных
enum fieldsForConnect{
    hostName = 0,
    dbName = 1,
    login = 2,
    pass = 3,
    port = 4
};

//Типы запросов
enum requestType{

    requestAllFilms = 1,
    requestComedy   = 2,
    requestHorrors  = 3

};



class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    void AddDataBase(const QString &driver, const QString &nameDB);
    void ConnectToDataBase(const QVector<QString> &data);
    void DisconnectFromDataBase(const QString &nameDb);
    void RequestToDB(const QString &request);
    QSqlError GetLastError();

signals:
    void sig_SendStatusConnection(bool status);
    void sig_SendQueryResult(bool success);
    void sig_SendDataFromDB(const QTableWidget *widget, int typeRequest);


private:
    QSqlDatabase dataBase;
};

#endif // DATABASE_H
