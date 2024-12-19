#pragma once
using namespace std;
#include "domain.h"
#include <algorithm>
#include <vector>

class Repository {
private:
    std::vector<Track> items;
    std::string file_name;

    void loadFromFile();
    void saveToFile();

public:
    explicit Repository(std::string file_name) : file_name(std::move(file_name)) {
        loadFromFile();
    }

    std::vector<Track> getAll() const { return items; }

    void addTrack(const Track &track);

    bool findTrack(int id);

    void setWheelsCount(int id, int new_count);
};
