#ifndef SENSORWORKER_H
#define SENSORWORKER_H

#include <QObject>

class SensorWorker : public QObject
{
    Q_OBJECT
public:
    explicit SensorWorker(QObject *parent = nullptr);

signals:
};

#endif // SENSORWORKER_H
