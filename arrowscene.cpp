#include "arrowscene.h"
#include <qmath.h>
#include <QPen>
#include <QPainter>
#include <QDebug>


Arrow::Arrow(DiagramItem *startItem, DiagramItem *endItem, QGraphicsItem *parent)
     : QGraphicsLineItem(parent)
{
     m_bDeleteFlag = false;//1 sdl
    myStartItem = startItem;
      myEndItem = endItem;
      setFlag(QGraphicsItem::ItemIsSelectable, true);
      myColor = Qt::black;
      setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
      bisArrow = true;
      if(myStartItem){startId = myStartItem->getItemId();}
      if(myEndItem){endId = myEndItem->getItemId();}
     m_lineType = LineType::lineType1;
}


  QRectF Arrow::boundingRect() const
  {
      qreal extra = (pen().width() + ) / 2.0;

      return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                        line().p2().y() - line().p1().y()))
         .normalized()
          .adjusted(-extra, -extra, extra, extra);
 }

  QPainterPath Arrow::shape() const
  {
      QPainterPath path = QGraphicsLineItem::shape();
      path.addPolygon(arrowHead);
      return path;
 }

  void Arrow::updatePosition()
  {
      QPointF endPt = mapFromItem(myEndItem, 0, 0);
      QLineF line(mapFromItem(myStartItem, 0, 0), endPt);
      setLine(line);
}


 //! [3]

 //! [4]
 void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
           QWidget *)
 {
     if(myStartItem == NULL || myEndItem == NULL) return;
     if(myStartItem->GetDeleteFlag() || myEndItem->GetDeleteFlag()) return;
     if (myStartItem->collidesWithItem(myEndItem))
         return;

     QPointF start = myStartItem->pos();
     QPointF end = myEndItem->pos();
     if(qFuzzyCompare(start.x(), end.x())){ //如果在同一竖直或水平线时，直接连接两节点中心点
         DrawArrow(painter, start, end, true);
         return;
     }
    if (qFuzzyCompare(start.y(), end.y())) {
         DrawArrow(painter, start, end, true);
         return;
     }

     DrawLine(painter, start, end);
 //    if(m_nLineType == 2){
 //        TwoLine(painter, start, end);
 //    }
 //    else if (m_nLineType == 3) {
 //        ThreeLine(painter, start, end);
 //    }
 }


 void Arrow::DrawArrow(QPainter *painter, QPointF startPt, QPointF endPt, bool bArrow)
 {
     if(endPt == QPointF(0, 0)){
         return;
     }
     QPen myPen = pen();
     myPen.setColor(myColor);
     qreal arrowSize = ;
     painter->setPen(myPen);
     painter->setBrush(myColor);


     QLineF centerLine(startPt, endPt);

     QPolygonF endPolygon;
     endPolygon = myEndItem->polygon();
     QPointF p1 = endPolygon.first() + endPt;
    QPointF p2;
     QPointF intersectPoint;
     QLineF polyLine;
     for (int i = 1; i < endPolygon.count(); ++i) {
         p2 = endPolygon.at(i) + endPt;
         polyLine = QLineF(p1, p2);
         QLineF::IntersectType intersectType =
             polyLine.intersect(centerLine, &intersectPoint);
         if (intersectType == QLineF::BoundedIntersection)
             break;
         p1 = p2;
     }

     setLine(QLineF(endPt, startPt/*myStartItem->pos()*/));


     if (bArrow){
         setLine(QLineF(intersectPoint, startPt/*myStartItem->pos()*/));//如果是箭头所在的线
     }
    double angle = std::atan2(-line().dy(), line().dx());

     QPointF arrowP1 = line().p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                     cos(angle + M_PI / 3) * arrowSize);
     QPointF arrowP2 = line().p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                     cos(angle + M_PI - M_PI / 3) * arrowSize);

     arrowHead.clear();
     arrowHead << line().p1() << arrowP1 << arrowP2;

     painter->drawLine(line());
     //是否画箭头
     if(bArrow){
         painter->drawPolygon(arrowHead);
     }
     if (isSelected()) {
         painter->setPen(QPen(myColor, 1, Qt::DashLine));
         QLineF myLine = line();
         myLine.translate(0, 4.0);
         painter->drawLine(myLine);
         myLine.translate(0,-.0);
         painter->drawLine(myLine);
    }
 }

 void Arrow::ThreeLine(QPainter *painter, QPointF start, QPointF end)
 {
     if(m_lineType == LineType::lineType4){
         qreal midY = (start.y() + end.y()) / 2;
         QPointF startPt = myStartItem->pos();
         QPointF endPt = myEndItem->pos();

        endPt.setX(startPt.x());
         endPt.setY(midY);
         DrawArrow(painter, startPt, endPt, false);

         startPt = endPt;
         endPt.setX(myEndItem->pos().x());
         endPt.setY(startPt.y());
         DrawArrow(painter, startPt, endPt, false);

         startPt = endPt;
         endPt = myEndItem->pos();

         DrawArrow(painter, startPt, endPt, true);
     }
    else if(m_lineType == LineType::lineType3){
         qreal midX = (start.x() + end.x()) / 2;
         QPointF startPt = myStartItem->pos();
         QPointF endPt = myEndItem->pos();

         endPt.setX(midX);
         endPt.setY(startPt.y());
         DrawArrow(painter, startPt, endPt, false);

         startPt = endPt;
         endPt.setX(startPt.x());
         endPt.setY(myEndItem->pos().y());
         DrawArrow(painter, startPt, endPt, false);

         startPt = endPt;
         endPt = myEndItem->pos();
         DrawArrow(painter, startPt, endPt, true);
     }
 }

 void Arrow::TwoLine(QPainter *painter, QPointF startPt, QPointF endPt)
 {
     if(m_lineType == LineType::lineType2){
         endPt.setX(startPt.x());
         endPt.setY(endPt.y());
         DrawArrow(painter, startPt, endPt, false);

        startPt = endPt;
        endPt = myEndItem->pos();
         DrawArrow(painter, startPt, endPt, true);
    }
     else if(m_lineType == LineType::lineType1){
         endPt.setY(startPt.y());
         DrawArrow(painter, startPt, endPt, false);

        startPt = endPt;
         endPt = myEndItem->pos();
         DrawArrow(painter, startPt, endPt, true);
     }
 }

 //void Arrow::SetLineStyle(bool bVhvLine)
 //{
 //    m_bVhvLine = bVhvLine;
//}

void Arrow::SetLineType(LineType lineType)
 {
     if(lineType > lineType4 || lineType < lineType1)
         m_lineType = lineType1;
     else{
         m_lineType = lineType;
     }
}

void Arrow::DrawLine(QPainter *painter, QPointF start, QPointF end)
 {
     if(m_lineType == LineType::lineType4){
         qreal midY = (start.y() + end.y()) / 2;
         QPointF startPt = myStartItem->pos();
         QPointF endPt = myEndItem->pos();

         endPt.setX(startPt.x());
         endPt.setY(midY);
         DrawArrow(painter, startPt, endPt, false);

         startPt = endPt;
         endPt.setX(myEndItem->pos().x());
         endPt.setY(startPt.y());
         DrawArrow(painter, startPt, endPt, false);

         startPt = endPt;
         endPt = myEndItem->pos();

         DrawArrow(painter, startPt, endPt, true);
     }
     else if(m_lineType == LineType::lineType3){
         qreal midX = (start.x() + end.x()) / 2;
         QPointF startPt = myStartItem->pos();
         QPointF endPt = myEndItem->pos();

         endPt.setX(midX);
         endPt.setY(startPt.y());
        DrawArrow(painter, startPt, endPt, false);

         startPt = endPt;
         endPt.setX(startPt.x());
         endPt.setY(myEndItem->pos().y());
         DrawArrow(painter, startPt, endPt, false);

         startPt = endPt;
         endPt = myEndItem->pos();
         DrawArrow(painter, startPt, endPt, true);
     }
     else if(m_lineType == LineType::lineType2){
         end.setX(start.x());
         end.setY(end.y());
         DrawArrow(painter, start, end, false);

         start = end;
         end = myEndItem->pos();
         DrawArrow(painter, start, end, true);
     }
     else if(m_lineType == LineType::lineType1){
         end.setY(start.y());
         DrawArrow(painter, start, end, false);

         start = end;
         end = myEndItem->pos();
         DrawArrow(painter, start, end, true);
     }
     else {//默认是linetype1
         m_lineType = LineType::lineType1;
         end.setY(start.y());
         DrawArrow(painter, start, end, false);

         start = end;
         end = myEndItem->pos();
         DrawArrow(painter, start, end, true);
     }
 }
