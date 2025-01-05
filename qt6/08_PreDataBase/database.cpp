#include "database.h"

DataBase::DataBase(QObject *parent)
        : QObject(parent), dataBase(QSqlDatabase()) {}

DataBase::~DataBase() {
    if (dataBase.isOpen()) {
        dataBase.close();
    }
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(const QString &driver, const QString &nameDB) {
    dataBase = QSqlDatabase::addDatabase(driver, nameDB);
}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(const QVector<QString> &data) {
    dataBase.setHostName(data[hostName]);
    dataBase.setDatabaseName(data[dbName]);
    dataBase.setUserName(data[login]);
    dataBase.setPassword(data[pass]);
    dataBase.setPort(data[port].toInt());

    bool status = dataBase.open();
    if (status) {
        qDebug() << "Connection to database established successfully.";
    } else {
        qDebug() << "Failed to connect to database:" << dataBase.lastError().text();
    }

    emit sig_SendStatusConnection(status);
}

/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(const QString &nameDb) {
    if (dataBase.isOpen()) {
        dataBase.close();
        qDebug() << "Disconnected from database:" << nameDb;
    }
}
/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */


void DataBase::RequestToDB(const QString &request) {
    QSqlQuery query(dataBase);
    if (!query.exec(request)) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        emit sig_SendQueryResult(false);
        return;
    }


    auto *tableWidget = new QTableWidget();
    tableWidget->setColumnCount(query.record().count());
    tableWidget->setRowCount(0);


    for (int col = 0; col < query.record().count(); ++col) {
        tableWidget->setHorizontalHeaderItem(col, new QTableWidgetItem(query.record().fieldName(col)));
    }

    int row = 0;
    while (query.next()) {
        tableWidget->insertRow(row);
        for (int col = 0; col < query.record().count(); ++col) {
            tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }
        ++row;
    }

    // Отправка данных через сигнал
    emit sig_SendDataFromDB(tableWidget, 0 /*typeRequest*/);
    emit sig_SendQueryResult(true);
}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */

QSqlError DataBase::GetLastError() {
    return dataBase.lastError();
}
