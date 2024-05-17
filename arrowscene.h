#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include <QGraphicsScene>

//

QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
class DiagramItem;
QT_END_NAMESPACE

enum LineType {
     lineType1 = 1,  //横竖
     lineType2,      //竖横
     lineType3,      //横竖横
     lineType4       //竖横竖
};

class Arrow : public QGraphicsLineItem
  {
  public:
      enum { Type = UserType + 4 };

     Arrow(DiagramItem *startItem, DiagramItem *endItem,
     QGraphicsItem *parent = 0);
     ~Arrow() {m_bDeleteFlag = true;}

     int type() const override { return Type; }
     QRectF boundingRect() const override;
     QPainterPath shape() const override;
     void setColor(const QColor &color) { myColor = color; }
     DiagramItem *startItem() const { return myStartItem; }
     DiagramItem *endItem() const { return myEndItem; }
     void setItemId(QString startItemId ,QString startEndId);
     void updatePosition();
     QString getStartId(){return startId;}
     QString getEndId(){return endId;}

     void setStartItem(DiagramItem *startItem){ myStartItem = startItem; }
     void setEndItem(DiagramItem *endItem){ myEndItem = endItem; }

     void setArrowFlag(bool IsArrow){bisArrow = IsArrow;}
     bool getArrowFlag(){return bisArrow;}
     bool getDeleteFlage() {return m_bDeleteFlag;}
     void DrawArrow(QPainter *painter, QPointF startPt, QPointF endPt, bool bArrow);
     void ThreeLine(QPainter *painter, QPointF startPt, QPointF endPt);//三段线
     void TwoLine(QPainter *painter, QPointF startPt, QPointF endPt); //两段线
     //void SetLineStyle(bool bVhvLine);//线段的折线风格
     //void SetLineType(int nLineType);//线段的数量
     void SetLineType(LineType lineType);
     int GetLineType() {return m_lineType;}
     void DrawLine(QPainter *painter, QPointF startPt, QPointF endPt);
 protected:
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

 private:
     DiagramItem *myStartItem;
     DiagramItem *myEndItem;
     QColor myColor;
     QPolygonF arrowHead;
     QString startId;
     QString endId;
     bool bisArrow;
     bool m_bDeleteFlag;//
     LineType m_lineType;
     //bool m_bVhvLine;//true三段线，竖横竖; false三段线 横竖横
     //bool m_bVhLine;// true两段线 竖横; false 两段线 横竖
     //int m_nLineType;//2-2段线，3-3段线
 };

inline void Arrow::setItemId(QString startItemId ,QString startEndId){
    startId = startItemId;
    endId = startEndId;
}

 #endif // ARROW_H
