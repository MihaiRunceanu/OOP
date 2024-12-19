#include "undo.h"

UndoAdauga::UndoAdauga(const Oferta &o, RepoAbstract &lista) : o{o}, lista{lista} {}

void UndoAdauga::doUndo() {
    int pos = lista.find(o.get_denumire());
    lista.remove(pos);
}

UndoSterge::UndoSterge(const Oferta &o, RepoAbstract &lista) : o{o}, lista{lista} {}

void UndoSterge::doUndo() {
    lista.store(o);
}

UndoModifica::UndoModifica(const Oferta &o, RepoAbstract &lista) : o{o}, lista{lista} {}

void UndoModifica::doUndo() {
    int pos = lista.find(o.get_denumire());
    lista.update(pos, o.get_destinatie(), o.get_tip(), o.get_pret());
}
