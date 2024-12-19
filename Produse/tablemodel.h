
#pragma once
#include <QColor>
#include <QAbstractTableModel>
#include "service.h"

class TableModel : public QAbstractTableModel {
private:
    Service &serv;
    vector<Produs> records;
    int maxPrice;

public:
    explicit TableModel(Service &service, QObject *parent) : QAbstractTableModel(parent), serv(service) {
        records = serv.getAll();
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return (int) records.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid()) {
            return {};
        }

        const auto &items = records;
        const auto &item = items[index.row()];
        auto raport=serv.raport_voc();

        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            switch (index.column()) {
            case 0:return item.get_id();
            case 1:return QString::fromStdString(item.get_nume());
            case 2:return QString::fromStdString(item.get_tip());
            case 3:return item.get_pret();
            case 4:return raport[item.get_nume()];
            default:return {};
            }
        } else if (role == Qt::BackgroundRole) {
                 if (item.get_pret() <= maxPrice) {
                    return QColor(Qt::red);
                }
            }
            return {};
        }

        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
            if (role != Qt::DisplayRole) {
                return {};
            }

            if (orientation == Qt::Horizontal) {
                switch (section) {
                case 0:return "ID";
                case 1:return "NUME";
                case 2:return "TIP";
                case 3:return "PRET";
                case 4:return "NR VOCALE";
                default:return {};
                }
            }

            return {};
        }

        void updateModel() {
            beginResetModel();
            endResetModel();
        }

        void setRecords(std::vector<Produs> rec) {
            records = std::move(rec);
            updateModel();
        }

        void refreshModel() {
            records = serv.getAll();
            updateModel();
        }

        void setMaxPrice(int maxp){this->maxPrice = maxp;}
    };
