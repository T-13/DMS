#include "DmsCharacter.h"

DmsCharacter::DmsCharacter() {
}

DmsCharacter::DmsCharacter(const DmsCharacter &character)
        : DmsObject(character.field_scope.get_enclosing_scope()) {
}

DmsCharacter::DmsCharacter(DmsFieldScope *enclosing_scope)
        : DmsObject(enclosing_scope) {
}

bool DmsCharacter::verify() {
    return field_scope.get_field<float>("dmg") != nullptr
        && field_scope.get_field<float>("hit_chance") != nullptr
        && field_scope.get_field<float>("hp") != nullptr
        && field_scope.get_field<float>("speed") != nullptr;
}
