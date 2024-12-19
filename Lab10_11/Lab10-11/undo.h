#pragma once
#include "repository.h"

class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo{
private:
    Oferta o;
    RepoAbstract &lista;
public:
    UndoAdauga(const Oferta &o, RepoAbstract &lista);
    void doUndo() override;
};

class UndoSterge : public ActiuneUndo{
private:
    Oferta o;
    RepoAbstract &lista;
public:
    UndoSterge(const Oferta &o, RepoAbstract &lista);
    void doUndo() override;

};

class UndoModifica : public ActiuneUndo{
private:
    Oferta o;
    RepoAbstract &lista;
public:
    UndoModifica(const Oferta &o, RepoAbstract &lista);
    void doUndo() override;
};
