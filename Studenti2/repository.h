#pragma once
#include<vector>
#include<fstream>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include"domain.h"
using std::vector;
using namespace std;

class repo
{
private:
    vector<student>st;
    string name;
public:
    repo(string name):name{name}{
        loadFromFile();
    }
    repo(const repo& rep) = delete;
    /*
    * caut in vector daca exista nr matricol

    */
    int cauta(int matricol) {
        auto index = find_if(st.begin(), st.end(), [&](const student& s) {
            return s.get_matricol() == matricol;
        });
        if (index != st.end()) {
            int rez = index- st.begin();
            return rez;
        }
        return -1;
    }
    /*
    * caut daca exista obicetul daca da arunc exceptie
    * daca nu  adaug
    */
    void adauga(student& s) {
        int index = cauta(s.get_matricol());
        if (index != -1) {
            throw runtime_error("exista");
        }
        st.push_back(s);
        writeToFile();
    }
    vector<student>& getAll() {
        return st;
    }
    /*
        scriere din fisier
    */
    void writeToFile() {
        std::ofstream out(name);
        if (!out.is_open()) {
            throw runtime_error("nu s-a deschis\n");
        }

        for (auto& prod : getAll()) {

            out << prod.get_matricol() << "," << prod.get_nume() << "," << prod.get_varsta() << "," << prod.get_facultate() << "\n";
        }
        out.close();
    }
    void loadFromFile() {
        ifstream in(name);
        if (!in.is_open()) {
            throw runtime_error("Nu se poate deschide: " + name);
        }

        std::string line;
        while (std::getline(in, line)) {
            std::stringstream stream(line);

            std::string token;
            std::vector<std::string> split;

            while (getline(stream, token, ',')) {
                split.push_back(token);
            }

            if (split.size() == 4) {
                int mat = stoi(split[0]);
                std::string nume = split[1];
                int varsta = stoi(split[2]);
                std::string facultate = split[3];

                st.push_back(student(mat, nume, varsta, facultate));
            }
        }

        in.close();

    }
    void modifica(string x) {

        for (auto& student : st) {
            if (student.get_varsta() == 0) {
                if (x == "intinerire") {
                    throw runtime_error("nu se mai poate\n!");
                    return;
                }
            }
            student.set_varsta(x);
        }

        writeToFile();

    }
    /*
    * caut daca exista obicetul daca nu arunc exceptie
    * daca da sterg
    */
    void sterge_repo(student& stud) {
        auto index = cauta(stud.get_matricol());
        if (index == -1) {
            throw runtime_error("obiectul nu exista!\n");
        }
        st.erase(st.begin() + index);
        writeToFile();
    }

};
