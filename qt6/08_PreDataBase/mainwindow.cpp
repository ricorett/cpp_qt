#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dbDataDialog(new DbData(this))
    , tableModel(nullptr)
    , queryModel(nullptr)
{
    ui->setupUi(this);

    connect(dbDataDialog, &DbData::sig_sendData, this, &MainWindow::onReceiveDbData);
    dbDataDialog->exec();

    ui->comboBoxFilter->addItem("Все");      // Индекс 0
    ui->comboBoxFilter->addItem("Комедии"); // Индекс 1
    ui->comboBoxFilter->addItem("Ужасы");   // Индекс 2

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);


    loadAllMovies();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dbDataDialog;
}


void MainWindow::onReceiveDbData(const QVector<QString> &data)
{
    if (data.isEmpty()) {
        qDebug() << "Данные для подключения не получены.";
        return;
    }

    if (QSqlDatabase::contains("DefaultConnection")) {
        dataBase = QSqlDatabase::database("DefaultConnection");
    } else {
        dataBase = QSqlDatabase::addDatabase("QPSQL", "DefaultConnection");
    }

    dataBase.setHostName(data[hostName]);
    dataBase.setDatabaseName(data[dbName]);
    dataBase.setUserName(data[login]);
    dataBase.setPassword(data[pass]);
    dataBase.setPort(data[port].toInt());

    if (dataBase.open()) {
        qDebug() << "Успешное подключение к базе данных.";
    } else {
        qDebug() << "Ошибка подключения к базе данных: " << dataBase.lastError().text();
        return;
    }

    // Загружаем данные после успешного подключения
    loadAllMovies();
}

void MainWindow::loadAllMovies()
{
    if (tableModel) {
        delete tableModel;
    }

    // Передаем dataBase вторым параметром
    tableModel = new QSqlTableModel(this, dataBase);
    tableModel->setTable("film");
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    tableModel->setHeaderData(1, Qt::Horizontal, "Название фильма");
    tableModel->setHeaderData(2, Qt::Horizontal, "Описание фильма");

    tableModel->select();
    ui->tableView->setModel(tableModel);
}

void MainWindow::loadMoviesByCategory(const QString &category)
{
    if (queryModel) {
        delete queryModel;
    }

    queryModel = new QSqlQueryModel(this);

    QString queryText = R"(
        SELECT f.title, f.description
        FROM film f
        JOIN film_category fc ON f.film_id = fc.film_id
        JOIN category c ON c.category_id = fc.category_id
        WHERE c.name = :category
    )";

    QSqlQuery query(dataBase);  // Указываем подключение к БД
    query.prepare(queryText);
    query.bindValue(":category", category);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return;
    }

    queryModel->setQuery(query);
    queryModel->setHeaderData(0, Qt::Horizontal, "Название фильма");
    queryModel->setHeaderData(1, Qt::Horizontal, "Описание фильма");

    ui->tableView->setModel(queryModel);
}

void MainWindow::on_comboBoxFilter_currentIndexChanged(int index)
{
    if (index == 0) {
        loadAllMovies();
    } else if (index == 1) {
        loadMoviesByCategory("Comedy");
    } else if (index == 2) {
        loadMoviesByCategory("Horror");
    }
}

void MainWindow::on_buttonClear_clicked()
{
    ui->tableView->setModel(nullptr); // Очищаем таблицу
}
