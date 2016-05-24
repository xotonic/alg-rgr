#pragma once
#include <QDebug>
#include <qmath.h>
#include "vertex_and_edge.cpp"
#include <vector>

using namespace std;

template<class Vertex, class Edge> class List
{
    struct Node
    {
    public:
        Node *next;
        Edge *Ed;
        int index;
        Node(Edge *Ed, int index)
        {
            this->index = index;
            this->Ed = Ed;
            this->next = NULL;
        }
    };
    vector<Node*> ListVertex;
    int number_v;
    int number_e;
    bool F;
public:
    int E()
    {
        return number_e;
    }
    List(bool F)
    {
        number_v = 0;
        number_e = 0;
        this->F = F;
    }
    void InsertV()
    {
        Node* head = NULL;
        ListVertex.push_back(head);
        number_v++;
    }
    void DeleteV(int v)
    {
        bool del = false;
        for(int i = 0; i < number_v; i++)
        {
            Node* t = ListVertex[i];
            if(ListVertex[i] != NULL) {
                if(i != v || del == true)
                {
                    if(ListVertex[i]->index == v)
                    {
                        Node* s = t->next;
                        number_e--;
                        delete t;
                        ListVertex[i] = s;
                        t = s;
                    }
                    Node* p = t;
                    Node* s = NULL;
                    while(t != NULL)
                    {
                        s = t->next;
                        if(t->index == v)
                        {
                            p->next = s;
                            number_e--;
                            delete t;
                            t = s;
                        }
                        else
                        {
                            p = t;
                            t = s;
                        }
                        if(p->index > v)
                            p->index--;
                    }
                }
                else
                {
                    Node* s = ListVertex[i];
                    while(t != NULL)
                    {
                        s = t->next;
                        if (F) number_e--;
                        delete t;
                        t = s;
                    }
                    ListVertex.erase(ListVertex.begin() + i);
                    number_v--;
                    i--;
                    del = true;
                }
            }
        }
    }
    Edge* InsertE(Vertex *Ver1, Vertex *Ver2, int *w)
    {
        int v1 = Ver1->index;
        int v2 = Ver2->index;
        Edge *Ed = new Edge(Ver1, Ver2, w);
        if(!F) InsertOneE(Ed, v2, v1);
        if(InsertOneE(Ed, v1, v2))
        {
            number_e++;
            return Ed;
        }
        else
            throw QString("Между этими вершинами есть ребро");
    }
    Edge* InsertE(Vertex *Ver1, Vertex *Ver2)
    {
        int v1 = Ver1->index;
        int v2 = Ver2->index;
        Edge *Ed = new Edge(Ver1, Ver2);
        if(!F) InsertOneE(Ed, v2, v1);
        if(InsertOneE(Ed, v1, v2))
        {
            number_e++;
            return Ed;
        }
        else
            throw QString("Между этими вершинами есть ребро");
    }
    void InsertE(Edge *Ed, int v1, int v2)
    {
        if(InsertOneE(Ed, v1, v2))
            number_e++;
    }
    bool DeleteE(Vertex *Ver1, Vertex *Ver2)
    {
        int v1 = Ver1->index;
        int v2 = Ver2->index;
        if(!F) DeleteOneE(v2, v1);
        if(DeleteOneE(v1, v2))
        {
            number_e--;
            return true;
        }
        else
            return false;
    }
    Edge* GetEdge(Vertex *Ver1, Vertex *Ver2)
    {
        int v1 = Ver1->index;
        int v2 = Ver2->index;
        
        Node *t = ListVertex[v1];
        while(t != NULL)
        {
            if(t->index == v2)
            {
                return t->Ed;
            }
            
            t = t->next;
        }
        return NULL;
    }
    
    
    
    QString print(int v)
    {
        QString s;
        if(v >= 0 && v < number_v)
        {
            Node* t = ListVertex[v];
            while(t != NULL)
            {
                //cout<<t->index<<" ";
                s.append(QString::number(t->index).append(" "));
                t = t->next;
            }
        }
        return s;
    }
    class IteratorEdgeL
    {
        List *l;
        Node *current;
        int v1;
        bool status;
    public:
        IteratorEdgeL(List<Vertex,Edge> *l)
        {
            this->l = l;
            status = false;
            v1 = 0;
        }
        Edge* beg()
        {
            int E = l->number_e;
            int V = l->number_v;
            if(E > 0)
            {
                v1 = -1;
                current = NULL;
                while(current == NULL && v1 < (V - 1))
                {
                    v1++;
                    current = l->ListVertex[v1];
                }
            }
            if(current == NULL)
            {
                status = false;
                return NULL;
            }
            else
            {
                status = true;
                return current->Ed;
            }
        }
        bool end()
        {
            return status;
        }
        bool next()
        {
            int V = l->number_v;
            if(status)
            {
                current = current->next;
                while(current == NULL && v1 < (V-1))
                {
                    v1++;
                    current = l->ListVertex[v1];
                }
                if(current == NULL)
                {
                    status = false;
                }
                else
                {
                    status = true;
                }
                return status;
            }
            else
                return false;
        }
        Edge* read()
        {
            if(status)
            {
                return current->Ed;
            }
            else
                return NULL;
        }
    };
    class IteratorOutEdgeL
    {
        List *l;
        Node *current;
        int v1;
        bool status;
    public:
        IteratorOutEdgeL(List<Vertex,Edge> *l, int v1)
        {
            this->l = l;
            status = false;
            this->v1 = v1;
        }
        Edge* beg()
        {
            int E = l->number_e;
            if(E > 0)
            {
                current = l->ListVertex[v1];
            }
            if(current == NULL)
            {
                status = false;
                return NULL;
            }
            else
            {
                status = true;
                return current->Ed;
            }
        }
        bool end()
        {
            return status;
        }
        bool next()
        {
            if(status)
            {
                current = current->next;
                if(current == NULL)
                {
                    status = false;
                }
                else
                {
                    status = true;
                }
                return status;
            }
            else
                return false;
        }
        Edge* read()
        {
            if(status)
            {
                return current->Ed;
            }
            else
                return NULL;
        }
    };
private:
    bool InsertOneE(Edge* Ed, int v1, int v2)
    {
        Node *t = ListVertex[v1];			//вставляем ребро v1-v2 в структуру
        Node *p = ListVertex[v1];
        while(t != NULL)
        {
            if(t->index == v2)
                return false;
            p  = t;
            t = t->next;
        }
        t = new Node(Ed, v2);
        //Node *s = t;
        if(p == NULL) ListVertex[v1] = t;
        else p->next = t;
        return true;
    }
    bool DeleteOneE(int v1, int v2)
    {
        Node *t = ListVertex[v1];
        Node *p = NULL;
        while(t != NULL)
        {
            if(t->index == v2)
            {
                if(p == NULL)
                {
                    ListVertex[v1] = t->next;
                    delete t;
                    return true;
                }
                p->next = t->next;
                delete t;
                return true;
            }
            p = t;
            t = t->next;
        }
        return false;
    }
};
template<class Vertex, class Edge> class Matrix//: public Parent_graf <Vertex,Edge>
{
    vector <vector <Edge*> > MatrixE;
    Vertex **ListV;
    int number_e;
    bool D;
public:
    int number_v;
    int E()
    {
        return number_e;
    }
    Matrix(bool _D)
    {
        number_e = 0;
        number_v = 0;
        D = _D;
    }
    void InsertV()
    {
        //Создаём новую пустую строку
        vector<Edge*> newLine;
        newLine.assign(number_v, NULL);
        //Вставляем новую строку:
        MatrixE.insert(MatrixE.begin() + number_v, newLine);
        number_v++;
        //Вставляем новый столбец:
        for(int i = 0; i < number_v; ++i)
            MatrixE[i].insert(MatrixE[i].begin() + (number_v-1), (Edge*)NULL);
    }
    void DeleteV(int v)
    {
        number_e -= deleteEdgesFromVertex(v,D);
        //Удаляем строку:
        MatrixE.erase(MatrixE.begin() + v);
        number_v--;
        for(int j = 0; j < number_v; j++)
        {    
            ///if(MatrixE[j][v] != NULL)
            ///    number_e--;
            ///if (D) if(MatrixE[v][j]!= NULL) number_e--;
        }
        //else if (D && MatrixE[v][j] != NULL) number_e--;
        //Удаляем столбец:
        for(int j = 0; j < number_v; j++)
        {
            //if (D && MatrixE[v][j]!= NULL) number_e--;
            MatrixE[j].erase(MatrixE[j].begin() + v);
        }
    }
    
    
    int deleteEdgesFromVertex(int index, bool directed)
    {
        int size = MatrixE.size();
        int deleted = 0;
        
        if (index < 0 || index >= size) return 0;
        
        for (int i = 0; i < size; i++)
        {
            if (MatrixE[i][index] != NULL)
            {
                delete MatrixE[i][index];
                MatrixE[i][index] = NULL;
                deleted++;
                if (!directed)
                    MatrixE[index][i] = NULL;
            }
            if(MatrixE[index][i] != NULL) 
            {
                delete MatrixE[index][i];
                MatrixE[index][i] = NULL;
                ++deleted;
            }
        }
        return deleted;
        
    }
    
    Edge* InsertE(Vertex *Ver1, Vertex *Ver2)
    {
        int v1 = Ver1->index;
        int v2 = Ver2->index;
        Edge *Ed = new Edge(Ver1, Ver2);
        if(MatrixE[v1][v2] == NULL)
        {
            MatrixE[v1][v2] = Ed;
            if(!D) MatrixE[v2][v1] = Ed;
            number_e++;
            return Ed;
        }
        else
            throw QString("Между этими вершинами уже есть ребро");
    }
    Edge* InsertE(Vertex *Ver1, Vertex *Ver2, int *w)
    {
        int v1 = Ver1->index;
        int v2 = Ver2->index;
        Edge *Ed = new Edge(Ver1, Ver2, w);
        if(MatrixE[v1][v2] == NULL)
        {
            MatrixE[v1][v2] = Ed;
            if(!D) MatrixE[v2][v1] = Ed;
            number_e++;
            return Ed;
        }
        else
            throw QString("Между этими вершинами уже есть ребро");
    }
    void InsertE(Edge *Ed, int v1, int v2)
    {
        if(MatrixE[v1][v2] == NULL)
        {
            MatrixE[v1][v2] = Ed;
            number_e++;
        }
    }
    bool DeleteE(Vertex *Ver1, Vertex *Ver2)
    {
        int v1 = Ver1->index;
        int v2 = Ver2->index;
        if(MatrixE[v1][v2] != NULL)
        {
            number_e--;
            MatrixE[v1][v2] = NULL;
            if(!D) MatrixE[v2][v1] = NULL;
            return true;
        }
        else
            return false;
    }
    Edge* GetEdge(Vertex *Ver1, Vertex *Ver2)
    {
        int v1 = Ver1->index;
        int v2 = Ver2->index;
        if(MatrixE[v1][v2] != NULL)
            return MatrixE[v1][v2];
        else
            return NULL;
    }
    QString print(int v)
    {
        //int w;
        //printf("  ");
        QString s =  "  ";
        //cout << "  ";
        for(int i = 0; i< number_v; i++)
        {
            if(MatrixE[v][i] != NULL)
                //cout<<" + ";
                s.append(" + ");
            else s.append(" - ");
            //cout<<" - ";
        }
        return s;
    }
    class IteratorEdgeM
    {
        Matrix *m;
        int v1;
        int v2;
        bool status;
    public:
        IteratorEdgeM(Matrix<Vertex,Edge> *m)
        {
            this->m = m;
            status = false;
            v1 = 0;
            v2 = 0;
        }
        Edge* beg()
        {
            int V = m->number_v;
            int E = m->number_e;
            Edge* Ed = NULL;
            if(E > 0)
            {
                v1 = -1;
                v2 = -1;
                while(Ed == NULL && v1 < (V - 1))
                {
                    v1++;
                    v2 = -1;
                    while(Ed == NULL && v2 < (V - 1))
                    {
                        v2++;
                        Ed = m->MatrixE[v1][v2];
                    }
                }
            }
            if(Ed == NULL)
            {
                status = false;
            }
            else
            {
                status = true;
            }
            return Ed;
        }
        bool end()
        {
            return status;
        }
        bool next()
        {
            Edge* Ed = NULL;
            int V = m->number_v;
            int E = m->number_e;
            if(status)
            {
                v1--;
                if(E > 0)
                {
                    while(Ed == NULL && v1 < (V - 1) )
                    {
                        v1++;
                        while(Ed == NULL && v2 < (V - 1))
                        {
                            v2++;
                            Ed = m->MatrixE[v1][v2];
                        }
                        if(Ed == NULL) v2 = -1;
                    }
                }
            }
            if(Ed != NULL)
            {
                status = true;
                return true;
            }
            else
            {
                status = false;
                return false;
            }
        }
        Edge* read()
        {
            if(status)
            {
                int V = m->number_v;
                int E = m->number_e;
                if(E == 0)
                    return NULL;
                if(v1 == V && v2 == V)
                    return NULL;
                else
                {
                    Edge* Ed = m->MatrixE[v1][v2];
                    return Ed;
                }
            }
            else
            {
                return NULL;
            }
        }
    };
    class IteratorEdgeOutM
    {
        Matrix *m;
        int v1;
        int v2;
        bool status;
    public:
        IteratorEdgeOutM(Matrix<Vertex,Edge> *m, int v1)
        {
            this->m = m;
            status = false;
            this->v1 = v1;
            v2 = 0;
        }
        Edge* beg()
        {
            int V = m->number_v;
            int E = m->number_e;
            Edge* Ed = NULL;
            if(E > 0)
            {
                v2 = -1;
                while(Ed == NULL && v2 < (V - 1))
                {
                    v2++;
                    Ed = m->MatrixE[v1][v2];
                }
            }
            if(Ed == NULL)
            {
                status = false;
            }
            else
            {
                status = true;
            }
            return Ed;
        }
        bool end()
        {
            return status;
        }
        bool next()
        {
            Edge* Ed = NULL;
            int V = m->number_v;
            int E = m->number_e;
            if(status)
            {
                if(E > 0)
                {
                    while(Ed == NULL && v2 < (V - 1))
                    {
                        v2++;
                        Ed = m->MatrixE[v1][v2];
                    }
                    if(Ed == NULL) v2 = -1;
                }
            }
            if(Ed != NULL)
            {
                status = true;
                return true;
            }
            else
            {
                status = false;
                return false;
            }
        }
        Edge* read()
        {
            if(status)
            {
                int V = m->number_v;
                int E = m->number_e;
                if(E == 0)
                    return NULL;
                if(v1 == V && v2 == V)
                    return NULL;
                else
                {
                    Edge* Ed = m->MatrixE[v1][v2];
                    return Ed;
                }
            }
            else
            {
                return NULL;
            }
        }
    };
};
template<class Vertex, class Edge> class Graf
{
    List<Vertex, Edge> *l;
    Matrix<Vertex, Edge> *m;
    vector<Vertex*> VertVector;
    int number_v;
    int number_e;
    bool W;
    bool D;	// D - форма представления, true - L-граф, false - M-граф
    bool F;	// F - тип графа, true - true - ориентированный, false - неориентированный
public:
    Graf(bool W)
    {
        this->D = true;
        this->F = true;
        this->W = W;
        number_v = 0;
        number_e = 0;
        l = new List<Vertex, Edge>(D);
    }
    Graf(int V, bool D, bool F, bool W)
    {
        this->D = D;
        this->F = F;
        this->W = W;
        number_v = 0;
        number_e = 0;
        if(D)
        {
            l = new List<Vertex, Edge>(F);
        }
        else
        {
            m = new Matrix<Vertex, Edge>(F);
        }
        for(int i = 0; i < V; i++)
        {
            InsertV();
        }
    }
    Graf(int V, int E, bool D, bool F, bool W)
    {
        this->D = D;
        this->F = F;
        this->W = W;
        number_v = 0;
        number_e = 0;
        if(D)
        {
            l = new List<Vertex, Edge>(F);
        }
        else
        {
            m = new Matrix<Vertex, Edge>(F);
        }
        for(int i = 0; i < V; i++)
        {
            InsertV();
        }
        if(F)
        {
            if(E > number_v * (number_v - 1))
                E = number_v * (number_v - 1);
        }
        else
        {
            if(E > (number_v * (number_v - 1) / 2))
                E = number_v * (number_v - 1) / 2;
        }
        
        int v1, v2;
        while(number_e < E)
        {
            v1 = rand() % number_v;
            v2 = rand() % number_v;
            if(v1 == v2)
                continue;
            if(GetEdge(VertVector[v1], VertVector[v2]) != NULL)
                continue;
            InsertE(VertVector[v1], VertVector[v2]);
        }
    }
    Graf(Graf<Vertex, Edge> *g)
    {
        number_e = g->E();
        number_v = g->V();
        D = g->D;
        F = g->F;
        VertVector = g->VertVector;
        if(D)
            l = g->l;
        else
            l = g->m;
    }
    bool w()
    {
        return W;
    }
    double K()
    {
        if(number_v == 0 || number_v == 1)
            return 0;
        if(F)
        {
            qDebug() << number_e;
            qDebug() << number_v;
            return (double)((double)number_e /(number_v * (number_v-1)));
        }
        else
        {
            qDebug() << number_e;
            qDebug() << number_v;
            return (double)(2*(double)number_e / (number_v * (number_v-1)));
        }
    }
    int V()
    {
        return number_v;
    }
    int E()
    {
        return number_e;
    }
    bool Directed()
    {
        return F;
    }
    bool Dense()
    {
        return D;
    }
    Vertex* InsertV()
    {
        Vertex *v = new Vertex();
        v->index = VertVector.size();
        VertVector.push_back(v);
        number_v++;
        if(D)
            l->InsertV();
        else
            m->InsertV();
        return v;
    }
    Vertex* InsertV(Vertex *v)
    {
        v->index = VertVector.size();
        VertVector.push_back(v);
        number_v++;
        
        if(D)
            l->InsertV();
        else
            m->InsertV();
        return v;
    }
    bool DeleteV(Vertex *Ver)
    {
        int index = Ver->index;
        if((index >= 0) && (index < number_v) && (VertVector[index] == Ver))
        {
            VertVector.erase( VertVector.begin() + Ver->index);
            if(D)
            {
                l->DeleteV(index);
                number_e = l->E();
            }
            else
            {
                m->DeleteV(index);
                number_e = m->E();
            }
            for(int i = Ver->index; i < VertVector.size(); i++)
                VertVector[i]->index = i;
            number_v--;
            return true;
        }
        else
            return false;
    }
    Edge* InsertE(Vertex *Ver1, Vertex *Ver2)
    {
        int v1 = Ver1->index;
        int v2 = Ver2->index;
        if((v1 >= 0) && (v1 < number_v) &&
                (v2 >= 0) && (v2 < number_v) && (v1 != v2) &&
                (Ver1 == VertVector[v1]) && (Ver2 == VertVector[v2]))
        {
            number_e++;
            if(D)
                return l->InsertE(Ver1, Ver2);
            else
                return m->InsertE(Ver1, Ver2);
        }
        else
            throw QString("В графе нет таких вершин");
    }
    bool DeleteE(Vertex *Ver1, Vertex *Ver2)
    {
        int v1 = Ver1->index;
        int v2 = Ver2->index;
        if((v1 >= 0) && (v1 < number_v) &&
                (v2 >= 0) && (v2 < number_v) &&
                (Ver1 == VertVector[v1]) && (Ver2 == VertVector[v2]))
        {
            number_e--;
            if(D)
                return l->DeleteE(Ver1, Ver2);
            else
                return m->DeleteE(Ver1, Ver2);
        }
        else
            throw false;
    }
    Edge* GetEdge(Vertex *Ver1, Vertex *Ver2)
    {
        int v1 = Ver1->index;
        int v2 = Ver2->index;
        // qDebug() << "v1 = " << v1 << "v2 = " << v2;
        if((v1 >= 0) && (v1 < number_v) &&
                (v2 >= 0) && (v2 < number_v) &&
                (Ver1 == VertVector[v1]) && (Ver2 == VertVector[v2]))
        {
            if(D)
                return l->GetEdge(Ver1, Ver2);
            else
                return m->GetEdge(Ver1, Ver2);
        }
        else
            return NULL;
    }
    
    
    bool IsEdge(Vertex *Ver1, Vertex *Ver2)
    {
        Edge* e = GetEdge(Ver1, Ver2);
        return e == NULL ? false : true;
    }
    
    bool IsEdge(int v1, int v2)
    {
        if((v1 >= 0) && (v1 < number_v) &&
                (v2 >= 0) && (v2 < number_v))
        {
            return IsEdge(VertVector[v1], VertVector[v2]);
        }
        else return false;
    }
    
    bool DeleteV(int index)
    {
        if((index >= 0) && (index < number_v))
        {
            VertVector.erase( VertVector.begin() + index);
            if(D)
            {
                l->DeleteV(index);
                number_e = l->E();
            }
            else
            {
                m->DeleteV(index);
                number_e = m->E();
            }
            for(int i = index, total = VertVector.size(); i < total; ++i)
                VertVector[i]->index = i;
            number_v--;
            return true;
        }
        else
            return false;
    }
    Edge* InsertE(int v1, int v2)
    {
        if((v1 >= 0) && (v1 < number_v) &&
                (v2 >= 0) && (v2 < number_v) && (v1 != v2))
        {
            Edge* e = NULL;
            if(D)
                e = l->InsertE(VertVector[v1], VertVector[v2]);
            else
                e = m->InsertE(VertVector[v1], VertVector[v2]);
            number_e++;
            return e;
            
        }
        else
            throw QString("В графе нет таких вершин");
    }
    Edge* InsertE(int v1, int v2, int *w)
    {
        
        if((v1 >= 0) && (v1 < number_v) &&
                (v2 >= 0) && (v2 < number_v) && (v1 != v2))
        {
            Edge* e = NULL;
            if(D)
                e = l->InsertE(VertVector[v1], VertVector[v2], w);
            else
                e = m->InsertE(VertVector[v1], VertVector[v2], w);
            number_e++;
            return e;
        }
        else
            throw QString("В графе нет таких вершин");
    }
    bool DeleteE(int v1, int v2)
    {
        if((v1 >= 0) && (v1 < number_v) &&
                (v2 >= 0) && (v2 < number_v))
        {
            number_e--;
            if(D)
                return l->DeleteE(VertVector[v1], VertVector[v2]);
            else
                return m->DeleteE(VertVector[v1], VertVector[v2]);
        }
        else
            return false;
    }
    Edge* GetEdge(int v1, int v2)
    {
        //int v1 = Ver1->index;
        //int v2 = Ver2->index;
        if((v1 >= 0) && (v1 < number_v) &&
                (v2 >= 0) && (v2 < number_v))
        {
            if(D)
                return l->GetEdge(VertVector[v1], VertVector[v2]);
            else
                return m->GetEdge(VertVector[v1], VertVector[v2]);
        }
        else
            return NULL;
    }
    bool ToListGraf()
    {
        if(D)
        {
            return false;
        }
        else
        {
            l = new List<Vertex, Edge>(F);
            for(int i = 0; i < number_v; i++)
            {
                l->InsertV();
            }
            for(int i = 0; i < number_v; i++)
                for(int j = 0; j < number_v; j++)
                {
                    Edge *Ed = m->GetEdge(VertVector[i],VertVector[j]);
                    if(Ed != NULL)
                        l->InsertE(Ed, i, j);
                }
            D = !D;
            delete m;
        }
        return true;
    }
    bool ToMatrixGraf()
    {
        if(!D)
        {
            return false;
        }
        else
        {
            m = new Matrix<Vertex, Edge>(F);
            for(int i = 0; i < number_v; i++)
            {
                m->InsertV();
            }
            for(int i = 0; i < number_v; i++)
                for(int j = 0; j < number_v; j++)
                {
                    Edge *Ed = l->GetEdge(VertVector[i],VertVector[j]);
                    if(Ed != NULL)
                        m->InsertE(Ed, i, j);
                }
            D = !D;
            delete l;
        }
        return true;
    }
    QString print()
    {
        QString s;
        QTextStream ts(&s);
        if(D)
        {
            for(int i = 0, total = VertVector.size(); i < total; ++i)
            {
                //cout<<VertVector[i]->index<<" ->";
                //l->print(i);
                //cout<<endl;
                ts << VertVector[i]->index << " ->" << l->print(i) << endl;
            }
        }
        else
        {
            //cout<<"     ";
            ts << "     ";
            for(int i = 0, total = VertVector.size(); i < total; ++i)
            {
                ts << VertVector[i]->index << "  ";
            }
            ts << endl;
            for(int i = 0, total = VertVector.size(); i < total; ++i)
            {
                ts << VertVector[i]->index << "|"
                   << m->print(i) << endl;
            }
        }
        return s;
    }
    class IteratorVertex
    {
        Graf *g;
        int current;
    public:
        IteratorVertex(Graf<Vertex,Edge> *g)
        {
            this->g = g;
            current = 0;
        }
        Vertex* beg()
        {
            current = 0;
            if(g->V() != 0)
                return g->VertVector[current];
            else
                return NULL;
        }
        bool end()
        {
            if(current < g->V())
                return true;
            else
                return false;
        }
        bool operator ++()
        {
            if(current < g->V())
            {
                current++;
                return true;
            }
            else
            {
                current++;
                return false;
            }
        }
        Vertex* operator *()
        {
            if(current < g->V())
                return g->VertVector[current];
            else
                return NULL;
        }
    };
    class IteratorEdge
    {
        typename Matrix<Vertex, Edge>::IteratorEdgeM *IteratorM;
        typename List<Vertex, Edge>::IteratorEdgeL *IteratorL;
        bool D;
    public:
        IteratorEdge(Graf<Vertex,Edge> *g)
        {
            this->D = g->D;
            if(D)
            {
                IteratorL = new typename List<Vertex, Edge>::IteratorEdgeL(g->l);
            }
            else
            {
                IteratorM = new typename Matrix<Vertex, Edge>::IteratorEdgeM(g->m);
            }
        }
        Edge* beg()
        {
            if(D)
            {
                return IteratorL->beg();
            }
            else
            {
                return IteratorM->beg();
            }
        }
        bool end()
        {
            if(D)
            {
                return IteratorL->end();
            }
            else
            {
                return IteratorM->end();
            }
        }
        bool operator ++()
        {
            if(D)
            {
                return IteratorL->next();
            }
            else
            {
                return IteratorM->next();
            }
        }
        Edge* operator *()
        {
            if(D)
            {
                return IteratorL->read();
            }
            else
            {
                return IteratorM->read();
            }
        }
    };
    class IteratorOutEdge
    {
        typename Matrix<Vertex, Edge>::IteratorEdgeOutM *IteratorM;
        typename List<Vertex, Edge>::IteratorOutEdgeL *IteratorL;
        bool D;
    public:
        IteratorOutEdge(Graf<Vertex,Edge> *g, int v1)
        {
            this->D = g->D;
            if(D)
            {
                IteratorL = new typename List<Vertex, Edge>::IteratorOutEdgeL(g->l, v1);
            }
            else
            {
                IteratorM = new typename Matrix<Vertex, Edge>::IteratorEdgeOutM(g->m, v1);
            }
        }
        Edge* beg()
        {
            if(D)
            {
                return IteratorL->beg();
            }
            else
            {
                return IteratorM->beg();
            }
        }
        bool end()
        {
            if(D)
            {
                return IteratorL->end();
            }
            else
            {
                return IteratorM->end();
            }
        }
        bool operator ++()
        {
            if(D)
            {
                return IteratorL->next();
            }
            else
            {
                return IteratorM->next();
            }
        }
        Edge* operator *()
        {
            if(D)
            {
                return IteratorL->read();
            }
            else
            {
                return IteratorM->read();
            }
        }
    };
};
