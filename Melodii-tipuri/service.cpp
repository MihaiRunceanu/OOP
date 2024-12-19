#include "service.h"
#include <stdexcept>

std::vector<Melodie> Service::getAll() const {
    std::vector<Melodie> res = repo.getAll();

    std::sort(res.begin(), res.end(), [](const Melodie &s1, const Melodie &s2) {
        return s1.getArtist() < s2.getArtist();
    });

    return res;
}

void Service::addSong(const std::string &title, const std::string &artist, const std::string &genre) {
    if (title.empty() || artist.empty() || genre.empty()) {
        throw runtime_error("Camp gol");
    }
    if (!(genre == "pop" || genre == "rock" || genre == "folk" || genre == "disco")) {
        throw runtime_error("Genul trebuie sa fie pop, rock, folk sau disco");
    }

    int id = generateUniqId();
    Melodie song(id, title, artist, genre);
    repo.addSong(song);
    notify();
}

void Service::deleteSong(int id) {
    if (!repo.findSong(id)) {
        throw runtime_error("Melodia nu exista");
    }

    repo.deleteSong(id);
    notify();
}

std::map<std::string, int> Service::raportArtist() const {
    std::map<std::string, int> res;

    for (const Melodie &song : repo.getAll()) {
        res[song.getArtist()] += 1;
    }

    return res;
}

std::map<std::string, int> Service::raportGenre() const {
    std::map<std::string, int> res;

    for (const Melodie &song : repo.getAll()) {
        res[song.getGenre()] += 1;
    }

    return res;
}

int Service::generateUniqId() const {
    int maxId = 0;
    for (const auto &song : repo.getAll()) {
        if (song.getId() > maxId) {
            maxId = song.getId();
        }
    }
    return maxId + 1;
}
