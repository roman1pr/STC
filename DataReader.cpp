#include "DataReader.h"

#include <QMessageBox>
#include <QXmlStreamReader>
#include <QtXml>
#include <QDataStream>

#include "DataStorage.h"

DataReader::DataReader()
{

}

void DataReader::parseReadFile(QString fileName)
{
    if (fileName.contains(".xml")){
        readFileMarksXML(openFile(fileName));
    } else {
        readPoints(openFile(fileName));
    }
}

QFile* DataReader::openFile(QString fileName)
{
    auto File = new QFile(fileName);

    if (!File->exists() || !File->open(QIODevice::ReadOnly | QIODevice::Text)) {

        showErrorMessage("Load XML File Problem",
                         "Couldn't open " + fileName + " to load settings for download"
                    );

        return nullptr;
    }

    return File;
}

void DataReader::readFileMarksXML(QFile* file)
{
    if (file) {
        QDomDocument doc;

        if (doc.setContent(file)){
            QDomElement elem = doc.documentElement();
            readMarks(elem);
        }

        file->close();
    }
}

void DataReader::readMarks(const QDomNode &node)
{
    if (!_DataStorage) {
        showErrorMessage("DataStorage Problem",
                         "DataStorage not init or not set in DataReader, before read points need to set DataStorage!!!"
                    );
        return;
    }

    QDomNode domNode = node.firstChild();

    while(!domNode.isNull()) {
        if (domNode.isElement()){
            QDomElement domElement = domNode.toElement();
            if (!domElement.isNull()){
                if (domElement.tagName() == "Point"){

                    auto x = domElement.attributeNode("X").value().toDouble();
                    auto y = domElement.attributeNode("Y").value().toDouble();

                    _DataStorage->Marks.push_back(Point2D{x, y});
                }
            }
        }

        domNode = domNode.nextSibling();
    }
}

void DataReader::readPoints(QFile* file)
{
    if (!file)
        return;

    QDataStream dataStream(file);
    dataStream.setByteOrder(QDataStream::LittleEndian);

    int XY = 0;
    qint16 x = 0;
    qint16 y = 0;

    while ( !dataStream.atEnd() ) {

            // Pop off a 32 bit int
            qint16 temp;
            dataStream >> temp;

            if (XY == 0) {
                x = temp;
            } else {
                y = temp;
                _DataStorage->pushPoint(Point2D{(double)x , (double)y  });
            }

            XY = (XY + 1) % 2;
        }

    file->close();
}

void DataReader::showErrorMessage(QString title, QString Text)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(Text);
    msgBox.exec();
}


void DataReader::setDataStorage(DataStorage* storage)
{
    _DataStorage = storage;
}
