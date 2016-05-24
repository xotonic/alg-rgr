#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "graphwidget.h"
#include "graph.cpp"
namespace Ui {
class Dialog;
}

typedef Graf<Vertex<int, QString>, Edge<Vertex<int, QString>, int, QString> > GrafType;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void log(QString msg, bool isResult);
private slots:
    void on_createGraphButton_clicked();

    void on_insertVertexButton_clicked();
    void updateScene();
    void on_removeVertexButton_clicked();  
    void on_InsertEdgeButton_clicked();
    void on_removeEdgeButton_clicked();
    void on_vertexCountButton_clicked();
    void on_edgeCountButton_clicked();
    void on_graphTypeButton_clicked();
    void on_viewFormButton_clicked();
    void on_toLGraphButton_clicked();
    void on_pushButton_9_clicked();
    void on_nasButton_clicked();
    void on_isEdgeButton_clicked();
    void on_getEdgeButton_clicked(); 
    void on_vi_begin_clicked();
    
    void on_vi_state_clicked();
    
    void on_vi_next_clicked();
    
    void on_vi_get_clicked();
    void on_vi_set_name_clicked();
    void on_vi_name_is_clicked();
    
    void on_vi_get_name_clicked();
    
    void on_vi_data_get_clicked();
    
    void on_vi_data_set_clicked();
    
    void on_pushButton_clicked();
    
    void on_ei_begin_clicked();
    
    void on_ei_state_clicked();
    
    void on_ei_next_clicked();
    
    void on_ei_get_clicked();
    
    void on_ei_v1_clicked();
    
    void on_ei_v2_clicked();
    
    void on_pushButton_3_clicked();
    
    void on_ie_is_data_clicked();
    
    void on_ie_get_data_clicked();
    
    void on_pushButton_4_clicked();
    
    void on_ie_is_w_clicked();
    
    void on_ie_get_w_clicked();
    
    void on_oei_create_clicked();
    
    void on_oei_begin_clicked();
    
    void on_oei_state_clicked();
    
    void on_oei_next_clicked();
    
    void on_oei_get_clicked();
    
    void on_oei_v1_clicked();
    
    void on_oei_v2_clicked();
    
    void on_ioe_data_set_clicked();
    
    void on_ioe_data_is_clicked();
    
    void on_ioe_data_get_clicked();
    
    void on_ioe_set_w_clicked();
    
    void on_ioe_is_w_clicked();
    
    void on_ioe_get_w_clicked();
    
    void on_task1Button_clicked();
    
    void on_task2Button_clicked();
    
private:
    Ui::Dialog *ui;
    GraphWidget* gWidget;
    bool dense = true;
    bool matrix = false;
    GrafType* graf = NULL;
    GrafType::IteratorVertex* iv = NULL;
    GrafType::IteratorEdge* ie = NULL;
    GrafType::IteratorOutEdge* ioe = NULL;
};

#endif // DIALOG_H
