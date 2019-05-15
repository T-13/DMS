#pragma once

#include "../DmsObject.h"

class DmsPlayer: public DmsObject {
public:
    DmsPlayer(DmsFieldScope *enclosing_scope);

    bool verify();
};

