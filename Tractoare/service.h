#pragma once

#include "observer.h"
#include "repository.h"
#include <stdexcept>
#include <map>
#include <set>

class Service : public Subject {
private:
    Repository &repo;

public:
    explicit Service(Repository &repo) : repo(repo) {}

    int getLen() const { return (int) repo.getAll().size(); }

    std::vector<Track> getAll() const;

    void addTrack(int id, const std::string &name, const std::string &type, int wheels_count);

    std::map<std::string, int> raportType() const;

    std::vector<Track> filterType(const std::string &type) const;

    std::set<std::string> getAllTypes() const;

    void setWheelsCount(int id, int new_count) { repo.setWheelsCount(id, new_count); }
};
