#pragma once

#include "../DmsObject.h"

class DmsEnemy: public DmsObject {
public:
    DmsEnemy();
    DmsEnemy(DmsFieldScope *enclosing_scope);

    bool verify();
};

