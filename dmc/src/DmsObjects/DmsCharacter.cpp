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
    bool found_dmg;
    bool found_hit_chance;
    bool found_hp;
    bool found_speed;

    field_scope.get_field_value<float>("dmg", &found_dmg);
    field_scope.get_field_value<float>("hit_chance", &found_hit_chance);
    field_scope.get_field_value<float>("hp", &found_hp);
    field_scope.get_field_value<float>("hp", &found_speed);

    return found_dmg && found_hit_chance && found_hp && found_speed;
}
