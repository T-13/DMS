#include "DmsEncounter.h"

#include "DmsEnemy.h"
#include "DmsPlayer.h"
#include <typeinfo>

DmsEncounter::DmsEncounter() {
}

DmsEncounter::DmsEncounter(DmsFieldScope *enclosing_scope)
        : DmsObject(enclosing_scope) {
}

bool DmsEncounter::verify() {
    std::vector<int> int_fields = field_scope.get_all_field_values<int>();
    std::vector<float> float_fields = field_scope.get_all_field_values<float>();
    std::vector<std::string> string_fields = field_scope.get_all_field_values<std::string>();
    std::vector<DmsObject*> object_fields = field_scope.get_all_field_values<DmsObject*>();

    // Contains any unwanted field
    if (!int_fields.empty() || !float_fields.empty() || !string_fields.empty()) {
        return false;
    }

    for (const auto &field : object_fields) {
        if (typeid(field) != typeid(DmsEnemy) || typeid(field) != typeid(DmsPlayer)) {
            return false;
        }
    }

    return true;
}
