#include <string>
#include <iostream>
#include <utility>
using namespace std;
#pragma once

class Oferta {

private:
    string denumire;
    string destinatie;
    string tip;
    int pret;

public:

    //Constructor pentru Oferta
    Oferta(const string denumire_o, const string destinatie_o, const string &tip_o,int pret_o) : denumire{denumire_o}, destinatie{destinatie_o}, tip{tip_o}, pret{pret_o} {};

    Oferta() = default;

    //Constructor copiere
    Oferta(const Oferta &other) : denumire{other.denumire}, destinatie{other.destinatie}, tip{other.tip}, pret{other.pret} {
        cout<<"Contructor copie apelat\n";
    }

    //Returneaza pretul unei oferte
    int get_pret() const;

    //Returneaza denumirea unei oferte
    string get_denumire() const;

    //Returneaza destinatia unei oferte
    string get_destinatie() const;

    //Returneaza tipul unei oferte
    string get_tip() const;

    //Modifica pretul unei oferte
    //Parametru: pret_n -> pretul nou, de tip int
    void set_pret(int pret_n);

    //Modifica destinatia unei oferte
    //Parametru: dest_n -> destinatia noua, de tip string
    void set_destinatie(const string &dest_n);

    //Modifica tipul unei oferte
    //Parametru: tip_n -> tipul nou, de tip int
    void set_tip(const string &tip_n);
};



