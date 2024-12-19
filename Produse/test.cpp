#include "test.h"

void Test::test_domain(){
    Produs p(1,"nm","tip",10);
    assert(p.get_id() == 1);
    assert(p.get_nume() == "nm");
    assert(p.get_pret() == 10);
    assert(p.get_tip() == "tip");
}

void Test::test_repo(){
    std::ofstream ofs;
    ofs.open("C:\\Scoala\\POO\\practic-Produse\\Produse\\test.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();


    Repository repo("C:\\Scoala\\POO\\practic-Produse\\Produse\\test.txt");
    Produs p(1,"nm","tip",10);

    assert(repo.getAll().empty());
    repo.store(p);
    assert(repo.getAll().size() == 1);

}

void Test::test_service(){
    std::ofstream ofs;
    ofs.open("C:\\Scoala\\POO\\practic-Produse\\Produse\\test.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    Repository repo("C:\\Scoala\\POO\\practic-Produse\\Produse\\test.txt");
    Service serv{repo};

    serv.add(1,"nm","tip",10);
    assert(serv.getAll().size() == 1);

    try{
        serv.add(5,"","tip",2);
        assert(false);
    } catch (runtime_error &e){
        assert(true);
    }
}
