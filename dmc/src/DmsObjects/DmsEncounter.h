#pragma once

#include "../DmsObject.h"

class DmsEncounter: public DmsObject {
public:
    DmsEncounter();
    DmsEncounter(const DmsEncounter &encounter);
    DmsEncounter(DmsFieldScope *enclosing_scope);

    bool verify();
};

