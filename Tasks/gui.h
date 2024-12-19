
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QTableView>
#include "secondary_window.h"

// Clasa pentru obiectul de tip GUI
class GUI : public QMainWindow, public Observer {
    Q_OBJECT
private:
    Service &service;
    Model *model;

    QTableView *tableView;

    QFormLayout *layoutForm;

    QLineEdit *inputId;
    QLineEdit *inputDescription;
    QLineEdit *inputProgrammer1;
    QLineEdit *inputProgrammer2;
    QLineEdit *inputProgrammer3;
    QLineEdit *inputProgrammer4;
    QLineEdit *inputStatus;

    QPushButton *btnAdd;
    QPushButton *btnSearch;
    QPushButton *btnRefresh;

    QLineEdit *inputName;

    QWidget *centralWidget;
    QHBoxLayout *mainLayout;

    StatusWindow *openWindow;
    StatusWindow *inProgressWindow;
    StatusWindow *closedWindow;

    // Functie de initializre a layout-ului
    void initLayout();

    // Functie de conectare a butoanelor
    void initSignals();

    // Functie de initializare si afisare a ferestrelor pentru status
    void initStatusWindows();

public:

    // Constructor si initializator
    explicit GUI(Service &service) : service(service) {
        service.addListener(this);
        initLayout();
        initSignals();
        initStatusWindows();
    }

    // Functie de actualizare tabel
    void update() override {
        model->refreshModel();
    }

    // Desctructor
    ~GUI() override {
        service.deleteListener(this);
    }
};
