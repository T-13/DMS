#include "DmsPlayer.h"

DmsPlayer::DmsPlayer() {
}

DmsPlayer::DmsPlayer(DmsFieldScope *enclosing_scope)
        : DmsObject(enclosing_scope) {
}

bool DmsPlayer::verify() {
    bool found_dmg;
    bool found_hit_chance;
    bool found_hp;
    bool found_speed;

    field_scope.get_field_value<float>("dmg", &found_dmg);
    field_scope.get_field_value<float>("hit_chance", &found_hit_chance);
    field_scope.get_field_value<float>("hp", &found_hp);
    field_scope.get_field_value<float>("speed", &found_speed);

    return found_dmg && found_hit_chance && found_hp && found_speed;
}
