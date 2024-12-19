#include <QLabel>
#include <QMessageBox>
#include "gui.h"

void GUI::initLayout() {
    centralWidget = new QWidget(this);
    mainLayout = new QHBoxLayout(centralWidget);

    tableView = new QTableView(this);
    model = new Model(service, this);
    tableView->setModel(model);

    layoutForm = new QFormLayout;

    inputId = new QLineEdit(this);
    layoutForm->addRow(new QLabel("Id:"), inputId);

    inputDescription = new QLineEdit(this);
    layoutForm->addRow(new QLabel("Descriere:"), inputDescription);

    inputProgrammer1 = new QLineEdit(this);
    layoutForm->addRow(new QLabel("Programator1:"), inputProgrammer1);

    inputProgrammer2 = new QLineEdit(this);
    layoutForm->addRow(new QLabel("Programator2:"), inputProgrammer2);

    inputProgrammer3 = new QLineEdit(this);
    layoutForm->addRow(new QLabel("Programator3:"), inputProgrammer3);

    inputProgrammer4 = new QLineEdit(this);
    layoutForm->addRow(new QLabel("Programator4:"), inputProgrammer4);

    inputStatus = new QLineEdit(this);
    layoutForm->addRow(new QLabel("Status:"), inputStatus);

    auto *btnLayout = new QVBoxLayout;
    btnAdd = new QPushButton("Add", this);
    btnSearch = new QPushButton("Search", this);
    btnRefresh = new QPushButton("Refresh", this);

    inputName = new QLineEdit(this);
    inputName->setPlaceholderText("Nume:");

    btnLayout->addWidget(btnAdd);
    btnLayout->addWidget(inputName);
    btnLayout->addWidget(btnSearch);
    btnLayout->addWidget(btnRefresh);

    auto *sideLayout = new QHBoxLayout;
    sideLayout->addLayout(layoutForm);
    sideLayout->addLayout(btnLayout);

    mainLayout->addWidget(tableView);
    mainLayout->addLayout(sideLayout);

    setCentralWidget(centralWidget);
}

void GUI::initSignals() {
    connect(btnAdd, &QPushButton::clicked, this, [this]() {
        int id = inputId->text().toInt();
        string description = inputDescription->text().toStdString();
        vector<string> programmers;
        if (!inputProgrammer1->text().isEmpty()) programmers.push_back(inputProgrammer1->text().toStdString());
        if (!inputProgrammer2->text().isEmpty()) programmers.push_back(inputProgrammer2->text().toStdString());
        if (!inputProgrammer3->text().isEmpty()) programmers.push_back(inputProgrammer3->text().toStdString());
        if (!inputProgrammer4->text().isEmpty()) programmers.push_back(inputProgrammer4->text().toStdString());
        string status = inputStatus->text().toStdString();

        try {
            service.addTask(id, description, programmers, status);
            model->refreshModel();
        } catch (const runtime_error &e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    });

    connect(btnSearch, &QPushButton::clicked, this, [this]() {
        try {
            auto records = service.searchByProgrammer(inputName->text().toStdString());
            model->setRecords(records);
        } catch (const runtime_error &e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    });

    connect(btnRefresh, &QPushButton::clicked, this, [this]() {
        model->refreshModel();
    });

}

void GUI::initStatusWindows() {
    openWindow = new StatusWindow("open", service);
    inProgressWindow = new StatusWindow("inprogress", service);
    closedWindow = new StatusWindow("closed", service);

    // openWindow->show();
    // inProgressWindow->show();
    // closedWindow->show();
}
