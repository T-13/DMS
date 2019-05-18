#pragma once

#include "../DmsObject.h"

#include "DmsEnemy.h"
#include "DmsDuplicator.h"

class DmsEncounter: public DmsObject {
public:
    DmsEncounter();
    DmsEncounter(const DmsEncounter &encounter);
    DmsEncounter(DmsFieldScope *enclosing_scope);

    bool verify();
    void addSpawner(DmsEnemy *enemy, int amount);
    std::vector<DmsDuplicator<DmsEnemy>*> getSpawners() { return enemies; }
    std::string serialize();

private:
    std::vector<DmsDuplicator<DmsEnemy>*> enemies;
};

