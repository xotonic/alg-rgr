
#include "graph.cpp"
#include "dialog.h"
#include <QQueue>
#include <QVector>

template< class Vertex, class Edge > class SimpleCycles2
{
    enum Color { white, gray, black };
    
    struct HelpData
    {
        Color color = white;
        int predecessor  = -1;
    };
    
    
    QVector<HelpData> data;
    int time;
    int target;
    GrafType *g;
    QTextStream out;
    QString result;
    QQueue<int> stack;
    
    //Graf<Vertex<int, int>, Edge<Vertex<int, int>, int, int> > dfs_tree;
    //int dfs_count;
public:
    SimpleCycles2(GrafType* _g) : 
        g(_g),// dfs_tree(false),
        out(&result) {}
    
    QString Result() { return result; }
    
    void Set(GrafType *_g)
    {
        g = _g;
    }
    void Restart(int index)
    {
        Set(g);
        DFS(index);
    }
    void DFS(int u)
    {
        target = u;
        data.clear();
        data.resize(g->V());
        
        for (int i = 0; i < g->V(); i++)
        {
            if (data[i].color == white) 
            visit(i);
        }
    }
    
    void visit(int u, int treeIndex = 0)
    {
        stack.push_back(u);
        data[u].color = gray;
        QVector<int> adjacent = get_adjacent(u);
        
        foreach (auto v, adjacent)
        {
            if (data[v].color == white )
            {
                data[v].predecessor = u;
                visit(v);
            }
            if (data[v].color == gray && v !=data[u].predecessor)
            {
                //if (stack.size() > 2) {
                foreach (int s , stack)
                {
                    out << " " << s;
                    //data[s].color = white;
                }
                out << " " << stack.first() << endl;
                
                //}
            }
        }
        data[u].color = black;
        stack.pop_back();
    }
    
    QVector<int> get_adjacent(int u)
    {
        QVector<int> adj;
        GrafType::IteratorOutEdge it(g,u);
        for (it.beg(); it.end(); ++it)
        {
            auto e = *it;
            adj.push_back(e->v2->index);
        }
        return adj;
    }
    
};
