#include "repository.h"

#include <algorithm>
#include <sstream>
#include <fstream>

void Repository::loadFromFile() {
    items.clear();

    std::ifstream in(file_name);
    if (!in.is_open()) {
        throw std::runtime_error("Can't open file: " + file_name);
    }

    std::string line;
    while (std::getline(in, line)) {
        std::stringstream line_stream(line);

        std::string current;
        std::vector<std::string> split;

        while (getline(line_stream, current, ',')) {
            split.push_back(current);
        }

        if (split.size() == 4) {
            int id = stoi(split[0]);
            std::string title = split[1];
            std::string artist = split[2];
            std::string genre = split[3];

            addSong({id, title, artist, genre});
        }
    }

    in.close();
}

void Repository::writeToFile() {
    std::ofstream out(file_name);

    for (const Melodie &song : items) {
        out << song.getId() << ","
            << song.getTitle() << ","
            << song.getArtist() << ","
            << song.getGenre() << "\n";
    }

    out.close();
}

void Repository::addSong(const Melodie &song) {
    items.push_back(song);
    writeToFile();
}

void Repository::deleteSong(int id) {
    auto it = std::find_if(items.begin(), items.end(),
                           [id](const Melodie &s) {
                               return s.getId() == id;
                           });

    items.erase(it);
    writeToFile();
}

bool Repository::findSong(int id) {
    auto it = std::find_if(items.begin(), items.end(),
                           [id](const Melodie &s) {
                               return s.getId() == id;
                           });

    return it != items.end();
}
