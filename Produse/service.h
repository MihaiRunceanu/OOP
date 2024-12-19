#pragma once
#include "repository.h"
#include "observer.h"
class Service : public Observable
{
private:
    Repository &repo;
public:
    Service(Repository& repo): repo(repo) {};

    vector<Produs> getAll(){
        vector<Produs> res{repo.getAll()};

        sort(res.begin(), res.end(),
                  [&](const Produs &p1, const Produs &p2) {
                      return p1.get_pret() < p2.get_pret();
                  });

        return res;
    }

    unordered_map<string,int> raport_voc(){
        unordered_map<string,int> res;
        for (const auto &i : repo.getAll()){
            for (int j=0;j<i.get_nume().length();j++)
                if (i.get_nume()[j] == 'a' or i.get_nume()[j] == 'e' or i.get_nume()[j] == 'i' or i.get_nume()[j] == 'o' or i.get_nume()[j] == 'u' or i.get_nume()[j] == 'A' or i.get_nume()[j] == 'E' or i.get_nume()[j] == 'I' or i.get_nume()[j] == 'O' or i.get_nume()[j] == 'U')
                    res[i.get_nume()] += 1;
        }
        return res;
    }

    void add(int id, const string &nume, const string &tip, double pret){
        string errors;
        if (nume == "")
            errors.append("Numele este gol\n");
        if (pret < 1.0 or pret > 100.0)
            errors.append("Pretul nu se incadreaza in 1 si 100\n");
        for (const auto &i : getAll()){
            if (i.get_id() == id){
                errors.append("Exista deja un produs cu acest id\n");
                break;
            }
        }
        if (!errors.empty())
            throw runtime_error(errors);

        Produs p(id, nume, tip, pret);
        repo.store(p);
        notify();
    }

    vector<Produs> filter(int pret){
        vector<Produs> rez;
        for (const auto &i : repo.getAll()){
            if (i.get_pret() <= pret)
                rez.push_back(i);
        }
        return rez;
    }

    unordered_map<string,int> filter_tip(){
        unordered_map<string,int> rez;
        for (const auto &i : repo.getAll()){
            rez[i.get_tip()] += 1;
        }
        return rez;
    }
};
