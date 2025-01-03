#pragma once

#include "service.h"
#include "model.h"

#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QPainter>

class MainWindow : public QMainWindow, public Observer {
    Q_OBJECT
private:
    Service &service;
    Model *model;

    QTableView *tableView;

    QLineEdit *inputTitle;
    QLineEdit *inputArtist;
    QLineEdit *inputGenre;

    QPushButton *btnAdd;
    QPushButton *btnDelete;

    QHBoxLayout *formLayout;
    QVBoxLayout *mainLayout;
    QWidget *mainWidget;

    void setupLayout();
    void setupSignals();
public:
    explicit MainWindow(Service &service, QWidget *parent = nullptr)
        : QMainWindow(parent), service(service) {
        setupLayout();
        setupSignals();
    }

    void update() override {
        model->updateModel();
        QWidget::update();
    }

protected:
    void paintEvent(QPaintEvent *event) override;
};
