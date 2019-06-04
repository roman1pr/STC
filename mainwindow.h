#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <mygraphicview.h>

class DataStorage;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setDataStorage(DataStorage *storage);

    void addThread();
private:
    Ui::MainWindow *ui;
    MyGraphicView   *GraphicView;     // Наш кастомный виджет
};

#endif // MAINWINDOW_H
