#pragma once
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
            void on_pushButton_clicked(); // Слот для обработки нажатия кнопки

private:
    Ui::MainWindow *ui;
    int progressValue; // Хранение текущего значения прогресса
};
