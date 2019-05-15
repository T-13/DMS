#pragma once

#include "../DmsObject.h"

class DmsEncounter: public DmsObject {
public:
    DmsEncounter();
    DmsEncounter(DmsFieldScope *enclosing_scope);

    bool verify();
};

