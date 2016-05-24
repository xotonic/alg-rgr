//#include <QSet>
//#include <QMap>
//#include <QStack>
//#include <QList>
//#include <QDebug>
//#include "graph.cpp"
//#include "dialog.h"
//using namespace std;


//template<class Vertex, class Edge> class TarjanSimpleCycles
//{
//public:
//    GrafType* graph;
    
//    QList<QList<Vertex *> > *cycles;
//    QSet<Vertex *> *marked;
//    QStack<Vertex *> *markedStack;
//    QStack<Vertex *> *pointStack;
//    QMap<Vertex *, int> *vToI;
//    QMap<Vertex *, QSet<Vertex *> > *removed;
       
//    /**
//     * Create a simple cycle finder for the specified graph->
//     * 
//     * @param graph - the DirectedGraph in which to find cycles->
//     * @throws IllegalArgumentException if the graph argument is
//     *         <code>NULL</code>->
//     */
//    TarjanSimpleCycles(GrafType* graph)
//    {
//        if (graph == NULL) {
//            throw QString("NULL graph argument");
//        }
//        this->graph = graph;
//    }
    
//    void clearState()
//    {
//        //delete cycles;
//        delete marked;
//        delete markedStack;
//        delete pointStack;
//        delete vToI;
//    }
    
//    QList<QList<Vertex*>>* findSimpleCycles()
//    {
//        if (graph == NULL) {
//            throw QString("NULL graph");
//        }
//        initState();
        
//        GrafType::IteratorVertex start(graph);
//        for (start.beg(); start.end(); ++start)//V start : graph->vertexSet()) {
//        {    backtrack(*start, *start);
//            while (!markedStack->empty()) {
//                marked->remove(markedStack->pop());
//            }
//        }
        
//        //QList<QList<Vertex*>>* result = cycles;
//        clearState();
//        return cycles;
//    }
    
//    bool backtrack(Vertex* start, Vertex* vertex)
//    {
//        bool foundCycle = false;
//        pointStack->push(vertex);
//        marked->insert(vertex);
//        markedStack->push(vertex);
        
        
//        GrafType::IteratorOutEdge currentEdge(graph, vertex->index);
        
//        for ( currentEdge.beg(); currentEdge.end(); ++currentEdge) 
//        {
//            Vertex* currentVertex = (*currentEdge)->v2;
//            if (getRemoved(vertex)->contains(currentVertex)) 
//            {
//                continue;
//            }
//            int comparison = toI(currentVertex) - toI(start);
//            if (comparison < 0) {
//                getRemoved(vertex)->push_back(currentVertex);
//            }
//            else if (comparison == 0) {
//                foundCycle = true;
//                QList<Vertex*> cycle;// = new QList<Vertex*>();
//                int cycleStart = pointStack->indexOf(start);
//                int cycleEnd = pointStack->size() - 1;
//                for (int i = cycleStart; i <= cycleEnd; i++) {
//                    cycle.push_back(pointStack->at(i));
//                }
//                cycles->push_back(cycle);
//            }
//            else if (!marked->contains(currentVertex)) {
//                bool gotCycle =
//                        backtrack(start, currentVertex);
//                foundCycle = foundCycle || gotCycle;
//            }
//        }
        
//        if (foundCycle) {
//            while (markedStack->top() != vertex) {
//                marked->remove(markedStack->pop());
//            }
//            marked->remove(markedStack->pop());
//        }
        
//        pointStack->pop();
//        return foundCycle;
//    }
    
//    void initState()
//    {
//        cycles = new QList<QList<Vertex*>>();
//        marked = new QSet<Vertex*>();
//        markedStack = new QStack<Vertex*>();
//        pointStack = new QStack<Vertex*>();
//        vToI = new QMap<Vertex*, int>();
//        removed = new QMap<Vertex*, QSet<Vertex*>>();
        
//        int index = 0;
        
//        GrafType::IteratorVertex v(graph);
//        for (v.beg() ; v.end(); ++v) {
//            vToI->insert(*v, index++);
//        }
//    }
    
    
    
//    int toI(Vertex* v)
//    {
//        return vToI->get(v);
//    }
    
//    QList<Vertex*>* getRemoved(Vertex* v)
//    {
//        // Removed sets typically not all
//        // needed, so instantiate lazily->
//        QList<Vertex*> result = removed->take(v).toList();
//        if (result == QList<Vertex*>()) {
//            result = (new QSet<Vertex*>())->toList();
//            removed->insert(v, result);
//        }
//        return result;
//    }
    
//    void Restart(int i)
//    {
//        auto res  = findSimpleCycles();
//    }
    
//    QString Result()
//    {
        
//    }
//};
