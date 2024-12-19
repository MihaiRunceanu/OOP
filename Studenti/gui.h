#pragma once
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include "Service.h"
#include "tablemodel.h"
#include <QMessageBox>
class GUI :public QWidget{
    //tabel
    QTableView* table=new QTableView;
    MyTable* myT;
    //butoane
    QPushButton* intinerire=new QPushButton{"intinerire"};
    QPushButton* imbatranire=new QPushButton{"imbatranire"};
    QPushButton* sterge=new QPushButton{"sterge"};
    QPushButton* undo=new QPushButton{"undo"};
    QPushButton* redo=new QPushButton{"redo"};
    //referinta la service
    Service &ctr;
    //functii
    void init();
    void connectBut();
    void loadTable();
public:
    GUI(Service &c):ctr(c){
        init();
        connectBut();
        loadTable();
    }


};

