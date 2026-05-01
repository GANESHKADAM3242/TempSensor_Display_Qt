#ifndef SENSORWORKER_H
#define SENSORWORKER_H

#pragma once
#include <QObject>
#include <QMutex>

struct SensorData
{
    double temperature = 0.0;
    double humidity    = 0.0;
    int readCount      = 0;
};

class SensorWorker : public QObject
{
    Q_OBJECT
public:
    explicit SensorWorker(SensorData *data, QMutex *mutex, QObject *parent = nullptr);

public slots:
        void startReading();
        void stop();

signals:
        void finished();

private:
        SensorData *writeData = nullptr;
        QMutex *sensorMutex   = nullptr;
        bool SensorRunning    = false;
};

#endif // SENSORWORKER_H
