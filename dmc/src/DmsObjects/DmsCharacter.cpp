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
    if (field_scope.get_field<float>("dmg") != nullptr)
        if(field_scope.get_field<float>("hit_chance") != nullptr)
                if(field_scope.get_field<float>("hp") != nullptr)
                        if(field_scope.get_field<float>("speed"))
                                return true;
    return false;
}
