#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>

#include "DataStorage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GraphicView   = new MyGraphicView();

    ui->graphicLayout->addWidget(GraphicView);
}

void MainWindow::setDataStorage(DataStorage *storage){
    GraphicView->setDataStorage(storage);
}

MainWindow::~MainWindow()
{
    delete ui;
}
