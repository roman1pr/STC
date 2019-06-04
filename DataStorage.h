#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include "point2d.h"
#include <QVector>
#include <QMutex>

class DataStorage
{
public:
    DataStorage();

    QVector<Point2D> Marks;

    void pushPoint(Point2D point);
    Point2D getPoint(int i);

    int getPointsSize();

private:
    QMutex	m_mutex;

    QVector<Point2D> Points;
};

#endif // DATASTORAGE_H
