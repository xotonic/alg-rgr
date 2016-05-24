
#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include <QDebug>
class NodeView;


class EdgeView : public QGraphicsItem
{
public:
    enum EdgeType { directed, undirected, both_directed };
    EdgeView(NodeView *sourceNode, NodeView *destNode, 
             EdgeType type = directed, bool drawWeights = false, int w1 = 0 , int w2 = 0);

    NodeView *sourceNode() const;
    NodeView *destNode() const;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const Q_DECL_OVERRIDE { return Type; }
protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    NodeView *source, *dest;
    EdgeType _type;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
    
    bool _draw_weights;
    int _w1, _w2;
};


#endif // EDGE_H
