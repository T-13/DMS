#pragma once

#include "DmsCharacter.h"

class DmsEnemy: public DmsCharacter {
public:
    DmsEnemy();
    DmsEnemy(DmsFieldScope *enclosing_scope);
};

