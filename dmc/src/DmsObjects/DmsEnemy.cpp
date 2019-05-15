#include "DmsEnemy.h"

DmsEnemy::DmsEnemy(DmsFieldScope *enclosing_scope)
        : DmsObject(enclosing_scope) {
}

bool DmsEnemy::verify() {
    bool found_dmg;
    bool found_hit_chance;
    bool found_hp;

    field_scope.get_field_value<float>("dmg", &found_dmg);
    field_scope.get_field_value<float>("hit_chance", &found_hit_chance);
    field_scope.get_field_value<float>("hp", &found_hp);

    return found_dmg && found_hit_chance && found_hp;
}
