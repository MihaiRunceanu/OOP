#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include "tablemodel.h"
#include "service.h"

// Clasa pentru obiectul de tip StatusWindow
class StatusWindow : public QWidget, public Observer {
    Q_OBJECT
private:
    string name;
    Service &service;
    QVBoxLayout *mainLayout;
    QTableView *tableView;
    Model *model;

    QPushButton *btnOpen;
    QPushButton *btnInProgress;
    QPushButton *btnClosed;

    QHBoxLayout *buttonLayout;

    // Functie de initializare a layout-ului
    void initLayout();

    // Functie de adaugare si conectare butoane
    void addButtons();

public:

    // Constructor
    explicit StatusWindow(const string& name, Service &service, QWidget *parent = nullptr);

    // Functie de actualizare a tabelului
    void update() override {
        model->setRecords(service.getTasksByStatus(name));
    }

    // Desctructor
    ~StatusWindow() override {
        service.deleteListener(this);
    }
};
