#pragma once

#include "../DmsObject.h"

#include <vector>
#include <string>

#include "DmsEncounter.h"
#include "DmsDuplicator.h"

class DmsScenario: public DmsObject {
public:
    DmsScenario();
    DmsScenario(const DmsScenario &scenario);
    DmsScenario(DmsFieldScope *enclosing_scope);
    ~DmsScenario();

    bool verify();
    void addEncounter(DmsEncounter *encounter, int amount);
    std::vector<DmsDuplicator<DmsEncounter>*> getEncounters() { return encounters; }
    std::string serialize();

private:
    std::vector<DmsDuplicator<DmsEncounter>*> encounters;
};

