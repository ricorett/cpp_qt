#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBoxFilter_currentIndexChanged(int index); // Обработка изменения фильтра
    void on_buttonClear_clicked(); // Очистка таблицы

private:
    Ui::MainWindow *ui;
    QSqlTableModel *tableModel; // Модель для отображения всех фильмов
    QSqlQueryModel *queryModel; // Модель для отображения фильмов по категориям

    void loadAllMovies();           // Загрузка всех фильмов
    void loadMoviesByCategory(const QString &category); // Загрузка фильмов по категории
};

#endif // MAINWINDOW_H