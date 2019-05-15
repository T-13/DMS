#include "DmsObject.h"

DmsObject::DmsObject() {
    // field_scope.add_parent(this);
}

DmsObject::DmsObject(DmsFieldScope* enclosing_scope) {
    field_scope.set_enclosing_scope(enclosing_scope);
}


DmsObject::~DmsObject() {
}
