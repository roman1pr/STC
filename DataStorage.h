#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include "point2d.h"
#include <QVector>

class DataStorage
{
public:
    DataStorage();

    QVector<Point2D> Marks;
};

#endif // DATASTORAGE_H
