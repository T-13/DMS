#include "DmsDuplicator.h"

DmsDuplicator::DmsDuplicator() {
}

DmsDuplicator::DmsDuplicator(const DmsDuplicator &duplicater)
        : DmsObject(duplicater.field_scope.get_enclosing_scope()) {
}

DmsDuplicator::DmsDuplicator(DmsFieldScope *enclosing_scope)
        : DmsObject(enclosing_scope) {
}
