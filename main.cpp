#include "mainwindow.h"
#include <QApplication>
#include <QThread>

#include "DataReader.h"
#include "DataStorage.h"

#include "DataReaderWorker.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataStorage Storage;

    DataReader reader;
    reader.setDataStorage(&Storage);
    reader.parseReadFile("C:\\256.xml");
//    reader.parseReadFile("C:\\data.xml");


    QThread *thread= new QThread;
    DataReaderWorker * worker = new DataReaderWorker();

    worker->moveToThread(thread);
    thread->start();

    reader.parseReadFile("C:\\iq_qam32.bin");

    MainWindow w;
    w.setDataStorage(&Storage);
    w.show();

    return a.exec();
}
