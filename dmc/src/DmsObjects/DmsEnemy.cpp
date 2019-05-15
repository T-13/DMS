#include "DmsEnemy.h"

DmsEnemy::DmsEnemy() {
}

DmsEnemy::DmsEnemy(const DmsEnemy &enemy)
        : DmsCharacter(enemy.field_scope.get_enclosing_scope()) {
}

DmsEnemy::DmsEnemy(DmsFieldScope *enclosing_scope)
        : DmsCharacter(enclosing_scope) {
}
