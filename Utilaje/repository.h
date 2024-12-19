#ifndef REPO_H
#define REPO_H

#include <string>
#include <vector>
#include <QString>
#include "domain.h"

using namespace std;

class Repo
{
private:
    vector<Utilaj> utilaje;
    string fisier;
public:
    ///constructor
    /// fisier1 - fisierul din care se citeste
    Repo(string fisier1):fisier(fisier1){loadFromFile();}
    ///adauga un utilaj la lista
    /// u - un utilaj  valid
    void adauga(Utilaj u);
    ///sterge elementul cu id-ul primit din lista
    /// id- un id care exista in tabel
    void stergere(int id);
    ///modifica elementul de la id-ul primit cu utilajul primit ca parametru
    /// id- un id din lista
    /// u - un utilaj
    void modificare(int id,Utilaj u);
    ///incarca datele din tabel
    void loadFromFile();
    ///incarca datele din fisier
    void loadToFile();
    ///returneaza dimensiunea listei de utilaje
    int getSize(){return utilaje.size();}
    ///returneaza toata lista de utilaje
    vector<Utilaj> getAll(){return utilaje;}
};

#endif // REPO_H
