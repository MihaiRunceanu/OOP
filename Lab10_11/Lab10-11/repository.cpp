#include <fstream>
#include "exceptions.h"
#include "repository.h"
#include <algorithm>
#include <utility>
#include <sstream>
#include <random>
void OfertaRepository::store(const Oferta &o){
    lista_oferte.push_back(o);
}



int OfertaRepository::find(const std::string &denumire) {
    auto it = find_if(lista_oferte.begin(),lista_oferte.end(), [&denumire](const Oferta &o) {return o.get_denumire() == denumire;});
    int i = int(distance(lista_oferte.begin(),it));
    if (i == lista_oferte.size())
        return -1;
    return i;
}

void OfertaRepository::remove(int i) {
    lista_oferte.erase(lista_oferte.begin() + i);
}

Oferta OfertaRepository::update(int i, const string &destinatie_noua, const string &tip_nou, int pret_nou) {
    Oferta o (lista_oferte[i].get_denumire(), destinatie_noua, tip_nou, pret_nou);
    Oferta p (lista_oferte[i].get_denumire(),lista_oferte[i].get_destinatie(),lista_oferte[i].get_tip(),lista_oferte[i].get_pret());
    lista_oferte[i].set_destinatie(o.get_destinatie());
    lista_oferte[i].set_tip(o.get_tip());
    lista_oferte[i].set_pret(o.get_pret());
    return p;
}

Repo_File::Repo_File(std::string filename) : OfertaRepository(), filename{std::move(filename)}{
    loadFromFile();
}

void Repo_File::loadFromFile() {
    ifstream in(filename);
    if (!in.is_open()) {
        throw MyException("Nu se poate citi fisierul " + filename);
    }

    string line;
    while (getline(in, line)) {
        stringstream stream(line);

        string token;
        vector<string> split;

        while (getline(stream, token, ',')) {
            split.push_back(token);
        }

        if (split.size() == 4) {
            string denumire = split[0];
            string destinatie = split[1];
            string tip = split[2];
            int pret = stoi(split[3]);

            OfertaRepository::store({denumire, destinatie, tip, pret});
        }
    }

    in.close();
}

void Repo_File::writeToFile() {
    std::ofstream out(filename);

    for (const Oferta &oferta : lista_oferte) {
        out << oferta.get_denumire() << ','
            << oferta.get_destinatie() << ','
            << oferta.get_tip() << ','
            << oferta.get_pret() << '\n';
    }

    out.close();
}

void Repo_File::store(const Oferta &o) {
    OfertaRepository::store(o);
    writeToFile();
}

void Repo_File::remove(int i) {
    OfertaRepository::remove(i);
    writeToFile();
}

Oferta Repo_File::update(int i, const std::string &destinatie_noua, const std::string &tip_nou, int pret_nou) {
    Oferta o = OfertaRepository::update(i,destinatie_noua,tip_nou,pret_nou);
    writeToFile();
    return o;}

void RepoLab::store(const Oferta &o) {
    mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, 10);
    int rand = dist(mt);
    if (rand < prob)
        throw(MyException("\nProbabilitate random\n\n"));
    int i = oferte.size();
    oferte.insert({i,o});
    list.push_back(o);
}

void RepoLab::remove(int i) {
    mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, 10);
    int rand = dist(mt);
    if (rand < prob)
        throw(MyException("\nProbabilitate random\n\n"));
    oferte.erase(i);
    list.erase(list.begin() + i);
}

Oferta RepoLab::update(int i, const std::string &destinatie_noua, const std::string &tip_nou, int pret_nou) {
    mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, 10);
    int rand = dist(mt);
    if (rand < prob)
        throw(MyException("\nProbabilitate random\n\n"));
    Oferta o = oferte[i];
    oferte[i].set_destinatie(destinatie_noua);
    oferte[i].set_pret(pret_nou);
    oferte[i].set_tip(tip_nou);
    list[i].set_destinatie(destinatie_noua);
    list[i].set_tip(tip_nou);
    list[i].set_pret(pret_nou);
    return o;}

int RepoLab::find(const std::string &denumire) {
    mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, 10);
    int rand = dist(mt);
    if (rand < prob)
        throw(MyException("\nProbabilitate random\n\n"));
    for (const auto & i : oferte)
        if (i.second.get_denumire() == denumire)
            return i.first;
    return -1;
}
