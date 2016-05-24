
#include "graphwidget.h"
#include "edge_view.h"
#include "node_view.h"

#include <math.h>

#include <QKeyEvent>


GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
    //nodes = new QVector<NodeView*>;
    //nodes.clear();
    //nodes = QVector<NodeView*>();
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    scene->setSceneRect( - 500, -500, 500, 500);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(1), qreal(1));
    setMinimumSize(400, 400);
    setWindowTitle(tr("Elastic Nodes"));

}



void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}


void GraphWidget::updateScene(GrafType* g)
{
    foreach (NodeView* n, nodes) {
        delete n;
    }
    nodes.clear();

    foreach (EdgeView* e, edges) {
        delete e;
    }
    edges.clear();
    
    const float margin = 50;
    int count = g->V();
    GrafType::IteratorVertex it(g);
    int i;
    for (it.beg(), i = 0 ;it.end(); ++it, ++i)
    {
        NodeView* n = new NodeView(this);               
        scene()->addItem(n);
        
        float x = - scene()->width()/2 - (scene()->width()/2 - margin) * sin(2*i*M_PI/count);
        float y = - scene()->height()/2 - (scene()->height()/2 - margin) * cos(2*i*M_PI/count);
        n->setPos(x,y);
        auto v = *it;
        n->index = v->index; 
        nodes.append(n);                                
        
    }
    
//    for(it.beg(); it.end(); ++it)
//    {
//        GrafType::IteratorVertex it(g);
//        Vertex<int,char*>* v = *it;
//        GrafType::IteratorOutEdge itoe(g,v->index);
//        for (itoe.beg(); itoe.end(); ++itoe)
//        {
//            Edge<Vertex<int, char*>, int, char*>* edge = *itoe;
//            EdgeView* e = new EdgeView(getNodeByIndex(edge->v1->index),
//                                       getNodeByIndex(edge->v2->index));
//            scene()->addItem(e);
//            edges.append(e);
//        }
//    }
    
    /*GrafType::IteratorEdge ite(g);
    Edge<Vertex<int, char*>, int, char*>* edge = ite.beg();
    
    while (1)
    {
     
        if (!edge || !ite.end())
        {
        NodeView* n1 = getNodeByIndex(edge->v1->index);
        NodeView* n2 = getNodeByIndex(edge->v2->index);
        
        if (n1) qDebug() << QString::number(n1->index).prepend("n1 = "); else qDebug() << QString("n1 is null!");
        if (n2) qDebug() << QString::number(n2->index).prepend("n2 = "); else qDebug() << QString("n2 is null!");
        
        EdgeView* e = new EdgeView(n1,n2);
        scene()->addItem(e);
        edges.append(e);
        if (++ite) edge = *ite;
        
        } else break;
        
    }*/
    
    /*if (nodes.size() > 1) 
    {
        EdgeView* ev = new EdgeView(nodes[0], nodes[1]);
        scene()->addItem(ev);
        edges.append(ev);
    }*/
    
    for (it.beg() ;it.end(); ++it)
    {
 
        auto v1 = *it;
        GrafType::IteratorVertex it2(g);
        
        for (it2.beg() ;it2.end(); ++it2)
        {
            auto v2 = *it2;
            auto edge = g->GetEdge(v1,v2);
            if (edge)
            {
                EdgeView::EdgeType type;
                auto inversed = g->GetEdge(v2,v1);
                if (g->Directed())
                    if (inversed) type = EdgeView::both_directed;
                    else type = EdgeView::directed;
                else type = EdgeView::undirected;
                
                bool weight = g->w();
                int w1 = weight ? *edge->GetW() : 0;
                int w2 = inversed && weight ? *inversed->GetW() : 0;
                EdgeView* ev = new EdgeView(getNodeByIndex(edge->v1->index), 
                                            getNodeByIndex(edge->v2->index),
                                            type,
                                            weight, 
                                            w1, 
                                            w2);
                scene()->addItem(ev);
                edges.append(ev);
            }
        }
    }
}




void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<NodeView *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (NodeView *node = qgraphicsitem_cast<NodeView *>(item))
            nodes << node;
    }

    foreach (NodeView *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (NodeView *node, nodes) {
        if (node->advance())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}


#ifndef QT_NO_WHEELEVENT

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}

#endif



void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

NodeView *GraphWidget::getNodeByIndex(int index)
{
    foreach (NodeView* n, nodes)
    {
        //qDebug() << QString::number(index).prepend("Finding index ");
        if (n->index == index) return n;
    }
    return 0;
}


void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene()->items()) {
        if (qgraphicsitem_cast<NodeView *>(item))
            item->setPos(-150 + qrand() % 300, -150 + qrand() % 300);
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
