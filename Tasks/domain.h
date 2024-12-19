#pragma once

#include <string>
#include <utility>
#include <vector>

using namespace std;

//Clasa pentru obiectul de tip Task
class Task {
private:
    int id;
    string description;
    vector<string> programmers;
    string status;

public:

    // Constructor
    Task(int id, const string description, vector<string> programmers, const string status)
        : id(id), description(description), programmers(programmers), status(status) {}

    // Getter pentru Id
    int getId() const { return id; }

    // Getter pentru Descriere
    string getDescription() const { return description; }

    // Getter pentru Lista de programatori
    vector<string> getProgrammers() const { return programmers; }

    // Getter pentru Status
    string getStatus() const { return status; }

    // Setter pentru Status-ul unui Task
    // stat: Noul status pentru task
    void setStatus(const string &stat) { this->status = stat; }
};
