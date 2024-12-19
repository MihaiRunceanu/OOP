
#pragma once

#include <string>
using namespace std;



class Produs{
private:
    int id;
    string nume;
    string tip;
    double pret;

public:
    Produs(int id, const string &nume, const string &tip, double pret) : id{id}, nume{nume}, tip{tip}, pret{pret} {};

    int get_id() const{
        return id;
    }

    string get_nume() const{
        return nume;
    }

    string get_tip() const{
        return tip;
    }

    double get_pret() const{
        return pret;
    }
};


