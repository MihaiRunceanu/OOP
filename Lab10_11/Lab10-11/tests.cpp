#include <cassert>
#include "tests.h"
#include "service.h"
#include "exceptions.h"
#include <iostream>
void tests::test_domain() {
    string a,b,c;
    int d = 100;
    a = "denumire";
    b = "destinatie";
    c = "tip";
    Oferta o {a,b,c,d};
    assert(o.get_denumire() == "denumire");
    assert(o.get_destinatie() == "destinatie");
    assert(o.get_tip() == "tip");
    assert(o.get_pret() == 100);

    b = "destinatie_nou";
    o.set_destinatie(b);
    assert(o.get_destinatie() == "destinatie_nou");

    c = "tip_nou";
    o.set_tip(c);
    assert(o.get_tip() == "tip_nou");

    d = 999;
    o.set_pret(d);
    assert(o.get_pret() == 999);
}

void tests::test_repo() {
    OfertaRepository repo;
    string a,b,c;
    int d = 100;
    a = "denumire";
    b = "destinatie";
    c = "tip";
    Oferta o {a,b,c,d};
    assert(repo.get_all().empty());
    repo.store(o);
    assert(repo.get_all().size() == 1);
    repo.update(0, "dest_noua", "tip_nou", 215);
    assert(repo.get_all()[0].get_destinatie() == "dest_noua" and repo.get_all()[0].get_tip() == "tip_nou" and repo.get_all()[0].get_pret() == 215);
    int i = repo.find("denumire");
    assert(i == 0);
    repo.remove(0);
    assert(repo.get_all().empty());
    Oferta m {"a","b","c",5}, n {"d","e","f",6};
    repo.store(m);
    repo.store(n);
    repo.remove(0);
    i = repo.find("denumire");
    assert(i == -1);

    std::ofstream ofs;
    ofs.open("C:\\Scoala\\POO\\Lab_6\\test.txt", ofstream::out | ofstream::trunc);
    ofs.close();

    Repo_File repo_f("C:\\Scoala\\POO\\Lab_6\\test.txt");
    repo_f.store({"a","b","c",100});
    assert(repo_f.get_all().size() == 1);
    Repo_File test("C:\\Scoala\\POO\\Lab_6\\test.txt");

    repo_f.update(0,"c","d",51);
    assert(repo_f.get_all()[0].get_destinatie() == "c" and repo_f.get_all()[0].get_tip() == "d" and repo_f.get_all()[0].get_pret() == 51);

    repo_f.remove(0);
    assert(repo_f.get_all().empty());

    try{
        Repo_File r("C:\\Scoala\\POO\\Lab_6\\a.txt");
    }catch (MyException& c){
        assert(true);
    }

    RepoLab repo_l;
    repo_l.set_prob(-1);
    repo_l.store({"a","b","c",4});
    assert(repo_l.get_all().size() == 1);
    repo_l.update(0, "c", "d", 50);
    assert(repo_l.get_all()[0].get_destinatie() == "c");
    assert(repo_l.find(".") == -1);
    assert(repo_l.find("a") == 0);
    repo_l.remove(0);
    assert(repo_l.get_all().empty());
    repo_l.store({"hw","c","d",50});
    repo_l.set_prob(1000);
    try{
        repo_l.store({"b","c","d",50});
    }catch (MyException& c){
        assert(true);
    }
    try{
        repo_l.remove(0);
    }catch (MyException& c){
        assert(true);
    }
    try{
        repo_l.update(0,"ne","fq",1);
    }catch (MyException& c){
        assert(true);
    }
    try{
        repo_l.find("hw");
    }catch (MyException& c){
        assert(true);
    }
    vector <Oferta> v = repo_l.copy_all();
}

void tests::test_service() {
    OfertaRepository repo;
    WishList wish_list;
    OfertaService service{repo,wish_list};
    string a,b,c;
    int d = 100;
    a = "denumire";
    b = "destinatie";
    c = "tip";
    try{
        service.undo();
    }catch (MyException& c){
        assert(true);
    }

    //adaugare
    assert(service.get_all_oferte().empty());
    service.add_oferta(a, b, c, d);
    assert(service.get_all_oferte().size() == 1);
    try{
        service.add_oferta(a, b, c, d);
    }catch (MyException& c){
        assert(true);
    }
    //modificare
    b = "nou";
    c = "nou";
    d = 538;
    service.modify_oferta(a, b, c, d);
    assert(service.get_all_oferte()[0].get_destinatie() == b and service.get_all_oferte()[0].get_tip() == c and service.get_all_oferte()[0].get_pret() == d);
    try{
        a = "...";
        service.modify_oferta(a, b, c, d);
    }catch (MyException& c){
        assert(true);
    }
    //stergere
    a = "denumire";
    service.delete_oferta(a);
    assert(service.get_all_oferte().empty());
    try{
        service.delete_oferta(a);
    }catch (MyException& c){
        assert(true);
    }
    //cautare
    int i = service.find_service(a);
    assert(i == -1);

    //filtrare
    vector <Oferta> lista;
    service.add_oferta("d1", "destinatie", "tip", 100);
    service.add_oferta("d2", "destinatie", "weg", 35);
    service.add_oferta("d3", "a", "twhg", 100);
    lista = lista;
    lista = service.filtrare_service_destinatie("destinatie");
    assert(lista.size() == 2 and lista[0].get_tip() == "tip" and lista[1].get_tip() == "weg");
    lista = service.filtrare_service_pret(100);
    assert(lista.size() == 2 and lista[0].get_tip() == "tip" and lista[1].get_tip() == "twhg");

    //sortare
    service.add_oferta("d0","wreh","tip", 40);
    lista = service.sortare_service(1,cmp_den);
    assert(lista.size() == 4 and lista[0].get_denumire() == "d0" and lista[1].get_denumire() == "d1" and lista[2].get_denumire() == "d2" and lista[3].get_denumire() == "d3");
    lista = service.sortare_service(2, cmp_den);
    assert(lista.size() == 4 and lista[0].get_denumire() == "d3" and lista[1].get_denumire() == "d2" and lista[2].get_denumire() == "d1" and lista[3].get_denumire() == "d0");

    lista = service.sortare_service(1,cmp_dest);
    assert(lista.size() == 4 and lista[0].get_destinatie() == "a" and lista[1].get_destinatie() == "destinatie" and lista[2].get_destinatie() == "destinatie" and lista[3].get_destinatie() == "wreh");
    lista = service.sortare_service(2,cmp_dest);
    assert(lista.size() == 4 and lista[0].get_destinatie() == "wreh" and lista[1].get_destinatie() == "destinatie" and lista[2].get_destinatie() == "destinatie" and lista[3].get_destinatie() == "a");

    lista = service.sortare_service(1,cmp_tip_pret);
    assert(lista.size() == 4 and lista[0].get_tip() == "tip" and lista[1].get_tip() == "tip" and lista[0].get_pret() == 40 and lista[1].get_pret() == 100 and lista[2].get_tip() == "twhg" and lista[3].get_tip() == "weg");

    lista = service.sortare_service(2,cmp_tip_pret);
    assert(lista.size() == 4 and lista[3].get_tip() == "tip" and lista[2].get_tip() == "tip" and lista[3].get_pret() == 40 and lista[2].get_pret() == 100 and lista[1].get_tip() == "twhg" and lista[0].get_tip() == "weg");

    service.add_oferta("ag","gew","tip",50);
    lista = service.sortare_service(1,cmp_tip_pret);
    assert(lista.size() == 5);

    //wishlist
    service.add_oferta_wishlist("ag");
    assert(wish_list.get_list().size() == 1);
    service.export_html("test.html");
    try{
        service.add_oferta_wishlist(".");
    }catch (MyException& c){
        assert(true);
    }
    service.delete_wishlist();
    assert(service.get_wishlist().empty());
    try{
        service.delete_wishlist();
    }catch (MyException& c){
        assert(true);
    }

    service.random_wishlist(4);
    assert(service.get_wishlist().size() == 4);

    //raport
    map<string,DTO> raport = service.raport_tip_oferte();
    assert(raport.size() == 3);
    assert(raport["tip"].get_nr() == 3);

    //undo
    assert(service.get_actiuni_undo().size() == 8);
    service.undo();
    assert(service.get_actiuni_undo().size() == 7);
    service.undo();
    service.undo();
    service.undo();
    service.undo();
    service.undo();
    service.undo();
    service.undo();
    assert(service.get_actiuni_undo().empty());
    service.add_oferta("a","b","c",1);
    service.delete_oferta("a");
    service.undo();
    assert(service.get_all_oferte().size() == 1);
    service.modify_oferta("a","m","n",2);
    service.undo();
    assert(service.get_all_oferte()[0].get_destinatie() == "b");
    service.undo();
    assert(service.get_all_oferte().empty());
}


void tests::all_tests() {
    test_domain();
    test_repo();
    test_service();
    cout<<"Toate testele au fost verificate\n\n";
}
