#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <vector>
#include <QString>
#include "domain.h"
#include "repository.h"
#include <QString>
#include <QDebug>

using namespace std;

class Service
{
private:
    Repo& repo;
public:
    ///constructor
    /// r - un repo
    Service(Repo& r):repo{r}{}
    ///sterge elementul de la id-ul primit
    /// id - un id din lista
    void stergere(int id);
    ///modifica elementul de la id-ul primit
    /// primeste datele unui nou utilaj, cu care va fi inlocuit cel vechi
    void modificare(int id,QString nume, QString tip, int cil);
    ///returneaza lista de utilitati
    vector<Utilaj> getAll(){return repo.getAll();}
    ///returneaza un vector cu 4 elemente, in care valoarea fiecarui element reprezinta nr de utilaje cu cilindrii corespunzatori(v[0]-1cilindru, v[1]-2 cilindri,v[2]-4 cilindri, v[3] - 8 cilindri
    vector<int> cilindrii();
};

#endif // SERVICE_H
