#include "DataReader.h"

#include <QMessageBox>
#include <QXmlStreamReader>
#include <QDebug>
#include <QtXml>

#include "DataStorage.h"

DataReader::DataReader()
{

}

void DataReader::parseReadFile(QString fileName){
   readFileMarksXML(openFile(fileName));
}

QFile* DataReader::openFile(QString fileName){

    auto xmlFile = new QFile(fileName);

    if (!xmlFile->exists() || !xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {

        showErrorMessage("Load XML File Problem",
                         "Couldn't open " + fileName + " to load settings for download"
                    );

        return nullptr;
    }

    return xmlFile;
}

void DataReader::readFileMarksXML(QFile* file){
    if (file) {
        QDomDocument doc;

        if (doc.setContent(file)){
            QDomElement elem = doc.documentElement();
            readMarks(elem);
        }

        file->close();
    }
}

void DataReader::readMarks(const QDomNode &node) {

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

                    auto X = domElement.attributeNode("X").value().toFloat();
                    auto Y = domElement.attributeNode("Y").value().toFloat();

                    _DataStorage->Marks.push_back(Point2D{X, Y});
                }
            }
        }

        domNode = domNode.nextSibling();
    }
}

void DataReader::readPoints(QFile* file){
    QBitArray *ba = new QBitArray(100, false);

    file = new QFile("out");
    if (!file->open(QIODevice::WriteOnly)) {
        qDebug() << "Can not create file";
    return;
    }

    QDataStream *outstream = new QDataStream(file);

    *outstream << *ba;
}

void DataReader::showErrorMessage(QString title, QString Text){
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(Text);
    msgBox.exec();
}


void DataReader::setDataStorage(DataStorage* storage){
    _DataStorage = storage;
}
