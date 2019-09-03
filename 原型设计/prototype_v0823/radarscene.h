#ifndef RADARSCENE_H
#define RADARSCENE_H

/**
* @projectName   prototype_v0719
* @brief         编辑雷达页面的自定义场景类，上面绘制设计雷达的组件链接。
* @author        Antrn
* @date          2019-08-12
*/
#include "diagramitem.h"
#include "diagramtextitem.h"

#include <QtXml>
#include <QGraphicsScene>
#include <QMenu>
#include <QObject>

class RadarScene : public QGraphicsScene
{
    Q_OBJECT

public:

    //InsertItem默认
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem };

    explicit RadarScene(QMenu *itemMenu, QObject *parent = nullptr);
    QFont font() const { return myFont; }
    QColor textColor() const { return myTextColor; }
    QColor itemColor() const { return myItemColor; }
    QColor lineColor() const { return myLineColor; }
    void setLineColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setItemColor(const QColor &color);
    void setFont(const QFont &font);

    void modifyXmlItems(QPointF pos, DiagramItem *item);
    void updateXmlItemsPos(QPointF pos, DiagramItem *item);
    void modifyXmlArrows(Arrow *arrow, DiagramItem *startItem, DiagramItem *endItem);

    QMenu *getItemMenu(){return myItemMenu;}
    QDomDocument getDoc(){return doc;}
    QList<int> idList;
    int generateUniqueid()
    {
        int i,j;
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        idList.append(qrand()%10);
        for(i=0;i<idList.size();i++)
        {
            bool flag=true;
            while(flag)
            {
                for(j=0;j<i;j++)
                {
                    if(idList[i]==idList[j])
                    {
                        break;
                    }
                }
                if(j<i)
                {
                    idList[i]=rand()%10;
                }
                if(j==i)
                {
                    flag=!flag;
                }
            }
        }
        return idList.back();
    }

public slots:
    void setMode(Mode mode);
    void setItemType(DiagramItem::DiagramType type);
    void editorLostFocus(DiagramTextItem *item);

signals:
    void signal_xy(double x,double y);
    void itemInserted(DiagramItem *item);
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    bool isItemChange(int type);

    DiagramItem::DiagramType myItemType;
    DiagramTextItem *textItem;
    QMenu *myItemMenu;
    Mode myMode;
    bool leftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *line;
    QFont myFont;

    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;

    //存储场景数据
    QDomDocument doc;
    QDomElement Arrs;
    QDomElement Items;
};

#endif // RADARSCENE_H
