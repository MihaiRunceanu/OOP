
#pragma once
#include <vector>
using std::vector;
#include <algorithm>

class Observer{
public:
    virtual void update() = 0;
};

class Observable{
private:
    std::vector<Observer*> observers;
public:
    void notify(){
        for (auto o : observers){
            o->update();
        }
    }

    void addObserver(Observer *obs){
        observers.push_back(obs);
    }

    void delObserver(Observer *obs){
        observers.erase(std::remove(observers.begin(),observers.end(),obs),observers.end());
    }
};
