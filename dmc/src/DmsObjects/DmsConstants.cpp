#include "DmsConstants.h"

DmsConstants::DmsConstants() {
}

DmsConstants::DmsConstants(DmsFieldScope *enclosing_scope)
        : DmsObject(enclosing_scope) {
}

bool DmsConstants::verify() {
    return true; // TODO
}
