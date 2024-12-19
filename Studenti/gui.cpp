#pragma once
#include "gui.h"

void GUI::init() {
    QHBoxLayout* main=new QHBoxLayout;
    setLayout(main);
    myT=new MyTable{ctr.getAll()};
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setModel(myT);
    main->addWidget(table);
    QVBoxLayout* dr=new QVBoxLayout;
    main->addLayout(dr);
    dr->addWidget(imbatranire);
    dr->addWidget(intinerire);
    dr->addWidget(sterge);
    dr->addWidget(undo);
    dr->addWidget(redo);
    resize(1000,500);


}

void GUI::connectBut() {
    QObject::connect(sterge,&QPushButton::clicked,[&](){
        auto sel=table->selectionModel()->selectedRows();
        if(sel.empty())
            QMessageBox::warning(this,"!","SELECTION EMPTY");
        else
        {
            vector<Student> toDelete;
            for(auto i:sel)
            {
                QModelIndex &index=i;
                auto st=myT->getStudent(i);
                cout<<st.getFacultate();
                toDelete.push_back(st);
            }
            ctr.stergereMultipla(toDelete);
            loadTable();
        }

    });
    QObject::connect(imbatranire,&QPushButton::pressed,[&](){
        ctr.updateAll(1);
        loadTable();

    });
    QObject::connect(undo,&QPushButton::pressed,[&](){
        try
        {
            ctr.UndoAct();

        }
        catch (runtime_error &e)
        {
            QMessageBox::warning(this,"!",QString::fromStdString(e.what()));
        }
        loadTable();

    });
    QObject::connect(redo,&QPushButton::pressed,[&](){
        try
        {
            ctr.RedoAct();

        }
        catch (runtime_error &e)
        {
            QMessageBox::warning(this,"!",QString::fromStdString(e.what()));
        }
        loadTable();

    });
    QObject::connect(intinerire,&QPushButton::pressed,[&](){
        ctr.updateAll(-1);
        loadTable();

    });
}

void GUI::loadTable() {
    myT->setStudenti(ctr.getAll());
}
