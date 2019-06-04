#ifndef DATAREADERWORKER_H
#define DATAREADERWORKER_H

#include <QObject>

class DataReader;

class DataReaderWorker : public QObject
{
    Q_OBJECT
public:
    DataReaderWorker();

    void setDataReader(DataReader *reader);

public slots:
    void doWork();
signals:
    void send(int);

private:
    DataReader*  _DataReader;
};

#endif // DATAREADERWORKER_H
