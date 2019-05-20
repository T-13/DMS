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
    if (field_scope.get_field<float>("hit_chance") != nullptr) {
        if (field_scope.get_field<float>("hit_chance")->get_value() > 1.0) {
            field_scope.set_field_value("hit_chance", 1.0, true);
        } else if (field_scope.get_field<float>("hit_chance")->get_value() < 0.0) {
            field_scope.set_field_value("hit_chance", 0.01, true);
        }
    }

    return field_scope.get_field<float>("dmg") != nullptr
        && field_scope.get_field<float>("hit_chance") != nullptr
        && field_scope.get_field<float>("hp") != nullptr
        && field_scope.get_field<float>("speed") != nullptr
        && field_scope.get_field<std::string>("name") != nullptr;
}
