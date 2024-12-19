#pragma once

#include "domain.h"
#include <vector>
#include <algorithm>

// Clasa pentru obiectul de tip Repository
class Repository {
private:
    vector<Task> items;
    string file_name;

    void loadFromFile();
    void writeToFile();
public:

    // Constructor
    explicit Repository(string file_name) : file_name(file_name) {
        loadFromFile();
    }

    // Getter pentru Lista de task-uri
    vector<Task> getAll() { return items; }

    // Functie de adaugare task
    // task: Task-ul care va fi adaugat
    void addTask(const Task &task);

    // Functie de cautare a unui Task dupa Id
    // id: Id-ul task-ului cautat
    // return: True sau False, daca Task-ul exista sau nu in lista
    bool findTask(int id);

    // Setter pentru Status-ul unui Task
    // id: Id-ul task-ului
    // status: Noul status
    void setTaskStatus(int id, const string &status);

    //Functie de sters ultimul element, for testing purposes
    void test_delete(){
        items.pop_back();
        writeToFile();
    }
};
