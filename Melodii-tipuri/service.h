#pragma once

#include "repository.h"
#include "observer.h"
#include <map>

class Service : public Subject {
private:
    Repository &repo;

    int generateUniqId() const;
public:
    explicit Service(Repository &repo) : repo(repo) {}

    int getLen() const { return repo.getAll().size(); }

    std::vector<Melodie> getAll() const;

    void addSong(const std::string &title, const std::string &artist, const std::string &genre);

    void deleteSong(int id);

    std::map<std::string, int> raportArtist() const;

    std::map<std::string, int> raportGenre() const;
};
