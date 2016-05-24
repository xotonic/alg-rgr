
#include "edge_view.h"
#include "node_view.h"

#include <math.h>

#include <QPainter>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;


EdgeView::EdgeView(NodeView *sourceNode, NodeView *destNode, EdgeType type, bool drawWeights, int w1, int w2)
    : arrowSize(10), _type(type),
    _draw_weights(drawWeights), _w1(w1), _w2(w2)
{
    setAcceptedMouseButtons(0);
    source = sourceNode;
    dest = destNode;
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
}



NodeView *EdgeView::sourceNode() const
{
    return source;
}

NodeView *EdgeView::destNode() const
{
    return dest;
}



void EdgeView::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + edgeOffset ;
        destPoint = line.p2() - edgeOffset ;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}



QRectF EdgeView::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra -15, -extra, extra +15, extra);
}



void EdgeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;


    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;
    
    // Draw the line itself
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
    
    QPointF offset = QPointF(sin(angle)*3, cos(angle)*3);
    //if (_type == both_directed)
    //    painter->drawLine(line.translated(offset));
    
    // Draw the arrows
    

    QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + Pi / 3) * arrowSize,
                                                  cos(angle + Pi / 3) * arrowSize);
    QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                                  cos(angle + Pi - Pi / 3) * arrowSize);
    QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
                                              cos(angle - Pi / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
                                              cos(angle - Pi + Pi / 3) * arrowSize);

    painter->setBrush(Qt::black);
    
    if (_type == undirected)
    {
        // no arrows
    }
    else if (_type == directed)
    {
        
        painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
    }
    else if (_type == both_directed)
    {
        //painter->drawPolygon(QPolygonF() << line.p1()+ offset  
        //                     << sourceArrowP1+ offset 
        //                     << sourceArrowP2 + offset);
        //painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
    }
    
    if (_draw_weights)
    {
        QRectF textRect( 0, 0,
                            30, 20);
        QString message(QString::number(_w1));
        if (_type == both_directed ) message.append("/").append(QString::number(_w2));
    
        QFont font = painter->font();
        //    font.setBold(true);
        font.setPointSize(12);
        
        painter->setFont(font);
        painter->setBrush(Qt::white);
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(textRect.translated(-textRect.center()).translated( line.pointAt(0.5)));
        painter->setPen(Qt::black);
        painter->drawText(textRect.translated(-textRect.center()).translated( line.pointAt(0.5)),Qt::AlignCenter, message);
    }
}

