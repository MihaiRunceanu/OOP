#pragma once
#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QListWidget>
#include <QMessageBox>
#include "service.h"
#include "exceptions.h"

class GUI : public QWidget
{
    Q_OBJECT
public:

    GUI(OfertaService &serv) : service{serv} {
        initGUI();
        initConnect();
        loadData(service.get_all_oferte());
    }
protected:
    QPushButton* btnAdd = new QPushButton{" &Adauga "};
    QPushButton* btnDel = new QPushButton{" &Sterge "};
    QPushButton* btnMod = new QPushButton{" &Modifica "};
    QPushButton* btnCaut = new QPushButton{" &Cautare "};
    QPushButton* btnExit = new QPushButton{" &Exit "};

    QPushButton* btnSort = new QPushButton{" &Sortare "};

    QLineEdit* txtDenumire = new QLineEdit;
    QLineEdit* txtDestinatie = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtPret = new QLineEdit;

    QListWidget* list = new QListWidget;

    OfertaService &service;

    void initConnect();

    void initGUI();

    void loadData(vector <Oferta> l);
signals:
};

class Small_GUI : public QWidget{
private:
    QLabel* lbl = new QLabel("Oferte sortate");
    QPushButton* btn1 = new QPushButton{" &Dupa denumire "};
    QPushButton* btn2 = new QPushButton{" &Dupa destinatie "};
    QPushButton* btn3 = new QPushButton{" &Dupa tip si pret "};
public:
    Small_GUI(){
        QHBoxLayout* ly = new QHBoxLayout;
        setLayout(ly);
        ly->addWidget(lbl);
        QListWidget* list = new QListWidget;
        ly->addWidget(list);

        QVBoxLayout* lybtn = new QVBoxLayout;
        lybtn->addWidget(btn1);
        lybtn->addWidget(btn2);
        lybtn->addWidget(btn3);

        ly->addLayout(lybtn);
    }

    void connect(){
        QObject::connect(btn1, &QPushButton::clicked, [&](){
            //vector<Oferta> sort = service.sortare_service(1,cmp_den);
            //loadData(sort);
        });
    }
};

