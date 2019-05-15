#pragma once

#include "../DmsObject.h"

class DmsScenario: public DmsObject {
public:
    DmsScenario();
    DmsScenario(const DmsScenario &scenario);
    DmsScenario(DmsFieldScope *enclosing_scope);

    bool verify();
};

