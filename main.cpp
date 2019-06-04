#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include <QDir>

#include "DataReader.h"
#include "DataStorage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataStorage Storage;

    DataReader reader;
    reader.setDataStorage(&Storage);
    reader.parseReadFile(QDir::currentPath() + "/xml/32.xml");
//    reader.parseReadFile(QDir::currentPath() + "/xml/128.xml");
//    reader.parseReadFile(QDir::currentPath() + "/xml/256.xml");

//    reader.parseReadFile(QDir::currentPath() + "/bin/iq_qam32.bin");

    MainWindow w;

    w.addThread();
    w.setDataStorage(&Storage);
    w.show();

    return a.exec();
}
