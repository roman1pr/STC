#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QWheelEvent>

class DataStorage;

class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicView(QWidget *parent = 0);
    ~MyGraphicView();

    void setDataStorage(DataStorage *storage);
private:
    QGraphicsScene      *Scene;
    QGraphicsItemGroup  *BaseGroup;
    QGraphicsItemGroup  *PointsGroup;

    DataStorage         *_DataStorage;

    int WidgetWidth;
    int WidgetHeight;

    double ZoomValue;
    double CurZoomValue;

private:

    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);

    void drawPoints();
    void drawMarks();
    void drawGrid();
    void drawGridInfo(QString text, QPointF pos);

    void drawScene();


    void deleteItemsFromGroup(QGraphicsItemGroup *group_1);

signals:

public slots:
     /* слот для обработчика переполнения таймера
                             * в нём будет производиться перерисовка
                             * виджета
                             * */
};

#endif // MYGRAPHICVIEW_H
