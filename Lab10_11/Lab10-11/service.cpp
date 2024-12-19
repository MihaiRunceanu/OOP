#include <algorithm>
#include "service.h"
#include "exceptions.h"
#include <random>
void OfertaService::add_oferta(const string &denumire,const string &destinatie, const string &tip, int pret){
    Oferta o {denumire,destinatie,tip,pret};
    if (repo.find(denumire) !=-1)
        throw(MyException("\nExista deja o oferta cu acest nume\n\n"));
    else{
        repo.store(o);
        actiuni_undo.push_back(make_unique<UndoAdauga>(o,repo));
    }
}

void OfertaService::delete_oferta(const string &denumire) {
    int i = repo.find(denumire);
    if (i == -1)
        throw(MyException("\nNu exista nicio oferta cu acest nume\n\n"));
    else{
        Oferta o = repo.get_all()[i];
        repo.remove(i);
        actiuni_undo.push_back(make_unique<UndoSterge>(o,repo));
    }
}

void OfertaService::modify_oferta(const string &denumire,const string &destinatie,const string &tip, int pret) {
    int i = repo.find(denumire);
    if (i == -1)
        throw(MyException("\nNu exista nicio oferta cu acest nume\n\n"));
    else{
        Oferta o = repo.update(i, destinatie, tip, pret);
        actiuni_undo.push_back(make_unique<UndoModifica>(o, repo));
    }
}

int OfertaService::find_service(const string &denumire) {
    int i = repo.find(denumire);
    return i;
}

vector <Oferta> OfertaService::filtrare_service_destinatie(const string &dest) {
    vector <Oferta> lista(this->get_all_oferte().size());
    vector <Oferta> oferte = this->repo.copy_all();
    auto it = copy_if(oferte.begin(), oferte.end(), lista.begin(), [&dest](const Oferta& o) {return o.get_destinatie() == dest;});
    lista.resize(std::distance(lista.begin(), it));
    return lista;
}

vector <Oferta> OfertaService::filtrare_service_pret(int pret) {
    vector <Oferta> lista(this->get_all_oferte().size());
    vector <Oferta> oferte = this->repo.copy_all();
    auto it = copy_if(oferte.begin(), oferte.end(), lista.begin(), [&pret](const Oferta& o) {return o.get_pret() == pret;});
    lista.resize(std::distance(lista.begin(), it));
    return lista;
}

bool cmp_den(const Oferta &o1,const Oferta &o2)
{
    if (o1.get_denumire() < o2.get_denumire())
        return true;
    else
        return false;
}

bool cmp_dest(const Oferta &o1,const Oferta &o2)
{
    if (o1.get_destinatie() < o2.get_destinatie())
        return true;
    else
        return false;
}

bool cmp_tip_pret(const Oferta &o1, const Oferta &o2){
    if (o1.get_tip() < o2.get_tip())
        return true;
    if (o1.get_tip() > o2.get_tip())
        return false;
    if (o1.get_pret() > o2.get_pret())
        return false;
    else
        return true;
}

vector<Oferta> OfertaService::sortare_service(int c, bool (*cmp)(const Oferta &, const Oferta &)) {
    vector <Oferta> lista;
    vector <Oferta> oferte = this->get_all_oferte();
    lista.reserve(oferte.size());
    for (const auto & i : oferte)
        lista.push_back(i);
    if (c==1){
        sort(lista.begin(),lista.end(),cmp);
    }
    else{
        sort(lista.begin(),lista.end(),cmp);
        reverse(lista.begin(),lista.end());
    }
    return lista;
}

void OfertaService::add_oferta_wishlist(const std::string &denumire) {
    int i = repo.find(denumire);
    if (i==-1){
        throw(MyException("\nExista deja o oferta cu acest nume\n\n"));
    }
    Oferta o = {get_all_oferte()[i].get_denumire(), get_all_oferte()[i].get_destinatie(), get_all_oferte()[i].get_tip(), get_all_oferte()[i].get_pret()};
    wish_list.add_wishlist(o);
}

void OfertaService::delete_wishlist() {
    if (wish_list.get_list().empty()){
        throw MyException("\nNu mai sunt oferte de sters in wishlist\n\n");
    }

    wish_list.deleteOferte();
}

void OfertaService::random_wishlist(int n) {
    mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, this->get_all_oferte().size()-1);
    for (int i=1;i<=n;i++)
    {
        int rndNr = dist(mt);
        add_oferta_wishlist(get_all_oferte()[rndNr].get_denumire());
    }
}

map<string,DTO> OfertaService::raport_tip_oferte() {
    map<string,DTO> dict;
    for (const auto & i : this->get_all_oferte())
        if (dict.find(i.get_tip()) != dict.end())
            dict[i.get_tip()].increment();
        else
            dict[i.get_tip()].init(i.get_tip());
    return dict;}

void OfertaService::undo() {
    if (actiuni_undo.empty())
        throw(MyException("\nNu se mai poate face undo\n\n"));
    else{
        auto last = std::move(actiuni_undo.back());
        actiuni_undo.pop_back();

        last->doUndo();
    }
}

void OfertaService::export_html(const std::string &filename) {
    ofstream output_file(filename);

    output_file << "<!DOCTYPE html>\n<html lang=\"en\">\n"
                << "<head>\n<title>Book List</title>\n"
                << "<link rel=\"stylesheet\" href=\"style.css\">\n"
                << "\n</head>\n<body>\n";
    output_file << "<h1>Book List</h1>\n<ul>\n";

    for (const auto &oferta : get_wishlist()) {
        output_file << "<li>\n";
        output_file << "<strong>Denumire:</strong> " << oferta.get_denumire() << "<br>\n";
        output_file << "<strong>Destinatie:</strong> " << oferta.get_destinatie() << "<br>\n";
        output_file << "<strong>Tip:</strong> " << oferta.get_tip() << "<br>\n";
        output_file << "<strong>Pret:</strong> " << oferta.get_pret() << "<br>\n";
        output_file << "</li>\n";
    }

    output_file << "</ul>\n</body>\n</html>\n";
}
