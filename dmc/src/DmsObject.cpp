#include "DmsObject.h"

DmsObject::DmsObject() {
}

DmsObject::DmsObject(DmsFieldScope* enclosing_scope) {
    field_scope.set_enclosing_scope(enclosing_scope);
}

DmsObject::~DmsObject() {
}
