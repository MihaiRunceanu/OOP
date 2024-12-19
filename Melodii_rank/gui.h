#pragma once

#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>
#include <QPainter>
#include "tablemodel.h"

class MainWindow : public QMainWindow, public Observer {
private:
    Service &service;
    Model *model;

    QTableView *tableView;

    QLineEdit *inputTitle;
    QSlider *sliderRank;

    QPushButton *updateButton;
    QPushButton *deleteButton;
    QVBoxLayout *chartLayout;

    QHBoxLayout *formLayout;

    QWidget *mainWidget;
    QVBoxLayout *mainLayout;

    void initLayout();
    void initSignals();
    void updateChart();

public:
    explicit MainWindow(Service &service, QWidget *parent = nullptr);

    void update() override;

    void paintEvent(QPaintEvent *event) override{
        QPainter painter(this);
        auto const raport = service.raportRanks();
        int x=10;
        for(const auto &md : raport){
            painter.setPen(QPen(Qt::blue, 5));
            //painter.setBrush(QBrush{Qt::blue});
            //QMessageBox::warning(this,"Ceva",QString::number(md));
            int y = height()/2+50;
            x = x + 30;
            painter.drawRect(QRect(x,y,4,md*60));
        }
    }



    ~MainWindow() override;
};
