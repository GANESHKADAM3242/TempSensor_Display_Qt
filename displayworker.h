#ifndef DISPLAYWORKER_H
#define DISPLAYWORKER_H

#pragma once
#include <QObject>
#include <QMutex>
#include "sensorworker.h"

class DisplayWorker : public QObject
{
    Q_OBJECT
public:
    explicit DisplayWorker(SensorData *data, QMutex *mutex, QObject *parent = nullptr);

public slots:
    void startDisplay();
    void stop();

signals:
    void newReading(double temp, double humidity, int count);
    void finished();

private:
    SensorData *m_data;
    QMutex *m_mutex;
    bool m_running = false;

};

#endif // DISPLAYWORKER_H
