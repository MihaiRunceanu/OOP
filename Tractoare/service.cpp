#include "service.h"

std::vector<Track> Service::getAll() const {
    std::vector<Track> res(repo.getAll());

    std::sort(res.begin(), res.end(), [](const Track &t1, const Track &t2) {
        return t1.getName() < t2.getName();
    });

    return res;
}

void Service::addTrack(int id, const std::string &name, const std::string &type, int wheels_count) {
    std::string error;

    if (name.empty() || type.empty()) {
        error.append("Camp nume sau camp tip gol\n");
    }
    if (!(2 <= wheels_count && wheels_count <= 16 && wheels_count % 2 == 0)) {
        error.append("Nr de roti trb sa fie par si intre 2 si 16\n");
    }
    if (repo.findTrack(id)) {
        error.append(("Exista deja un tractor cu acest id\n"));
    }

    if (!error.empty()) {
        throw runtime_error(error);
    }

    Track new_track(id, name, type, wheels_count);
    repo.addTrack(new_track);
    notify();
}

std::map<std::string, int> Service::raportType() const {
    std::map<std::string, int> res;

    for (const auto &item : repo.getAll()) {
        res[item.getType()] += 1;
    }

    return res;
}

std::vector<Track> Service::filterType(const std::string &type) const {
    std::vector<Track> res;

    for (const auto &item : repo.getAll()) {
        if (item.getType() == type) {
            res.push_back(item);
        }
    }

    return res;
}

std::set<std::string> Service::getAllTypes() const {
    std::set<std::string> res;

    for (const auto &item : repo.getAll()) {
        res.insert(item.getType());
    }

    return res;
}
