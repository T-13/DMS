#pragma once

#include "../DmsObject.h"

class DmsEnemy: public DmsObject {
public:
    DmsEnemy(DmsFieldScope *enclosing_scope);

    bool verify();
};

