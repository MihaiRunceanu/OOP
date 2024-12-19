#include "test.h"
#include <QDebug>
#include "service.h"

void testeRepo(){
    Repo r("C:\\Scoala\\POO\\practic-Utilaje\\Utilaje\\test.txt");

    assert(r.getAll().size() == r.getSize());
    //5,"ceva","tip",4
    //7,"ceva",tip2",8
    //10,"ceva",tip2",8
    Utilaj u(3,"nume","tip",4);
    Utilaj u1(99,"nume5","tip5",8);
    Utilaj u2(3,"nume3","tip3",2);

    r.adauga(u1);
    r.adauga(u);


    Repo r2("C:\\Scoala\\POO\\practic-Utilaje\\Utilaje\\test.txt");
    int x = r2.getSize();
    assert(r.getSize() == r2.getSize());

    Service s(r2);
    vector<int> v = s.cilindrii();
    assert(v[0] == 0);
    assert(v[1] == 0);
    assert(v[2] == 2);
    assert(v[3] == 3);

    r2.modificare(3,u2);

    v = s.cilindrii();
    assert(v[0] == 0);
    assert(v[1] == 1);
    assert(v[2] == 1);
    assert(v[3] == 3);

    s.stergere(3);
    r2.stergere(99);
    assert(r2.getSize() == x-2);



}

void Teste::testAll(){
    testeRepo();
    qDebug()<<"teste rulate";
}
