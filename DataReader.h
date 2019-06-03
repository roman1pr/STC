#ifndef DATAREADER_H
#define DATAREADER_H

#include <QString>
#include <QFile>
#include <QDomElement>
#include <QVector>

class DataStorage;

class DataReader
{
public:
    DataReader();

    void parseReadFile(QString fileName);
    void setDataStorage(DataStorage* storage);

private:

    QFile* openFile(QString fileName);
    void readFileMarksXML(QFile* file);
    void readMarks(const QDomNode &node);

    void readPoints(QFile* file);

    void showErrorMessage(QString title, QString Text);

private:

    DataStorage* _DataStorage;
};

#endif // DATAREADER_H
