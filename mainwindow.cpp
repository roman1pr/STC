#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QThread>

#include "DataStorage.h"
#include "DataReaderWorker.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GraphicView   = new MyGraphicView();

    ui->graphicLayout->addWidget(GraphicView);
}

void MainWindow::setDataStorage(DataStorage *storage)
{
    GraphicView->setDataStorage(storage);
}

void MainWindow::addThread()
{
    QThread *thread= new QThread;
    DataReaderWorker * worker = new DataReaderWorker();

    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));

    worker->moveToThread(thread);
    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
