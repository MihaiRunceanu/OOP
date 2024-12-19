#pragma once
#include <QAbstractTableModel>
#include "domain.h"
#include <QColor>
class MyTable :public QAbstractTableModel{
    vector<Student> studenti;
public:
    MyTable(const vector<Student> &st):studenti(st){}
    int rowCount(const QModelIndex& index=QModelIndex()) const override{
        return studenti.size();
    }
    int columnCount(const QModelIndex&index=QModelIndex()) const override{
        return 4;
    }
    QVariant data(const QModelIndex& index,int role) const override{
        if(role==Qt::DisplayRole||role==Qt::BackgroundRole)
        {
            auto student=studenti[index.row()];
            string fac=student.getFacultate();
            QColor color;
            if(fac=="mate")
                color=QColor(Qt::red);
            if(fac=="info")
                color=QColor(Qt::blue);
            if(fac=="mate-info")
                color=QColor(Qt::white);
            if(fac=="ai")
                color=QColor(Qt::green);
            if(index.column()==0)
            {

                if(role==Qt::BackgroundRole)
                    return color;
                return QString::fromStdString(to_string(student.getNr()));

            }
            if(index.column()==1)
            {

                if(role==Qt::BackgroundRole)
                    return color;
                return QString::fromStdString(student.getNume());

            }
            if(index.column()==2)
            {

                if(role==Qt::BackgroundRole)
                    return color;
                return QString::fromStdString(to_string(student.getVarsta()));

            }
            if(index.column()==3)
            {

                if(role==Qt::BackgroundRole)
                    return color;
                return QString::fromStdString(student.getFacultate());

            }
        }
        return QVariant{};
    }
    Student getStudent(QModelIndex & index)
    {
        return studenti[index.row()];
    }
    void setStudenti(const vector<Student> &stud)
    {
        studenti=stud;
        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomRight);//notify ca la observer
        emit layoutChanged();
    }

};
