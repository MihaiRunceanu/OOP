#include "domain.h"
#include <vector>
#include <map>
#pragma once
using namespace std;

class RepoAbstract{
public:
    virtual ~RepoAbstract() = default;

    virtual void store(const Oferta &o) = 0;

    virtual void remove(int i) = 0;

    virtual Oferta update(int i, const string &destinatie_noua, const string &tip_nou, int pret_nou) = 0;

    virtual int find(const string &denumire) = 0;

    virtual vector<Oferta> &get_all() = 0;

    virtual vector<Oferta> copy_all() const = 0;
};

class OfertaRepository : public RepoAbstract{
protected:
    vector<Oferta> lista_oferte;
public:
    //Returneaza lista de oferte
    vector<Oferta> &get_all() override {
        return lista_oferte;
    }

    vector<Oferta> copy_all() const override{
        return this->lista_oferte;
    }

    //Constructor pentru repository
    OfertaRepository() = default;

    ~OfertaRepository() override = default;

    //Adauga in lista de oferte
    //Parametru: o -> oferta ce se adauga in lista
    //Parametru type: Oferta
    void store(const Oferta &o) override;

    //Sterge din lista de oferte
    //Oferta situata pe pozitia i
    //Parametrul i este de tip int
    void remove(int i) override;

    //Modifica din lista de oferte
    //Oferta situata pe pozitia i
    //Parametrii: destinatie_noua -> destinatia noua, tip_nou -> tipul nou si pret_nou -> pretul nou al ofertei
    Oferta update(int i, const string &destinatie_noua, const string &tip_nou, int pret_nou) override;

    //Cauta oferta din lista
    //Parametru: denumire -> denumirea pe care o cauta in lista
    //Parametru type: string
    int find(const string &denumire) override;
};

class Repo_File : public OfertaRepository{
private:
    string filename;
public:
    void loadFromFile();

    void writeToFile();

    explicit Repo_File(string filename);

    void store(const Oferta &o) override;

    void remove(int i) override;

    Oferta update(int i, const string &destinatie_noua, const string &tip_nou, int pret_nou) override;
};

class RepoLab : public RepoAbstract{
private:
    double prob = 5;
    map <int,Oferta> oferte;
    vector <Oferta> list;
public:
    RepoLab() = default;

    ~RepoLab() override = default;

    void store(const Oferta &o) override;

    void remove(int i) override;

    void set_prob(int p_noua){
        prob = p_noua;
    }

    Oferta update(int i, const string &destinatie_noua, const string &tip_nou, int pret_nou) override;

    vector<Oferta> copy_all() const override{
        return list;
    }

    vector<Oferta> &get_all() override{
        return list;
    }

    int find(const string &denumire) override;
};

class DTO{
private:
    int nr;
    string tip;
public:
    DTO() : nr{0}, tip{"."} {};

    void increment(){
        nr++;
    }
    void init(const string &tip_n){
        nr = 1;
        tip = tip_n;
    }
    int get_nr() const{
        return nr;
    }
};
