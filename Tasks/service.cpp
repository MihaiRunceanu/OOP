#include "service.h"

vector<Task> Service::getAll() const {
    vector<Task> res(repo.getAll());

    sort(res.begin(), res.end(), [](const Task &t1, const Task &t2) {
        return t1.getStatus() < t2.getStatus();
    });

    return res;
}
void Service::addTask(int id, const string &description, const vector<string> &programmers, string status) {
    if (description.empty() || programmers.empty() || status.empty()) {
        throw runtime_error("Argumentele nu pot fi vide!");
    }
    if (!(status == "open" || status == "inprogress" || status == "closed")) {
        throw runtime_error("Statusul trebuie sa fie open, closed sau inprogress!");
    }
    if (repo.findTask(id)) {
        throw runtime_error("Deja exista un task cu acest id!");
    }

    Task task(id, description, programmers, status);
    repo.addTask(task);
}

vector<Task> Service::searchByProgrammer(const string &name) const {
    if (name.empty()) {
        throw runtime_error("Numele nu poate fi vid!");
    }

    vector<Task> res;

    for (const Task &task : getAll()) {
        for (const string &programmer : task.getProgrammers()) {
            if (programmer.find(name) != string::npos) {
                res.push_back(task);
                break;
            }
        }
    }

    return res;
}

vector<Task> Service::getTasksByStatus(const string &status) const {
    vector<Task> res;

    for (const Task &task : getAll()) {
        if (task.getStatus() == status) {
            res.push_back(task);
        }
    }

    return res;
}

void Service::setTaskStatus(int id, const string &status) {
    repo.setTaskStatus(id, status);
    notify();
}
