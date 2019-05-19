#include "DmsPlayer.h"

DmsPlayer::DmsPlayer() {
}

DmsPlayer::DmsPlayer(const DmsPlayer &player)
        : DmsCharacter(player) {
}

DmsPlayer::DmsPlayer(DmsFieldScope *enclosing_scope)
        : DmsCharacter(enclosing_scope) {
}
