#include "Stopwatch.h"

Stopwatch::Stopwatch(QObject *parent)
    : QObject(parent), timer(new QTimer(this)), lastLapTime(0), running(false) {
    connect(timer, &QTimer::timeout, this, &Stopwatch::updateTime);
}

void Stopwatch::start() {
    if (!running) {
        running = true;
        elapsed.start();
        timer->start(100); // Обновляем каждые 0.1 сек
    }
}

void Stopwatch::stop() {
    if (running) {
        running = false;
        timer->stop();
    }
}

void Stopwatch::reset() {
    stop();
    lastLapTime = 0;
    emit timeUpdated("0.0");
}

QString Stopwatch::lap() {
    if (!running) return QString();

    qint64 currentLapTime = elapsed.elapsed();
    QString lapTime = QString::number((currentLapTime - lastLapTime) / 1000.0, 'f', 1);
    lastLapTime = currentLapTime;

    return lapTime;
}

QString Stopwatch::getCurrentTime() const {
    if (!running) return "0.0";
    return QString::number(elapsed.elapsed() / 1000.0, 'f', 1);
}

bool Stopwatch::isRunning() const {
    return running;
}

void Stopwatch::updateTime() {
    emit timeUpdated(getCurrentTime());
}
