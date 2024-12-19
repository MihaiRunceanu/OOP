#ifndef MODEL_H
#define MODEL_H
#include "domain.h"

#include <QAbstractTableModel>
#include <vector>
#include <QString>
#include <cstring>
#include <QBrush>
#include <QDebug>
#include <algorithm>

using namespace std;

class Model: public QAbstractTableModel{
private:
    vector<Utilaj> vec;
    vector<int> tip;
public:
    Model(const vector<Utilaj>& vec1, vector<int> cilindrii): vec{vec1},tip(cilindrii){sortare();}
    int rowCount(const QModelIndex& parent) const override{
        return vec.size();
    }
    int columnCount(const QModelIndex& parent) const override{
        return 5;
    }
    QVariant data(const QModelIndex& index, int role) const override{
        if(!index.isValid() || index.row() >= vec.size())
            return QVariant();
        if(role == Qt::DisplayRole){
            Utilaj u = vec.at(index.row());
            if(index.column() == 0){
                return QString::fromStdString(to_string(u.getId()));
            }
            if(index.column() == 1){
                return u.getNume();
            }
            if(index.column() == 2){
                return u.getTip();
            }
            if(index.column() == 3){
                return QString::fromStdString(to_string(u.getCil()));
            }
            if(index.column() == 4){
                if(u.getCil()==1)
                    return tip[0];
                if(u.getCil()==2)
                    return tip[1];
                if(u.getCil() == 4)
                    return tip[2];
                if(u.getCil() == 8)
                    return tip[3];
                return QVariant();
            }
        }
        return QVariant();
    }

    ///serteaza un vectorul de utilaje dupa tip, iar daca tipurile sunt egale, dupa nume
    void sortare(){
        std::sort(vec.begin(),vec.end(),[](Utilaj u1, Utilaj u2){
            if(u1.getTip()==u2.getTip())
                return u1.getNume()<u2.getNume();
            return u1.getTip()<u2.getTip();
        });
    }

    ///updateaza vectorul din tabel, il ordoneaza  si afiseaza numarul de cilindri
    void setVector(const vector<Utilaj>& vec1,vector<int> tipuri){
        this->vec = vec1;
        sortare();
        tip[0] = tipuri.at(0);
        tip[1] = tipuri.at(1);
        tip[2] = tipuri.at(2);
        tip[3] = tipuri.at(3);
        auto topLeft =  createIndex(0,0);
        int x = vec.size();
        auto bottomR = createIndex(x,5);
        emit dataChanged(topLeft,bottomR);
        emit layoutChanged();
    }
};

#endif // MODEL_H
