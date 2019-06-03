#include "mainwindow.h"
#include <QApplication>

#include "DataReader.h"
#include "DataStorage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataStorage Storage;

    DataReader reader;
    reader.setDataStorage(&Storage);
    reader.parseReadFile("C:\\data.xml");

    MainWindow w;
    w.setDataStorage(&Storage);
    w.show();

    return a.exec();
}
