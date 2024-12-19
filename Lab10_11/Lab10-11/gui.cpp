#include "gui.h"

void GUI::initGUI(){
    QHBoxLayout* lymain = new QHBoxLayout{};
    setLayout(lymain);

    QLabel* oferte = new QLabel;
    oferte->setText(" Lista oferte ");
    lymain->addWidget(oferte);

    lymain->addWidget(list);
    auto stgLy = new QVBoxLayout;

    auto formLy = new QFormLayout;
    formLy->addRow("Denumire", txtDenumire);
    formLy->addRow("Destinatie", txtDestinatie);
    formLy->addRow("Tip", txtTip);
    formLy->addRow("Pret", txtPret);
    stgLy->addLayout(formLy);

    auto lyBtn2 = new QHBoxLayout{};
    lyBtn2->addWidget(btnSort);
    stgLy->addLayout(lyBtn2);

    auto lyBtn = new QHBoxLayout{};
    lyBtn->addWidget(btnAdd);
    lyBtn->addWidget(btnDel);
    lyBtn->addWidget(btnMod);
    lyBtn->addWidget(btnCaut);
    lyBtn->addWidget(btnExit);
    stgLy->addLayout(lyBtn);

    lymain->addLayout(stgLy);
}

void GUI::initConnect(){
    QObject::connect(btnExit, &QPushButton::clicked, [&]() {
        //qDebug()<<"Exit button apasat";
        QMessageBox::information(nullptr,"Info","Exit buton apasat");
        close();
    });

    QObject::connect(btnAdd, &QPushButton::clicked, [&](){
        try{
            auto denumire = txtDenumire->text();
            auto destinatie = txtDestinatie->text();
            auto tip = txtTip->text();
            auto pret = txtPret->text();
            string pret_s = pret.toStdString();
            int pret_n = -1;
            if (pret_s[0] == '0')
                pret_n = 0;
            for (int i=1;i<pret_s.size();i++)
                if (pret_s[i]>'9' or pret_s[i]<'0')
                    throw(MyException("\nPretul introdus nu este de tip int\n\n"));
            if (pret_n == -1)
                pret_n = stoi(pret_s);
            service.add_oferta(denumire.toStdString(),destinatie.toStdString(),tip.toStdString(),pret_n);
        } catch(MyException e)
        {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.what()));
        };
        loadData(service.get_all_oferte());
    });

    QObject::connect(btnDel, &QPushButton::clicked, [&](){
        try{
            auto denumire = txtDenumire->text().toStdString();
            service.delete_oferta(denumire);
        } catch(MyException e){
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.what()));
        };
        loadData(service.get_all_oferte());
    });

    QObject::connect(btnMod, &QPushButton::clicked, [&](){
        try{
            auto denumire = txtDenumire->text().toStdString();
            auto destinatie_noua = txtDestinatie->text().toStdString();
            auto tip_nou = txtTip->text().toStdString();
            auto pret_nou = txtPret->text().toStdString();
            string pret_s = pret_nou;
            int pret_n = -1;
            if (pret_s[0] == '0')
                pret_n = 0;
            for (int i=1;i<pret_s.size();i++)
                if (pret_s[i]>'9' or pret_s[i]<'0')
                    throw(MyException("\nPretul introdus nu este de tip int\n\n"));
            if (pret_n == -1)
                pret_n = stoi(pret_s);
            service.modify_oferta(denumire,destinatie_noua,tip_nou,pret_n);
        } catch(MyException e){
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.what()));
        };
        loadData(service.get_all_oferte());
    });

    QObject::connect(btnCaut, &QPushButton::clicked, [&](){
        vector <Oferta> v;
        try{
            auto denumire = txtDenumire->text().toStdString();
            int i = service.find_service(denumire);
            v.push_back(service.get_all_oferte()[i]);

        } catch(MyException e){
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.what()));
        };
        loadData(v);
    });

    QObject::connect(list, &QListWidget::itemSelectionChanged, [&](){
        auto sel = list->selectedItems();
        if (sel.isEmpty()){
            txtDenumire->setText("");
            txtDestinatie->setText("");
            txtTip->setText("");
            txtPret->setText("");
        }else{
            auto selItem = sel.at(0);
            auto denumire = selItem->text();
            txtDenumire->setText(denumire);
            auto i = service.find_service(denumire.toStdString());
            txtDestinatie->setText(QString::fromStdString(service.get_all_oferte()[i].get_destinatie()));
            txtTip->setText(QString::fromStdString(service.get_all_oferte()[i].get_tip()));
            txtPret->setText(QString::fromStdString(std::to_string(service.get_all_oferte()[i].get_pret())));

        }
    });

    QObject::connect(btnSort, &QPushButton::clicked, [&](){
        vector <Oferta> sort;
        try{
            auto gui = new Small_GUI{};
            gui->show();
            //sort = service.sortare_service(1, cmp_den);
        }catch(MyException e){
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.what()));
        };
        loadData(sort);
    });
}

void GUI::loadData(vector <Oferta> l){
    list->clear();
    for (const auto& oferta : l){
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(oferta.get_denumire()));
        item->setBackground(QBrush{Qt::red, Qt::SolidPattern});
        list->addItem(item);
    }
}
