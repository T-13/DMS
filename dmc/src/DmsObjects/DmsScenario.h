#pragma once

#include "../DmsObject.h"

class DmsScenario: public DmsObject {
public:
    DmsScenario(DmsFieldScope *enclosing_scope);

    bool verify();
};

