
#include "edge_view.h"
#include "node_view.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>


NodeView::NodeView(GraphWidget *graphWidget)
    : graph(graphWidget)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}



void NodeView::addEdge(EdgeView *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<EdgeView *> NodeView::edges() const
{
    return edgeList;
}



void NodeView::calculateForces()
{
    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }



    // Sum up all forces pushing this item away
    qreal xvel = 0;
    qreal yvel = 0;
//    foreach (QGraphicsItem *item, scene()->items()) {
//        NodeView *node = qgraphicsitem_cast<NodeView *>(item);
//        if (!node)
//            continue;

//        QPointF vec = mapToItem(node, 0, 0);
//        qreal dx = vec.x();
//        qreal dy = vec.y();
//        double l = 2.0 * (dx * dx + dy * dy);
//        if (l > 0) {
//            xvel += (dx * 150.0) / l;
//            yvel += (dy * 150.0) / l;
//        }
//    }



    // Now subtract all forces pulling items together
//    double weight = (edgeList.size() + 1) * 10;
//    foreach (EdgeView *edge, edgeList) {
//        QPointF vec;
//        if (edge->sourceNode() == this)
//            vec = mapToItem(edge->destNode(), 0, 0);
//        else
//            vec = mapToItem(edge->sourceNode(), 0, 0);
//        xvel -= vec.x() / weight;
//        yvel -= vec.y() / weight;
//    }



    //if (qAbs(xvel) < 1 && qAbs(yvel) < 1)
     //   xvel = yvel = 0;



    QRectF sceneRect = scene()->sceneRect();
    newPos = pos() + QPointF(xvel, yvel);
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + 10), sceneRect.right() - 10));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + 10), sceneRect.bottom() - 10));
}



bool NodeView::advance()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}



QRectF NodeView::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -20 - adjust, -30 - adjust, 33 + adjust, 43 + adjust);
}



QPainterPath NodeView::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}



void NodeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    //painter->setPen(Qt::NoPen);
    //painter->setBrush(Qt::darkGray);
    //painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::cyan).light(120));
        gradient.setColorAt(0, QColor(Qt::blue).light(120));
    } else {
        gradient.setColorAt(0, Qt::black);
        gradient.setColorAt(1, Qt::black);
    }
    painter->setBrush(gradient);

    //painter->setPen(QPen(Qt::black, 0));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-10, -10, 20, 20);

    QRectF textRect( -10, -10,
                        20, 20);
    QString message(QString::number(index));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(12);
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(textRect,Qt::AlignCenter, message);
    painter->setPen(Qt::black);
    //    painter->drawText(textRect, message);


}



QVariant NodeView::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (EdgeView *edge, edgeList)
            edge->adjust();
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}



void NodeView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void NodeView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

