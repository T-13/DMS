#include "DmsEncounter.h"

#include "DmsEnemy.h"
#include "DmsPlayer.h"
#include <typeinfo>

DmsEncounter::DmsEncounter() {
}

DmsEncounter::DmsEncounter(const DmsEncounter &encounter)
        : DmsObject(encounter.field_scope.get_enclosing_scope()) {
}

DmsEncounter::DmsEncounter(DmsFieldScope *enclosing_scope)
        : DmsObject(enclosing_scope) {
}

bool DmsEncounter::verify() {
    auto float_fields = field_scope.get_all_fields<float>();
    auto string_fields = field_scope.get_all_fields<std::string>();
    auto object_fields = field_scope.get_all_fields<DmsSerializable*>();

    // Contains any unwanted field
    if (!float_fields.empty() || !string_fields.empty()) {
        return false;
    }

    for (const auto &field : object_fields) {
        if (typeid(field.get_value()) != typeid(DmsEnemy) /*|| typeid(field) != typeid(DmsPlayer)*/) {
            return false;
        }
    }

    return true;
}
