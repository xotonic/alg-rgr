#pragma once
#include <QString>
#include <QTextStream>
template <class DataV, class NameV> class Vertex
{
    NameV* name;
    DataV* data;
public:
    int index;
    Vertex()
    {
        data = NULL;
        name = NULL;
    }
    Vertex(NameV *name, DataV *data)
    {
        this->data = data;
        this->name = name;
    }
    NameV* GetName()
    {
        return name;
    }
    DataV* GetData()
    {
        return data;
    }
    void SetName(NameV* name)
    {
        if (this->name) delete this->name;
        this->name = name;
    }
    void SetData(DataV* data)
    {
        if (this->data) delete this->data;
        this->data = data;
    }
    
    bool IsName() { return name ? true : false; }
    bool IsData() { return data ? true : false; }
    
    QString print()
    {
        QString s;
        QTextStream ts(&s);
        ts << "index = " << index << endl;
        
        ts << "name  = "; 
        if (name) ts << *name; 
        else ts << "NULL"; ts << endl;
        
        ts << "data  = "; 
        if(data) ts << *data; 
        else ts << "NULL"; 
        ts << endl;
        
        return s;
    }
};
template <class Vertex, class TypeW, class DataE> class Edge
{
    DataE *data;
    TypeW *w;
public:
    Vertex *v1;
    Vertex *v2;
    Edge(Vertex *v1, Vertex *v2)
    {
        this->v1 = v1;
        this->v2 = v2;
        data = NULL;
        w = NULL;
    }
    Edge(Vertex *v1, Vertex *v2, TypeW *w)
    {
        this->v1 = v1;
        this->v2 = v2;
        this->w = w;
        data = NULL;
    }
    Edge(Vertex *v1, Vertex *v2, TypeW *w, DataE *data)
    {
        this->v1 = v1;
        this->v2 = v2;
        this->w = w;
        this->data = data;
    }
    TypeW* GetW()
    {
        return w;
    }
    void SetW(TypeW *w)
    {
        if (this->w) delete this->w;
        this->w = w;
    }
    DataE* GetData()
    {
        return data;
    }
    void SetData(DataE *data)
    {
        if (this->data) delete this->data;
        this->data = data;
    }
    bool IsData() { return data ? true : false; }
    bool IsW() { return w ? true : false; }
    QString print()
    {
        QString s;
        QTextStream ts(&s);
        ts << "v1 = " << v1->index << ", v2 = " << v2->index << endl;
        ts   << "data  = ";
        if (data) ts << *data;
        else ts << "NULL";
        ts << endl;
              
        ts << "w     = ";
        if (w) ts << *w; else ts << "NULL";
        ts  << endl;
        return s;
    }
};
