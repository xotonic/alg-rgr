#include "dialog.h"
#include "task1.cpp"
#include "task2.cpp"
#include "task22.cpp"
#include "ui_dialog.h"

#include <QInputDialog>
#include <QTextStream>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::log(QString msg, bool isResult = false)
{
    ui->plainTextEdit->appendPlainText(msg.prepend( isResult ? "Результат функции : " : ""));
    
}

void Dialog::on_createGraphButton_clicked()
{
    if (graf) delete graf;
    if (iv) delete iv;
    if (ie) delete ie;
    //if (ioe) delete ioe;
    
    bool directed = ui->directedCheckBox->isChecked();
    bool weight = ui->weightCheckBox->isChecked();
    bool L = ui->LCheckBox->isChecked();
    graf = new GrafType(0, L, directed, weight);
    iv = new GrafType::IteratorVertex(graf);
    ie = new GrafType::IteratorEdge(graf);
    //ioe = new GrafType::IteratorOutEdge(graf);
    QString s = "";
    s += "Граф создан : ";
    s += (L ? "L - граф" : "M - граф");
    s += ", ";
    s += (directed ? "ориентированный":"неориентированный");
    s += ", ";
    s += (weight ? "взвешенный":"невзвешенный");
    log(s);
}

void Dialog::on_insertVertexButton_clicked()
{
    graf->InsertV();
    updateScene();
}

void Dialog::updateScene()
{
    ui->graphicsView->updateScene(graf);
}

void Dialog::on_removeVertexButton_clicked()
{
    int index = ui->deleteVSpin->value();
    log(QString::number(graf->DeleteV(index)), true);
    updateScene();
}

void Dialog::on_InsertEdgeButton_clicked()
{
    int v1 = ui->deleteV1Spin->value();
    int v2 = ui->deleteV2Spin->value();
    int w = ui->deleteWeight->value();
    
    try
    {
        if(graf->w())
            graf->InsertE(v1,v2, new int(w));
        else graf->InsertE(v1,v2);
        log("Ребро добавлено");
    } 
    catch(QString e) { log(e.prepend( "Исключение : "));}
    updateScene();
}

void Dialog::on_removeEdgeButton_clicked()
{
    int v1 = ui->deleteV1Spin->value();
    int v2 = ui->deleteV2Spin->value();
    
    log(QString::number(graf->DeleteE(v1,v2)), true);
    
    updateScene();
}

void Dialog::on_vertexCountButton_clicked()
{
    log(QString::number(graf->V()), true);
}

void Dialog::on_edgeCountButton_clicked()
{
    log(QString::number(graf->E()), true);
}

void Dialog::on_graphTypeButton_clicked()
{
    log(QString::number(graf->Directed()), true);
}

void Dialog::on_viewFormButton_clicked()
{
    log(QString::number(graf->Dense()), true);
    log(graf->print());
}

void Dialog::on_toLGraphButton_clicked()
{
    log(QString::number(graf->ToListGraf()), true);
    dense = true;
    
}

void Dialog::on_pushButton_9_clicked()
{
    log(QString::number(graf->ToMatrixGraf()), true);
    dense = true;
}

void Dialog::on_nasButton_clicked()
{
    log(QString::number((double)graf->K()), true);
}

void Dialog::on_isEdgeButton_clicked()
{
    int index1 = ui->deleteV1Spin->value();
    int index2 = ui->deleteV2Spin->value();
    
    log(QString::number(graf->IsEdge(index1, index2)), true);
}

void Dialog::on_getEdgeButton_clicked()
{
    int index1 = ui->deleteV1Spin->value();
    int index2 = ui->deleteV2Spin->value();
    
    auto e = graf->GetEdge(index1, index2);
    log(e ? e->print() : "NULL");
}

void Dialog::on_vi_begin_clicked()
{
    auto e = iv->beg();
    if (e) log(e->print()); else log("Не удалось установить итератор");
}

void Dialog::on_vi_state_clicked()
{
    log(QString::number(iv->end()),true);
}

void Dialog::on_vi_next_clicked()
{
    bool r = ++(*iv);
    log(QString::number(r), true);
}

void Dialog::on_vi_get_clicked()
{
    auto v = *(*iv);
    if (v) log(v->print()); else log("Не удалось считать данные");
    
}

void Dialog::on_vi_set_name_clicked()
{
    auto v = *(*iv);
    QString *s = new QString(QInputDialog::getText(this,"Введите значение","name"));
    v->SetName(s);
}

void Dialog::on_vi_name_is_clicked()
{
    log(QString::number((*(*iv))->IsName()), true);
}

void Dialog::on_vi_get_name_clicked()
{
    auto v = *(*iv);
    if (v->IsName()) log(*v->GetName(),true);
    else log("NULL", true);
}

void Dialog::on_vi_data_set_clicked()
{
    auto v = *(*iv);
    int *s = new int(QInputDialog::getInt(this,"Введите значение","data"));
    v->SetData(s);
}

void Dialog::on_vi_data_get_clicked()
{
    auto v = *(*iv);
    if (v->IsData()) log(QString::number(*v->GetData()),true);
    else log("NULL", true);
}

void Dialog::on_pushButton_clicked()
{
    log(QString::number((*(*iv))->IsData()), true);
}

void Dialog::on_ei_begin_clicked()
{
    if (dense)
    {
        delete ie;
        ie = new GrafType::IteratorEdge(graf);
        dense = false;
    }
    auto e = ie->beg();
    if (e) log(e->print()); else log("Не удалось установить итератор");
}

void Dialog::on_ei_state_clicked()
{
    log(QString::number(ie->end()),true);
}

void Dialog::on_ei_next_clicked()
{
    bool r = ++(*ie);
    log(QString::number(r), true);
}

void Dialog::on_ei_get_clicked()
{
    auto v = *(*ie);
    if (v) log(v->print()); else log("Не удалось считать данные");
}

void Dialog::on_ei_v1_clicked()
{
    auto v = *(*ie);
    if (v)
    {
        auto v1 = v->v1;
        log(  v1 ? v1->print() : "NULL");
    }
    else log("NULL");
}

void Dialog::on_ei_v2_clicked()
{
    auto v = *(*ie);
    if (v)
    {
        auto v1 = v->v2;
        log(  v1 ? v1->print() : "NULL");
    }
    else log("NULL");
}

void Dialog::on_pushButton_3_clicked()
{
    auto v = *(*ie);
    QString *s = new QString(QInputDialog::getText(this,"Введите значение","data"));
    if (v)
        v->SetData(s); else log("NULL");
}

void Dialog::on_ie_is_data_clicked()
{
    if (*(*ie))
        log(QString::number((*(*ie))->IsData()), true);
    else log("error");
}

void Dialog::on_ie_get_data_clicked()
{
    auto v = *(*ie);
    if (v->IsData()) log(*v->GetData(),true);
    else log("NULL", true);
}

void Dialog::on_pushButton_4_clicked()
{
    auto v = *(*ie);
    int *s = new int(QInputDialog::getInt(this,"Введите значение","data"));
    if (v)
        v->SetW(s); else log("NULL");
}

void Dialog::on_ie_is_w_clicked()
{
    if (*(*ie))
        log(QString::number((*(*ie))->IsW()), true);
    else log("error");
}

void Dialog::on_ie_get_w_clicked()
{
    auto v = *(*ie);
    if (v->IsW()) log(QString::number(*(v->GetW())),true);
    else log("NULL", true);
}

void Dialog::on_oei_create_clicked()
{
    if (ioe) delete ioe;
    int index = ui->spinBox_2->value();
    if (index > graf->V()) log("wrong index");
    else ioe = new GrafType::IteratorOutEdge(graf,index);
}

void Dialog::on_oei_begin_clicked()
{
    auto e = ioe->beg();
    if (e) log(e->print()); else log("Не удалось установить итератор");
}

void Dialog::on_oei_state_clicked()
{
    log(QString::number(ioe->end()),true);
}

void Dialog::on_oei_next_clicked()
{
    bool r = ++(*ioe);
    log(QString::number(r), true);
}

void Dialog::on_oei_get_clicked()
{
    auto v = *(*ioe);
    if (v) log(v->print()); else log("Не удалось считать данные");
}

void Dialog::on_oei_v1_clicked()
{
    auto v = *(*ioe);
    if (v)
    {
        auto v1 = v->v1;
        log(  v1 ? v1->print() : "NULL");
    }
    else log("NULL");
}

void Dialog::on_oei_v2_clicked()
{
    auto v = *(*ioe);
    if (v)
    {
        auto v1 = v->v2;
        log(  v1 ? v1->print() : "NULL");
    }
    else log("NULL");
}

void Dialog::on_ioe_data_set_clicked()
{
    auto v = *(*ioe);
    QString *s = new QString(QInputDialog::getText(this,"Введите значение","data"));
    if (v)
        v->SetData(s); else log("NULL");
}

void Dialog::on_ioe_data_is_clicked()
{
    if (*(*ioe))
        log(QString::number((*(*ioe))->IsData()), true);
    else log("error");
}

void Dialog::on_ioe_data_get_clicked()
{
    auto v = *(*ioe);
    if (v->IsData()) log(*v->GetData(),true);
    else log("NULL", true);
}

void Dialog::on_ioe_set_w_clicked()
{
    auto v = *(*ioe);
    int *s = new int(QInputDialog::getInt(this,"Введите значение","data"));
    if (v)
        v->SetW(s); else log("NULL");
}

void Dialog::on_ioe_is_w_clicked()
{
    if (*(*ioe))
        log(QString::number((*(*ioe))->IsW()), true);
    else log("error");
}

void Dialog::on_ioe_get_w_clicked()
{
    auto v = *(*ioe);
    if (v->IsW()) log(QString::number(*(v->GetW())),true);
    else log("NULL", true);
}

void Dialog::on_task1Button_clicked()
{
    int index = ui->spinBox_3->value();
    if (index > graf->V()) 
    {
        log("Неверный индекс"); 
        return;
    }
    
    
    try { 
        SimpleCycles<Vertex<int, QString>, Edge<Vertex<int, QString>, int, QString> > t2(graf); 
        t2.Restart(index);
        log(t2.Result());
    }  
    catch (QString e) { log(e.prepend("Исключение: "));}
}

void Dialog::on_task2Button_clicked()
{
    int index = ui->spinBox->value();
    if (index > graf->V()) 
    {
        log("Неверный индекс"); 
        return;
    }
    try {
        ShortestWay<Vertex<int, QString> , Edge<Vertex<int, QString>, int, QString> > way(graf, this);
        way.Restart(index);
        log(way.Result());
    } catch (QString e) { log(e.prepend("Исключение: "));}
    
    
}
