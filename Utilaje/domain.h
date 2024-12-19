#ifndef UTILAJ_H
#define UTILAJ_H

#include <string>
#include <vector>
#include <QString>

using namespace std;

class Utilaj{
private:
    int id;
    QString nume;
    QString tip;
    int cilindrii;
public:
    Utilaj(int id1, QString nume1, QString tip1 , int cilindrii1):id(id1),nume(nume1),tip(tip1),cilindrii(cilindrii1){}
    void setId(int id1){id = id1;}
    void setNume(QString nume1){nume=nume1;}
    void setTip(QString tip1){tip = tip1;}
    void setCil(int cil1){cilindrii=cil1;}
    int getId(){return id;}
    QString getNume(){return nume;}
    QString getTip(){return tip;}
    int getCil(){return cilindrii;}
};

#endif // UTILAJ_H
