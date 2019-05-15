#pragma once

#include "../DmsObject.h"

class DmsPlayer: public DmsObject {
public:
    DmsPlayer(): DmsObject(){};
    DmsPlayer(DmsFieldScope *enclosing_scope): DmsObject(enclosing_scope){};
    bool verify();
};

