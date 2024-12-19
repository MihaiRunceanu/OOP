#include "gui.h"
#include <QMessageBox>

void GUI::initializareGUI(){
    this->setLayout(this->mL);
    tv->setModel(model);
    mL->addWidget(tv);
    qh2->addWidget(lName);
    qh2->addWidget(lineName);
    mL->addLayout(qh2);
    qh3->addWidget(lTip);
    qh3->addWidget(lineTip);
    mL->addLayout(qh3);
    //qh4->addWidget(lCil);
    //qh4->addWidget(lineCil);
    //mL->addLayout(qh4);
    mL->addWidget(bModifica);
    mL->addWidget(bSterge);
    qhRadio->addWidget(radioC[0]);
    radioC[0]->setText("1 cilindru");
    qhRadio->addWidget(radioC[1]);
    radioC[1]->setText("2 cilindrii");
    qhRadio->addWidget(radioC[2]);
    radioC[2]->setText("4 cilindrii");
    qhRadio->addWidget(radioC[3]);
    radioC[3]->setText("8 cilindrii");
    mL->addLayout(qhRadio);
}

void GUI::initializareConn(){

    QItemSelectionModel::connect(tv->selectionModel(),&QItemSelectionModel::selectionChanged,[this](){
        if(tv->selectionModel()->selectedIndexes().size()>0){
            idCurent = tv->model()->index(tv->selectionModel()->selectedIndexes().at(0).row(),0).data().toInt();
            lineName->setText(tv->model()->index(tv->selectionModel()->selectedIndexes().at(0).row(),1).data().toString());
            lineTip->setText(tv->model()->index(tv->selectionModel()->selectedIndexes().at(0).row(),2).data().toString());
            lineCil->setText(tv->model()->index(tv->selectionModel()->selectedIndexes().at(0).row(),3).data().toString());
            int cil = tv->model()->index(tv->selectionModel()->selectedIndexes().at(0).row(),3).data().toInt();
            if(cil == 1){
                radioC[0]->setChecked(true);
            }
            if(cil == 2){
                radioC[1]->setChecked(true);
            }
            if(cil == 4){
                radioC[2]->setChecked(true);
            }
            if(cil == 8){
                radioC[3]->setChecked(true);
            }
            qDebug()<<idCurent;
        }
    });
    QPushButton::connect(bSterge,&QPushButton::clicked,[this](){
        if(idCurent!=-1){
            vector<int> vec = service.cilindrii();
            int cil = tv->model()->index(tv->selectionModel()->selectedIndexes().at(0).row(),3).data().toInt();
            if((cil == 1 && vec[0] == 1) || (cil == 2 && vec[1] == 1) || (cil == 4 && vec[2] == 1) || (cil == 8 && vec[3] == 1))
            {
                QMessageBox* m = new QMessageBox;
                m->setText("este ultimul element");
                m->show();
                return;
            }
            service.stergere(idCurent);
            model->setVector(service.getAll(),service.cilindrii());
            repaint();
            return;
        }
        QMessageBox* m = new QMessageBox;
        m->setText("niciun element selectat");
        m->show();
        return;
    });
    QPushButton::connect(bModifica,&QPushButton::clicked,[this](){
        if(idCurent!=-1){
            int cil = -1;
            if(radioC[0]->isChecked()){
                cil = 1;
            }
            if(radioC[1]->isChecked()){
                cil = 2;
            }
            if(radioC[2]->isChecked()){
                cil = 4;
            }
            if(radioC[3]->isChecked()){
                cil = 8;
            }
            //service.modificare(idCurent,lineName->text(),lineTip->text(),lineCil->text().toInt());
            service.modificare(idCurent,lineName->text(),lineTip->text(),cil);
            model->setVector(service.getAll(),service.cilindrii());
            repaint();
            return;
        }
        QMessageBox* m = new QMessageBox;
        m->setText("niciun element selectat");
        m->show();
        return;
    });
}
