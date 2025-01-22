#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QVector>
#include "dbdata.h"
#include "database.h"

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
public slots:
    void onReceiveDbData(const QVector<QString> &data); // Для получения данных от DbData

private:
    Ui::MainWindow *ui;
    DbData *dbDataDialog;
    QSqlTableModel *tableModel;
    QSqlQueryModel *queryModel;
    QSqlDatabase dataBase;

    void loadAllMovies();
    void loadMoviesByCategory(const QString &category);
};

#endif // MAINWINDOW_H
