#include "DmsObject.h"

DmsObject::DmsObject() {
    field_scope.add_parent(this);
}


DmsObject::~DmsObject() {
}
