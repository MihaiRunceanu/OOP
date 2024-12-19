#pragma once

#include "repository.h"
#include "observer.h"
#include <stdexcept>

// Clasa pentru obiectul de tip Service
class Service : public Subject{
private:
    Repository &repo;

public:

    // Constructor
    explicit Service(Repository &repo) : repo(repo) {};

    // Getter pentru lungimea listei de programatori
    int getLen() const { return repo.getAll().size(); }

    // Getter pentru lista de programatori
    vector<Task> getAll() const;

    // Functie de adaugare Task
    // id: Id-ul taskului
    // description: Descrierea taskului
    // programmers: Lista de programatori
    // status: Status-ul taskului
    // throw: runtime_error, daca id nu este unic sau
    // description este vid sau programmers este vid sau
    // status diferit de "open","inprogress","closed"
    void addTask(int id, const string &description, const vector<string> &programmers, string status);

    // Functie de cautare Task dupa programator
    // name: Numele programatorului
    // return: Lista de task-uri la care participa programatorul cu numele(name)
    // throw: runtime_error daca name este vid
    vector<Task> searchByProgrammer(const string &name) const;

    // Getter pentru lista de Task-uri cu un status
    // status: Status-ul dupa care vor fi cautate Task-urile
    // return: Lista de task-uri cu status-ul dat
    vector<Task> getTasksByStatus(const string &status) const;

    // Setter pentru status-ul unui Task
    // id: Id-ul task-ului
    // status: Noul status
    void setTaskStatus(int id, const string &status);

    //Functie de sters ultimul element, for testing purposes
    void test_delete(){
        repo.test_delete();
    }

};
