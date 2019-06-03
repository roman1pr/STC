#ifndef DATAREADERWORKER_H
#define DATAREADERWORKER_H

#include <QObject>

class DataStorage;
class DataReader;

class DataReaderWorker : public QObject
{
public:
    DataReaderWorker();

    void setDataStorage(DataStorage *storage);
    void setDataReader(DataReader *reader);

public slots:
    void doWork();
signals:
    void send(int);

private:
    DataStorage* _DataStorage;
    DataReader*  _DataReader;
};

#endif // DATAREADERWORKER_H
