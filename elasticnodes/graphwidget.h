
#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include "edge_view.h"
#include "graph.cpp"
#include "graphwidget.h"
#include <QGraphicsView>
#include <QVector>
#include <QDebug>
class NodeView;

typedef Graf<Vertex<int, QString>, Edge<Vertex<int, QString>, int, QString> > GrafType;
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    void itemMoved();
    void updateScene(GrafType *g);
public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();

protected:
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif
    void scaleView(qreal scaleFactor);

private:
    QVector<NodeView *> nodes;
    QVector<EdgeView*> edges;
    int timerId;
    NodeView* getNodeByIndex(int index);
};


#endif // GRAPHWIDGET_H
