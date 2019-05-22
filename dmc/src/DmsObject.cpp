#include "DmsObject.h"

DmsObject::DmsObject() {
}

DmsObject::DmsObject(const DmsObject &object)
        : field_scope(object.field_scope) {
}

DmsObject::DmsObject(DmsFieldScope* enclosing_scope) {
    field_scope.set_enclosing_scope(enclosing_scope);
}

DmsObject::~DmsObject() {
}

std::string DmsObject::serialize(bool split) {
    return field_scope.serialize(split);
}

bool DmsObject::verify() {
    return true;
}
