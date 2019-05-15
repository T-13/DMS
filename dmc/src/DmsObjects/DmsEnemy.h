#pragma once

#include "DmsCharacter.h"

class DmsEnemy: public DmsCharacter {
public:
    DmsEnemy();
    DmsEnemy(const DmsEnemy &enemy);
    DmsEnemy(DmsFieldScope *enclosing_scope);
};

