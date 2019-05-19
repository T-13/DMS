#include "DmsEnemy.h"

DmsEnemy::DmsEnemy() {
}

DmsEnemy::DmsEnemy(const DmsEnemy &enemy)
        : DmsCharacter(enemy) {
}

DmsEnemy::DmsEnemy(DmsFieldScope *enclosing_scope)
        : DmsCharacter(enclosing_scope) {
}
