#ifndef GUI_H
#define GUI_H

#include "service.h"
#include "domain.h"
#include "tablemodel.h"

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QSlider>
#include <QPainter>
#include <QItemSelectionModel>
#include <QRadioButton>
#include <QHBoxLayout>

class GUI: public QWidget
{
private:
    int idCurent = -1;
    Service& service;

    QVBoxLayout* mL = new QVBoxLayout;

    QTableView* tv = new QTableView;
    Model* model = new Model{service.getAll(),service.cilindrii()};

    QLineEdit* lineName = new QLineEdit;
    QLineEdit* lineTip = new QLineEdit;
    QLineEdit* lineCil = new QLineEdit;
    QLabel* lName = new QLabel("Nume: ");
    QLabel* lTip = new QLabel("Tip: ");
    QLabel* lCil = new QLabel("cilindrii: ");
    QHBoxLayout* qh2 = new QHBoxLayout;
    QHBoxLayout* qh3 = new QHBoxLayout;
    QHBoxLayout* qh4 = new QHBoxLayout;

    QPushButton* bModifica = new QPushButton("Modifica utilaj");
    QPushButton* bSterge = new QPushButton("Sterge utilaj");

    QPushButton* bSelect = new QPushButton("arata titlul");

    QSlider * slider = new QSlider;
    QRadioButton* radioC[4] = {new QRadioButton,new QRadioButton,new QRadioButton,new QRadioButton};
    QHBoxLayout* qhRadio = new QHBoxLayout;

public:
    ///constructor
    /// s - un service
    GUI(Service &s):service(s){
        initializareGUI();
        initializareConn();
    }
    ///aseaza elementele vizuale in layout
    void initializareGUI();
    ///conecteaza functile la obiecte
    void initializareConn();
    ///deseneaza cercurile pentru cilindri
    void paintEvent(QPaintEvent* ev) override{
        vector<int> vec = service.cilindrii();
        QPainter painter{this};
        for(int i = 0 ; i < 4 ; i ++){
            painter.drawEllipse(QPoint(i*100,height()),10*vec[i],10*vec[i]);
        }
    }
};

#endif // GUI_H
