#pragma once

#include "DmsCharacter.h"

class DmsPlayer: public DmsCharacter {
public:
    DmsPlayer();
    DmsPlayer(const DmsPlayer &player);
    DmsPlayer(DmsFieldScope *enclosing_scope);
};

