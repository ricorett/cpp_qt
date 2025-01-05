#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
        , tableModel(nullptr)
        , queryModel(nullptr)
{
    ui->setupUi(this);

    // Настройка ComboBox для фильтрации
    ui->comboBoxFilter->addItem("Все");      // Индекс 0
    ui->comboBoxFilter->addItem("Комедии"); // Индекс 1
    ui->comboBoxFilter->addItem("Ужасы");   // Индекс 2

    // Настройка TableView
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    // Загрузка всех фильмов по умолчанию
    loadAllMovies();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Загрузка всех фильмов
void MainWindow::loadAllMovies()
{
    if (tableModel) {
        delete tableModel; // Удаляем предыдущую модель
    }

    tableModel = new QSqlTableModel(this);
    tableModel->setTable("film"); // Указываем таблицу "film"
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // Настраиваем заголовки
    tableModel->setHeaderData(1, Qt::Horizontal, "Название фильма");
    tableModel->setHeaderData(2, Qt::Horizontal, "Описание фильма");

    tableModel->select(); // Загружаем данные
    ui->tableView->setModel(tableModel); // Устанавливаем модель в TableView
}

// Загрузка фильмов по категории
void MainWindow::loadMoviesByCategory(const QString &category)
{
    if (queryModel) {
        delete queryModel; // Удаляем предыдущую модель
    }

    queryModel = new QSqlQueryModel(this);

    QString queryText = R"(
        SELECT f.title, f.description
        FROM film f
        JOIN film_category fc ON f.film_id = fc.film_id
        JOIN category c ON c.category_id = fc.category_id
        WHERE c.name = :category
    )";

    QSqlQuery query;
    query.prepare(queryText);
    query.bindValue(":category", category);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return;
    }

    queryModel->setQuery(query);
    queryModel->setHeaderData(0, Qt::Horizontal, "Название фильма");
    queryModel->setHeaderData(1, Qt::Horizontal, "Описание фильма");

    ui->tableView->setModel(queryModel); // Устанавливаем модель в TableView
}

// Обработка изменения фильтра
void MainWindow::on_comboBoxFilter_currentIndexChanged(int index)
{
    if (index == 0) { // Все фильмы
        loadAllMovies();
    } else if (index == 1) { // Комедии
        loadMoviesByCategory("Comedy");
    } else if (index == 2) { // Ужасы
        loadMoviesByCategory("Horror");
    }
}

// Очистка таблицы
void MainWindow::on_buttonClear_clicked()
{
    ui->tableView->setModel(nullptr); // Очищаем таблицу
}