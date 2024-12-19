#pragma once

#include <memory>
#include "undo.h"
using namespace std;
#include <stdexcept>
class Service {
    Repository &repo;
    vector<unique_ptr<Undo>> to_undo;
    vector<unique_ptr<Redo>> to_redo;
public:
    Service(Repository &r):repo(r){};
    Service(Service &s)=delete;
    void stergereMultipla(const vector<Student> &stud);
    void updateAll(int i);
    void UndoAct();
    void RedoAct();
    vector<Student> getAll();

};

