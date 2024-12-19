#include "repository.h"
#include <vector>
#include <map>
#include <memory>
#include "wishlist.h"
#include "undo.h"
#include <fstream>
using namespace std;
class OfertaService {
private:
    RepoAbstract &repo;
    WishList &wish_list;
    vector<unique_ptr<ActiuneUndo>> actiuni_undo;
public:
    //Constructor pentru service
    //Contine un repository si un wishlist ca si campuri
    OfertaService(RepoAbstract &repository, WishList &wish_list) : repo{repository}, wish_list{wish_list} {
        std::ofstream html("C:\\Scoala\\POO\\Lab_6\\export.html");
        html.close();
    }

    //Adauga o oferta in lista de oferte
    void add_oferta(const string &denumire, const string &destinatie, const string &tip, int pret);

    //Sterge o oferta din lista de oferte
    void delete_oferta(const string &denumire);

    //Modifica o oferta din lista de oferte
    void modify_oferta(const string &denumire,const string &destinatie,const string &tip, int pret);

    //Returneaza lista de oferte
    //Return type: vector <Oferta>
    const vector<Oferta> &get_all_oferte(){
        return repo.get_all();
    }

    const vector<Oferta> &get_wishlist(){
        return wish_list.get_list();
    }

    const vector<unique_ptr<ActiuneUndo>> &get_actiuni_undo(){
        return actiuni_undo;
    }

    //Filtreaza lista de oferte dupa o destinatie data ca parametru
    //Return: un vector ce contine lista filtrata
    //Return Type: vector <Oferta>
    vector <Oferta> filtrare_service_destinatie(const string &dest);

    //Filtreaza lista de oferte dupa un pret data ca parametru
    //Return: un vector ce contine lista filtrata
    //Return Type: vector <Oferta>
    vector <Oferta> filtrare_service_pret(int pret);

    //Cauta o oferta din lista dupa o denumire data
    //Parametru: denumire -> denumirea data
    int find_service(const string &denumire);

    //Sorteaza lista de oferte dupa un criteriu
    //Param: c -> determina in ce ordine se sorteaza elementele(1 -> crescator, 2 -> descrescator)
    //Param: cmp -> o functie ce compara doua oferte dupa un anumit criteriu
    //Param type: int, bool
    //Returneaza un vector ce contine ofertele sortate
    vector<Oferta> sortare_service(int c, bool(*cmp)(const Oferta &o1, const Oferta &o2));

    void add_oferta_wishlist(const string &denumire);

    void delete_wishlist();

    void random_wishlist(int n);

    map<string,DTO> raport_tip_oferte();

    void undo();

    void export_html(const string &filename);
};

//Compara doua oferte dupa destinatie
//Parametrii: o1 -> prima oferta, o2 -> a doua oferta
//Parametrii type: Oferta
bool cmp_dest(const Oferta &o1,const Oferta &o2);

//Compara doua oferte dupa denumire
//Parametrii: o1 -> prima oferta, o2 -> a doua oferta
//Parametrii type: Oferta
bool cmp_den(const Oferta &o1,const Oferta &o2);

//Compara doua oferte dupa tip si pret
//Parametrii: o1 -> prima oferta, o2 -> a doua oferta
//Parametrii type: Oferta
bool cmp_tip_pret(const Oferta &o1, const Oferta &o2);

