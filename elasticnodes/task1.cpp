#pragma once
#include "dialog.h"
#include <QString>

#define MAX 200
#define MAX_INT 2147483647


template< class Vertex, class Edge > class ShortestWay
{
    
    struct Vertex_Simply
    {
        int vertex;
        int parrent;
        int w;
        bool state;
        Vertex_Simply(int vertex, int parrent, int w)
        {
            this->vertex = vertex;
            this->parrent = parrent;
            this->state = true;
            this->w = w;
        }
        Vertex_Simply(int vertex)
        {
            this->vertex = vertex;
            this->w = MAX_INT;
            this->state = false;
        }
    };
    
    class stack
    {
        
        struct Node
        {
            Vertex_Simply *v;
            Node *next;
            Node()
            {
                v = NULL;
                next = NULL;
            }
            Node(Vertex_Simply *v, Node* next)
            {
                this->v = v;
                this->next = next;
            }
        };
        Node *top;
    public:
        stack()
        {
            top = NULL;
        }
        
        void push(Vertex_Simply *t)
        {
            Node *current = new Node(t, top);
            top = current;
        }
        
        Vertex_Simply* pop()
        {
            if (top != NULL)
            {
                Vertex_Simply* v = top->v;
                Node *current = top;
                top = top->next;
                delete current;
                return v;
            }
            else
            {
                return NULL;
            }
        }
        
        bool state()
        {
            if (top != NULL)
                return true;
            else
                return false;
        }
    };
    Graf<Vertex, Edge> *g;
    Dialog *_dialog;
    QString result;
    int way[MAX];
    
public:
    
    ShortestWay(Graf<Vertex, Edge> *g, Dialog* dialog): _dialog(dialog)
    {
        this->g = new Graf<Vertex, Edge>(true);
        
        for (int i = 0; i < g->V(); i++)
        {
            this->g->InsertV();
            way[i] = -1;
        }
        way[g->V()] = -1;
        
        for (int i = 0; i < g->V(); i++)
        {
            GrafType::IteratorOutEdge Iterator(g, i);
            Edge *Ed = Iterator.beg();
            bool it = true;
            while (it && Ed != NULL)
            {
                int v1;
                
                if (Ed->v1->index == i)
                    v1 = Ed->v2->index;
                else
                    v1 = Ed->v1->index;
                
                try { this->g->InsertE(v1, i, Ed->GetW()); }
                catch (QString e) { result = e; return; }
                it = ++Iterator;
                Ed = *Iterator;
            }
            
        }
    }
    
    void Restart(int v1)
    {
        Route(v1);
    }
    
    void Route(int v1)
    {
        Vertex_Simply *v[MAX];
        for (int i = 0; i < g->V(); i++)
            v[i] = new Vertex_Simply(i);
        
        int curr_v = v1;
        int son_v = 0;
        
        stack st;
        v[curr_v]->w = 0;
        v[curr_v]->parrent = -1;
        st.push(v[curr_v]);
        while (st.state())
        {
            v[g->V()] = st.pop();
            v[g->V()]->state = true;
            curr_v = v[g->V()]->vertex;
            GrafType::IteratorOutEdge Iterator(g, curr_v);
            Edge *Ed = Iterator.beg();
            
            while (Ed != NULL)
            {
                int w = *Ed->GetW();
                if (Ed->v1->index == curr_v)
                    son_v = Ed->v2->index;
                else
                    son_v = Ed->v1->index;
                
                if (v[son_v]->w > (v[curr_v]->w + w))
                {
                    v[son_v]->w = v[curr_v]->w + w;
                    v[son_v]->parrent = curr_v;
                }
                if (!v[son_v]->state)
                    st.push(v[son_v]);
                ++Iterator;
                Ed = *Iterator;
                
            }
        }
        int s = MAX;
        int v2;
        for (int i = 0, total = g->V(); i < total; ++i)
            if (v[i]->vertex != v1)
                if (v[i]->state)
                {
                    if (v[i]->w > s || s == MAX)
                    {
                        v2 = v[i]->vertex;
                        s = v[i]->w;
                    }
                }
                else
                    throw QString("Граф несвязный");
        
        
        for (int i = 0; i < g->V(); i++)
        {
            if (i != v1)
            {
                result += QString("Кратчайший путь из %1 в %2 ").arg(i).arg(v1);
                int j = 0;
                way[j] = i;
                int v2 = v[i]->vertex;
                while (v2 != v1)
                {
                    j++;
                    v2 = v[v2]->parrent;
                    way[j] = v2;
                }
                way[j + 1] = -1;
                j = 1;
                
                result.append(QString(" = %1").arg(way[0]));
                while (way[j] != -1)
                {
                    result.append(QString(" - %1").arg(way[j]));
                    j++;
                }
                result += '\n';
                
            }
        }
        
        for (int i = 0; i < g->V(); i++)
            delete v[i];
    }
    
    QString Result()
    {
        return result;
    }
    
};

