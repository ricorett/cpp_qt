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
    dbDataDialog->exec(); // Открываем окно ввода данных подключения

    // Проверяем, есть ли уже элементы перед добавлением
    if (ui->comboBoxFilter->count() == 0) {
        ui->comboBoxFilter->addItem("Все");
        ui->comboBoxFilter->addItem("Комедии");
        ui->comboBoxFilter->addItem("Ужасы");
    }

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dbDataDialog;
}

/*!
 * \brief Обработчик получения данных для подключения
 */
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

    bool status = dataBase.open();

    qDebug() << (status ? "Подключение успешно." : "Ошибка подключения: " + dataBase.lastError().text());

    emit onStatusConnection(status);

    if (status) {
        on_comboBoxFilter_currentIndexChanged(ui->comboBoxFilter->currentIndex());
    }
}

/*!
 * \brief Слот обновления статуса подключения в UI
 */
void MainWindow::onStatusConnection(bool status)
{
    if (status) {
        qDebug() << "Соединение с БД установлено.";
        ui->lb_statusConnect->setText("Подключено");
        ui->lb_statusConnect->setStyleSheet("color: green;");
    } else {
        qDebug() << "Соединение с БД не удалось.";
        ui->lb_statusConnect->setText("Ошибка подключения");
        ui->lb_statusConnect->setStyleSheet("color: red;");
    }
}

/*!
 * \brief Загрузка всех фильмов
 */
void MainWindow::loadAllMovies()
{
    if (!queryModel) {
        queryModel = new QSqlQueryModel(this);
    }

    QString queryText = R"(
        SELECT title, description FROM film
    )";

    QSqlQuery query(dataBase);
    if (!query.exec(queryText)) {
        qDebug() << "Ошибка выполнения запроса: " << query.lastError().text();
        return;
    }

    queryModel->setQuery(query);
    queryModel->setHeaderData(0, Qt::Horizontal, "Название фильма");
    queryModel->setHeaderData(1, Qt::Horizontal, "Описание фильма");

    ui->tableView->setModel(queryModel);
}

/*!
 * \brief Загрузка фильмов по категории
 */
void MainWindow::loadMoviesByCategory(const QString &category)
{
    if (!queryModel) {
        queryModel = new QSqlQueryModel(this);
    }

    QString queryText = R"(
        SELECT f.title, f.description
        FROM film f
        JOIN film_category fc ON f.film_id = fc.film_id
        JOIN category c ON c.category_id = fc.category_id
        WHERE c.name = :category
    )";

    QSqlQuery query(dataBase);
    query.prepare(queryText);
    query.bindValue(":category", category);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса: " << query.lastError().text();
        return;
    }

    queryModel->setQuery(query);
    queryModel->setHeaderData(0, Qt::Horizontal, "Название фильма");
    queryModel->setHeaderData(1, Qt::Horizontal, "Описание фильма");

    ui->tableView->setModel(queryModel);
}

/*!
 * \brief Обработчик смены жанра
 */
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

/*!
 * \brief Очистка таблицы
 */
void MainWindow::on_buttonClear_clicked()
{
    ui->tableView->setModel(nullptr);
}

void MainWindow::on_pb_request_clicked()
{
    int index = ui->comboBoxFilter->currentIndex();

    on_comboBoxFilter_currentIndexChanged(index);

    qDebug() << "Запрос обновлен для категории: " << ui->comboBoxFilter->currentText();
}