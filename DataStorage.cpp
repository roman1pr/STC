#include "DataStorage.h"

DataStorage::DataStorage()
{

}

void DataStorage::pushPoint(Point2D point)
{
    m_mutex.lock();
    Points.push_back(point);
    m_mutex.unlock();
}

Point2D DataStorage::getPoint(int i)
{
    QMutexLocker locker (&m_mutex);
    return Points.at(i);
}

int DataStorage::getPointsSize(){
    QMutexLocker locker (&m_mutex);
    return Points.size();
}
