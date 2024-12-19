#pragma once
using namespace std;
#include "domain.h"
#include <utility>
#include <vector>

class Repository {
private:
    std::vector<Melodie> items;
    std::string file_name;

    void loadFromFile();
    void writeToFile();
public:
    explicit Repository(std::string file_name) : file_name(std::move(file_name)) {
        loadFromFile();
    }

    std::vector<Melodie> getAll() {
        return items;
    }

    void addSong(const Melodie &song);
    void deleteSong(int id);
    bool findSong(int id);
};
