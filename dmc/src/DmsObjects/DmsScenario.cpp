#include "DmsScenario.h"

#include <typeinfo>

#include "DmsEncounter.h"

DmsScenario::DmsScenario() {
}

DmsScenario::DmsScenario(const DmsScenario &scenario)
        : DmsObject(scenario.field_scope.get_enclosing_scope()) {
}

DmsScenario::DmsScenario(DmsFieldScope *enclosing_scope)
        : DmsObject(enclosing_scope) {
}

bool DmsScenario::verify() {
    auto float_fields = field_scope.get_all_fields<float>();
    auto string_fields = field_scope.get_all_fields<std::string>();
    auto object_fields = field_scope.get_all_fields<DmsSerializable*>();

    // Contains any unwanted field
    if (!float_fields.empty() || !string_fields.empty()) {
        return false;
    }

    for (const auto &field : object_fields) {
        if (typeid(field.get_value()) != typeid(DmsScenario) || typeid(field) != typeid(DmsEncounter)) {
            return false;
        }
    }

    return true;
}
