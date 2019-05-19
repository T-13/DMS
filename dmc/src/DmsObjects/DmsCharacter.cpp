#include "DmsCharacter.h"

DmsCharacter::DmsCharacter() {
}

DmsCharacter::DmsCharacter(const DmsCharacter &character)
        : DmsObject(character) {
}

DmsCharacter::DmsCharacter(DmsFieldScope *enclosing_scope)
        : DmsObject(enclosing_scope) {
}

bool DmsCharacter::verify() {
    return field_scope.get_field<float>("dmg") != nullptr
        && field_scope.get_field<float>("hit_chance") != nullptr
        && field_scope.get_field<float>("hp") != nullptr
        && field_scope.get_field<float>("speed") != nullptr
        && field_scope.get_field<std::string>("name") != nullptr;
}
