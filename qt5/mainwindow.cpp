#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), stopwatch(new Stopwatch(this)), lapCount(0) {
    ui->setupUi(this);

    // Подключение сигналов и слотов
    connect(ui->startStopButton, &QPushButton::clicked, this, &MainWindow::onStartStopButtonClicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::onResetButtonClicked);
    connect(ui->lapButton, &QPushButton::clicked, this, &MainWindow::onLapButtonClicked);
    connect(stopwatch, &Stopwatch::timeUpdated, this, &MainWindow::updateTimeLabel);

    // Инициализация кнопок
    ui->lapButton->setEnabled(false); // Деактивируем "Круг" при остановке
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onStartStopButtonClicked() {
    if (stopwatch->isRunning()) {
        stopwatch->stop();
        ui->startStopButton->setText("Старт");
        ui->lapButton->setEnabled(false);
    } else {
        stopwatch->start();
        ui->startStopButton->setText("Стоп");
        ui->lapButton->setEnabled(true);
    }
}

void MainWindow::onResetButtonClicked() {
    stopwatch->reset();
    ui->lapBrowser->clear();
    lapCount = 0;
}

void MainWindow::onLapButtonClicked() {
    QString lapTime = stopwatch->lap();
    lapCount++;
    ui->lapBrowser->append(QString("Круг %1, время: %2 сек").arg(lapCount).arg(lapTime));
}

void MainWindow::updateTimeLabel(const QString &time) {
    ui->timeLabel->setText(time);
}
