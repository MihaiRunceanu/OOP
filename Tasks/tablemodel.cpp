#include "tablemodel.h"

QVariant Model::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return {};
    }

    const auto &tasks = records;
    const auto &task = tasks[index.row()];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0:return task.getId();
        case 1:return QString::fromStdString(task.getDescription());
        case 2:return (int) task.getProgrammers().size();
        case 3:return QString::fromStdString(task.getStatus());
        case 4:return 5;
        default:return {};
        }
    }

    return {};
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return {};
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:return "ID";
        case 1:return "DESCRIERE";
        case 2:return "NR";
        case 3:return "STATUS";
        default:return {};
        }
    }

    return {};
}

void Model::updateModel() {
    beginResetModel();
    endResetModel();
}

void Model::setRecords(vector<Task> rec) {
    records = rec;
    updateModel();
}

void Model::refreshModel() {
    records = service.getAll();
    updateModel();
}
