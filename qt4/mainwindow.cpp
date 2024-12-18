#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          ui(new Ui::MainWindow),
          progressValue(0) // Инициализация начального значения прогресса
{
    ui->setupUi(this);

    // Настройка RadioButton
    ui->radioButton1->setText("Option 1");
    ui->radioButton2->setText("Option 2");

    // Настройка ComboBox
    ui->comboBox->addItems({"Item 1", "Item 2", "Item 3", "Item 4", "Item 5",
                            "Item 6", "Item 7", "Item 8", "Item 9", "Item 10"});

    // Настройка кнопки
    ui->pushButton->setText("Start");
    ui->pushButton->setCheckable(true); // Переключение типа кнопки на Toggle

    // Настройка ProgressBar
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(10);
    ui->progressBar->setValue(progressValue);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    // Увеличение значения прогресс-бара на 10%
    progressValue += 1;

    // Сброс значения, если оно превышает максимум
    if (progressValue > 10) {
        progressValue = 0;
    }

    ui->progressBar->setValue(progressValue);
}