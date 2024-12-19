#include "domain.h"
int Oferta::get_pret() const {
    return this->pret;
}

string Oferta::get_denumire() const {
    return this->denumire;
}

string Oferta::get_destinatie() const {
    return this->destinatie;
}

string Oferta::get_tip() const {
    return this->tip;
}

void Oferta::set_pret(int pret_n) {
    this->pret = pret_n;
}

void Oferta::set_destinatie(const std::string &dest_n) {
    this->destinatie = dest_n;
}

void Oferta::set_tip(const std::string &tip_n) {
    this->tip = tip_n;
}
