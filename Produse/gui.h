

#include "service.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTableWidget>
#include "tablemodel.h"
#include <QHeaderView>
#include <QPushButton>
#include <QFormLayout>
#include <QSlider>
#include <QMessageBox>
#include <QLabel>

class TipWindow : public QWidget, public Observer{
private:
    QLabel* label = new QLabel;
    Service &serv;
    string tip;
public:
    TipWindow(Service &serv,const string &tip):serv(serv),tip(tip){
        serv.addObserver(this);
        auto fil = serv.filter_tip();
        label->setText(QString::number(fil[tip]));
        this->setWindowTitle(QString::fromStdString(tip));
        auto ly = new QHBoxLayout;
        setLayout(ly);
        ly->addWidget(label);
    }

    void update() override{
        auto fil = serv.filter_tip();
        //QMessageBox::information(this,"plm",QString::number(rape[tip]));
        label->setText(QString::number(fil[tip]));
    }

    ~TipWindow(){
        serv.delObserver(this);
    }
};


class GUI : public QWidget
{
private:
    Service &serv;
    QHBoxLayout *lyMain= new QHBoxLayout;;
    QTableView *table_view=new QTableView{this};
    TableModel *model=new TableModel{serv,this};

    QLineEdit* id = new QLineEdit;
    QLineEdit* nume = new QLineEdit;
    QLineEdit* tip = new QLineEdit;
    QLineEdit* pret = new QLineEdit;

    QPushButton* add = new QPushButton{"&Adauga"};

    QSlider* sld = new QSlider(Qt::Horizontal, this);


public:


    GUI(Service& serv) : serv{serv} {
        initGUI();
        initConnect();
    };
    void initGUI(){
        setLayout(lyMain);
        table_view->setModel(model);
        table_view->setMinimumWidth(400);
        table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        lyMain->addWidget(table_view);

        auto formly = new QFormLayout;
        formly->addRow("Id: ", id);
        formly->addRow("Nume: ", nume);
        formly->addRow("Tip: ", tip);
        formly->addRow("Pret: ", pret);
        formly->addWidget(add);

        sld->setRange(1,100);

        formly->addWidget(sld);

        lyMain->addLayout(formly);

        for (const auto &i : serv.filter_tip()){
            auto w = new TipWindow(serv, i.first);
            w->show();
        }


    }
    void initConnect(){
        connect(add, &QPushButton::clicked, [&](){
            try{
                auto txt_id = id->text().toInt();
                auto txt_nume = nume->text().toStdString();
                auto txt_tip = tip->text().toStdString();
                auto txt_pret = pret->text().toDouble();

                serv.add(txt_id, txt_nume, txt_tip, txt_pret);
                model->refreshModel();
            } catch (runtime_error &e){
                QMessageBox::warning(this, "Warning", e.what());
            }

        });

        connect(sld, &QSlider::valueChanged, [&](int val){
            model->setMaxPrice(val);
            model->updateModel();
        });
    }

};



