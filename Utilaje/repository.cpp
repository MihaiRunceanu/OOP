#include "repository.h"
#include <fstream>
#include <QStringList>
#include <algorithm>

void Repo::adauga(Utilaj u){
    utilaje.push_back(u);
    loadToFile();
}

void Repo::stergere(int id){
    for(int i = 0 ; i < utilaje.size();i++)
        if(utilaje.at(i).getId()==id)
            utilaje.erase(utilaje.begin()+i);
    loadToFile();
}

void Repo::modificare(int id,Utilaj u){
    for(int i = 0 ; i < utilaje.size();i++){
        if(utilaje.at(i).getId() == id)
            utilaje.at(i) = u;
    }
    loadToFile();
}

void Repo::loadFromFile(){
    ifstream fin(this->fisier);
    string line;
    while(getline(fin,line)){
        QString Qline = QString::fromStdString(line);
        QStringList list = Qline.split(',');
        Utilaj u(list.at(0).toInt(),list.at(1),list.at(2),list.at(3).toInt());
        this->utilaje.push_back(u);
    }
    fin.close();
}

void Repo::loadToFile(){
    ofstream fout(this->fisier);
    for(Utilaj x:this->utilaje){
        string obj = to_string(x.getId())+","+x.getNume().toStdString()+","+x.getTip().toStdString()+","+to_string(x.getCil());
        fout << obj << "\n";
    }
}
