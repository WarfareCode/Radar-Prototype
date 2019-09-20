#include "diagramitem.h"
#include "arrow.h"
#include "radarscene.h"
#include<QGraphicsScene>
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsBlurEffect>
/**
* @projectName   prototype_v0719
* @brief         这里就是悬浮框中雷达内部组件的图表类。
* @author        Antrn
* @date          2019-08-12
*/



DiagramItem::DiagramItem(DiagramType diagramType, QMenu *contextMenu,
             QGraphicsItem *parent): QGraphicsPolygonItem(parent)
{
    myDiagramType = diagramType;
    myContextMenu = contextMenu;

    QPainterPath path;
    //这里元素的大小和在场景中是一样的，修改了都会变。
    switch (myDiagramType) {
        //暂不使用
        case Comp3:
            path.moveTo(200, 50);
            path.arcTo(150, 0, 50, 50, 0, 90);
            path.arcTo(50, 0, 50, 50, 90, 90);
            path.arcTo(50, 50, 50, 50, 180, 90);
            path.arcTo(150, 50, 50, 50, 270, 90);
            path.lineTo(200, 25);
            myPolygon = path.toFillPolygon();
            break;
        //立着正方形
        case Comp2:
            myPolygon << QPointF(-50, 0) << QPointF(0, 50)
                      << QPointF(50, 0) << QPointF(0, -50)
                      << QPointF(-50, 0);
            break;
        //正方形
        case Comp1:
            path.moveTo(-50, -50);
            path.addText(QPointF(0,0),QFont("Helvetica", 20),QString("hhh"));
            path.moveTo(50, -50);
//            path.lineTo(50, -50);
            path.lineTo(50, 50);
            path.lineTo(-50, 50);
            path.lineTo(-50, -50);

//            myPolygon << QPointF(-50, -50) << QPointF(50, -50)
//                      << QPointF(50, 50) << QPointF(-50, 50)
//                      << QPointF(-50, -50);
            myPolygon = path.toFillPolygon();
            break;
        //默认 菱形，IO
        default:
            myPolygon << QPointF(-60, -40) << QPointF(-35, 40)
                      << QPointF(60, 40) << QPointF(35, -40)
                      << QPointF(-60, -40);
            break;
    }
    setPolygon(myPolygon);

    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    //坐标变化
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

//QRectF DiagramItem::boundingRect()
//{
//    qreal adjust=0.5;
//    return QRectF(0-adjust,0-adjust,100+adjust,100+adjust);
//}

//void DiagramItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
//{
//    painter->drawRect(0,0,100,100);
//    painter->drawPixmap(0,0,48,48, QPixmap(":/img/radar.png"));
//}

void DiagramItem::removeArrow(Arrow *arrow)
{
    int index = arrows.indexOf(arrow);

    if (index != -1)
        arrows.removeAt(index);
}

void DiagramItem::removeArrows()
{
    foreach (Arrow *arrow, arrows) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
//        RadarScene *sce = dynamic_cast<RadarScene*>(this->scene());
//        sce->idList.removeOne(arrow->itemId);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void DiagramItem::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

QPixmap DiagramItem::image() const
{
    QPixmap pixmap(250, 250);
//    pixmap.fill(Qt::transparent);
    QString iconName;
    switch (diagramType()) {
        case DiagramItem::DiagramType::Comp1 :
            iconName = "FDPC";
            break;
        case DiagramItem::DiagramType::Comp2 :
            iconName = "CFAR";
            break;
        case DiagramItem::DiagramType::Comp4 :
            iconName = "MTD";
            break;
        default:
            break;
    }
    QString itemIcon = ":/img/" +iconName+".ico";
    pixmap.convertFromImage(QImage(itemIcon));
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));
    painter.translate(125, 125);
//    painter.drawPolyline(myPolygon);
    painter.setRenderHint(QPainter::Antialiasing, true);
    return pixmap;
}

//void DiagramItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
//{
//    setCursor(Qt::ArrowCursor);
//}

//void DiagramItem::mousePressEvent(QGraphicsSceneMouseEvent *)
//{
//    setFocus();
    // 当移动的时候改变光标
//    setCursor(Qt::ClosedHandCursor);
//}

//void DiagramItem::KeyPressEvent(QKeyEvent *event)
//{
//    if(event->key() == Qt::Key_Down){
//        moveBy(0, 10);
          //？为什么不是想象中的移动图形项，而是scene
//    }
//    switch (event->key()) {
//        case Qt::Key_1:{
//            QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect;
//            blurEffect->setBlurHints(QGraphicsBlurEffect::QualityHint);
//            blurEffect->setBlurRadius(8);
//            setGraphicsEffect(blurEffect);
//            break;
//        }
//        case Qt::Key_5:{
//            graphicsEffect()->setEnabled(false);
//            break;
//        }
//    }
//}

//void DiagramItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
//{
//    setCursor(Qt::OpenHandCursor);
//    setToolTip("component");
//}

//右键菜单，保持一致
void DiagramItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}

QVariant DiagramItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    //检测位置发生变化
    if (change == QGraphicsItem::ItemPositionChange) {
        if(this->init_pos_set != 0){
//            qDebug() << "现在的位置： " << this->pos();
            // 获取最新位置，更新doc
            RadarScene *scene = dynamic_cast<RadarScene *>(this->scene());
            scene->updateXmlItemsPos(this->pos(), this);
        }else{
            init_pos_set = 1;
        }
        foreach (Arrow *arrow, arrows) {
            arrow->updatePosition();
        }
    }
//    update();
    return value;
}
