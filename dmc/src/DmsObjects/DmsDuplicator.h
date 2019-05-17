#pragma once

#include "../DmsObject.h"

class DmsDuplicator: public DmsObject {
public:
    DmsDuplicator();
    DmsDuplicator(const DmsDuplicator &duplicater);
    DmsDuplicator(DmsFieldScope *enclosing_scope);
};
