#include "MyGraphicView.h"
#include <cmath>

#include "DataStorage.h"

#define GRID_NUM_MULTIPLIER 10
#define SCENE_SIZE_MULTIPLIER 10


MyGraphicView::MyGraphicView(QWidget *parent)
    : QGraphicsView(parent),
      ZoomValue(1),
      CurZoomValue(1)
{
    /* Widget View settings */
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setMinimumHeight(100);
    this->setMinimumWidth(100);

    /* Scene settings */
    Scene = new QGraphicsScene();
    this->setScene(Scene);

    BaseGroup = new QGraphicsItemGroup();
    PointsGroup = new QGraphicsItemGroup();

    Scene->addItem(BaseGroup);
    Scene->addItem(PointsGroup);
}

MyGraphicView::~MyGraphicView()
{

}

void MyGraphicView::setDataStorage(DataStorage *storage)
{
    _DataStorage = storage;
}

void MyGraphicView::wheelEvent(QWheelEvent *event)
{
    // Do a wheel-based zoom about the cursor position
    double angle = event->angleDelta().y();
    double factor = std::pow(1.001, angle);

    CurZoomValue *= factor;

    auto targetViewportPos = event->pos();
    auto targetScenePos = mapToScene(event->pos());

    scale(factor, factor);
    centerOn(targetScenePos);
    QPointF deltaViewportPos = targetViewportPos - QPointF(viewport()->width() / 2.0, viewport()->height() / 2.0);
    QPointF viewportCenter = mapFromScene(targetScenePos) - deltaViewportPos;
    centerOn(mapToScene(viewportCenter.toPoint()));

    //Need to reDraw with zoom level?
    if (std::abs(CurZoomValue / ZoomValue) > 2) {
        ZoomValue = CurZoomValue;
        drawScene();
    }
}

void MyGraphicView::drawPoints()
{
    double pointSize = 20 / ZoomValue;

    int drawCount = 16000;
    int index = 0;

    for (int i = 0; i < std::min(drawCount, _DataStorage->getPointsSize()); i++){
        auto point = _DataStorage->getPoint(i);

        double pointSceneX = point.X + WidgetWidth / 2.0;
        double pointSceneY = point.Y + WidgetHeight / 2.0;

        PointsGroup->addToGroup(Scene->addEllipse(pointSceneX, pointSceneY, pointSize, pointSize, QPen(Qt::green), QBrush(Qt::SolidPattern)));

        index++;
    }

}

void MyGraphicView::drawMarks()
{
    double pointSize = 1 / ZoomValue;

    for (auto point : _DataStorage->Marks) {

        double pointSceneX = point.X + WidgetWidth / 2.0;
        double pointSceneY = point.Y + WidgetHeight / 2.0;

        PointsGroup->addToGroup(Scene->addLine(pointSceneX - pointSize, pointSceneY, pointSceneX + pointSize, pointSceneY, QPen(Qt::red)));
        PointsGroup->addToGroup(Scene->addLine(pointSceneX, pointSceneY - pointSize, pointSceneX, pointSceneY + pointSize, QPen(Qt::red)));
    }
}

void MyGraphicView::drawGrid()
{
    int stepWidth = WidgetWidth / GRID_NUM_MULTIPLIER;
    int stepHeight = WidgetHeight / GRID_NUM_MULTIPLIER;

    double pointSize = 1 / ZoomValue;

    // Vertical lines
    for (int x = 0; x <= WidgetWidth; x += stepWidth){
        BaseGroup->addToGroup(Scene->addLine(x, 0, x, WidgetHeight, QPen(Qt::gray)));

        int showValue = x - WidgetWidth / 2;

        if ((abs(showValue) > 10)){
            drawGridInfo(QString::number(showValue), QPointF(x, WidgetHeight / 2));
        } else {
            BaseGroup->addToGroup(Scene->addLine(x, 0, x, WidgetHeight, QPen(QBrush(Qt::SolidPattern), 5 / ZoomValue)));
        }
    }

    // Horizontal lines
    for (int y = 0; y <= WidgetHeight; y += stepHeight){
        BaseGroup->addToGroup(Scene->addLine(0, y, WidgetWidth, y, QPen(Qt::gray)));

        int showValue = (y - WidgetHeight / 2) * -1;

        if ((abs(showValue) > 10)){
            drawGridInfo(QString::number(showValue), QPointF(WidgetWidth / 2, y));
        } else {
            BaseGroup->addToGroup(Scene->addLine(0, y, WidgetWidth, y, QPen(QBrush(Qt::SolidPattern), 5 / ZoomValue)));
        }
    }

    drawGridInfo("0", QPointF(WidgetWidth / 2, WidgetHeight / 2));
    drawGridInfo("X", QPointF(WidgetWidth, WidgetHeight / 2 - 10));
    drawGridInfo("Y", QPointF(WidgetWidth / 2 - 10, 0));
}

void MyGraphicView::drawGridInfo(QString text, QPointF pos)
{

    QGraphicsTextItem * textItem = new QGraphicsTextItem;
    textItem->setPos(pos);
    textItem->setPlainText(text);

    BaseGroup->addToGroup(textItem);
}

void MyGraphicView::drawScene()
{
    this->deleteItemsFromGroup(BaseGroup);
    this->deleteItemsFromGroup(PointsGroup);

    WidgetWidth = this->width() * SCENE_SIZE_MULTIPLIER;
    WidgetHeight = this->height() * SCENE_SIZE_MULTIPLIER;

    Scene->setSceneRect(0, 0, WidgetWidth, WidgetHeight);

    drawGrid();
    drawPoints();
    drawMarks();
}

void MyGraphicView::resizeEvent(QResizeEvent *event)
{
    drawScene();
    QGraphicsView::resizeEvent(event);
}

void MyGraphicView::deleteItemsFromGroup(QGraphicsItemGroup *group)
{
    foreach( QGraphicsItem *item, Scene->items(group->boundingRect())) {
       if(item->group() == group ) {
          delete item;
       }
    }
}
