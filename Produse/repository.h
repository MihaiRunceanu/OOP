
#include "domain.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>


class Repository{
private:
    vector<Produs> items;
    string filename;


    void writetofile(){
        ofstream out(filename);

        for (const Produs &i : items) {
            out << i.get_id() << ','
                << i.get_nume() << ','
                << i.get_tip() << ','
                << i.get_pret() << '\n';
        }

        out.close();
    }
    void loadfromfile(){
        ifstream in(filename);
        if (!in.is_open()) {
            throw runtime_error("Nu se poate deschide: " + filename);
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
                int id = stoi(split[0]);
                string nume = split[1];
                string tip = split[2];
                double pret = stod(split[3]);

                items.push_back(Produs(id, nume, tip, pret));
            }
        }

        in.close();
    }
public:
    Repository(const string& filename) : filename(filename) {
        loadfromfile();
    };
    vector<Produs> &getAll(){
        return items;
    }

    void store(const Produs &p){
        items.push_back(p);
        writetofile();
    }
};



