#pragma once

#include "DmsCharacter.h"

class DmsPlayer: public DmsCharacter {
public:
    DmsPlayer();
    DmsPlayer(DmsFieldScope *enclosing_scope);
};

