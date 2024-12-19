#pragma once

#include <vector>
#include <algorithm>

// Clasa pentru obiecte care observa
class Observer {
public:
    virtual void update() = 0;
};

// Clasa pentru obiecte care poate fi observat
class Subject {
private:
    std::vector<Observer *> listeners;
protected:
    // Functie de notificare a observatorilor
    void notify() {
        for (auto l : listeners) {
            l->update();
        }
    }
public:

    // Functie de adaugare observator
    void addListener(Observer *obs) {
        listeners.push_back(obs);
    }

    // Functie de stergere a unui observator
    void deleteListener(Observer *obs) {
        listeners.erase(std::remove(listeners.begin(), listeners.end(), obs), listeners.end());
    }
};
