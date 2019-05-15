#include "DmsPlayer.h"

DmsPlayer::DmsPlayer() {
}

DmsPlayer::DmsPlayer(const DmsPlayer &player)
        : DmsCharacter(player.field_scope.get_enclosing_scope()) {
}

DmsPlayer::DmsPlayer(DmsFieldScope *enclosing_scope)
        : DmsCharacter(enclosing_scope) {
}
