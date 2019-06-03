#include "DataReaderWorker.h"
#include <QThread>

#include "DataStorage.h"
#include "DataReader.h"

DataReaderWorker::DataReaderWorker()
{

}

void DataReaderWorker::setDataStorage(DataStorage *storage){
    _DataStorage = storage;
}

void DataReaderWorker::setDataReader(DataReader *reader){
    _DataReader = reader;
}

void DataReaderWorker::doWork()
{
    _DataReader->parseReadFile("C:\\iq_qam32.bin");
}
