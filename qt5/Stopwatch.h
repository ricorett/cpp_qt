#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QElapsedTimer>
#include <QTimer>

class Stopwatch : public QObject {
    Q_OBJECT

public:
    explicit Stopwatch(QObject *parent = nullptr);

    void start();
    void stop();
    void reset();
    QString lap();

    QString getCurrentTime() const;
    bool isRunning() const;

signals:
    void timeUpdated(const QString &time); // Сигнал обновления времени

private slots:
    void updateTime();

private:
    QTimer *timer;
    QElapsedTimer elapsed;
    qint64 lastLapTime;
    bool running;          // Флаг состояния секундомера
};

#endif // STOPWATCH_H
