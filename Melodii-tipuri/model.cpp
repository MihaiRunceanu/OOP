#include "model.h"

QVariant Model::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }

    const auto &songs = service.getAll();
    const auto &song = songs[index.row()];

    switch (index.column()) {
    case 0: return song.getId();
    case 1: return QString::fromStdString(song.getTitle());
    case 2: return QString::fromStdString(song.getArtist());
    case 3: return QString::fromStdString(song.getGenre());
    case 4: return service.raportArtist()[song.getArtist()];
    case 5: return service.raportGenre()[song.getGenre()];

    default: return {};
    }
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return {};
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "ID";
        case 1: return "TITLE";
        case 2: return "ARTIST";
        case 3: return "GENRE";
        case 4: return "SAME ARTIST";
        case 5: return "SAME GENRE";
        default: return {};
        }
    }

    return {};
}

void Model::updateModel() {
    beginResetModel();
    endResetModel();
}
