#include "service.h"

vector<int> Service::cilindrii(){
    vector<Utilaj> vec = repo.getAll();
    vector<int> rez;
    rez.push_back(0);
    rez.push_back(0);
    rez.push_back(0);
    rez.push_back(0);
    for(auto u:vec){
        if(u.getCil()==1)
            rez[0]++;
        if(u.getCil()==2)
            rez[1]++;
        if(u.getCil() == 4)
            rez[2]++;
        if(u.getCil() == 8)
            rez[3]++;
    }
    return rez;
}

void Service::stergere(int id){
    repo.stergere(id);
}

void Service::modificare(int id,QString nume, QString tip, int cil){
    Utilaj u(id,nume,tip,cil);
    repo.modificare(id,u);
}
