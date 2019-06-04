#include "DataReaderWorker.h"
#include <QThread>
#include <QDebug>

#include "DataReader.h"

DataReaderWorker::DataReaderWorker()
{

}

void DataReaderWorker::setDataReader(DataReader *reader)
{
    _DataReader = reader;
}

void DataReaderWorker::doWork()
{
    qDebug() << "doWork";
    _DataReader->parseReadFile("/bin/iq_qam32.bin");
}
