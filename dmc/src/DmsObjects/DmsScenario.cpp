#include "DmsScenario.h"

#include "DmsEncounter.h"
#include <typeinfo>

DmsScenario::DmsScenario() {
}

DmsScenario::DmsScenario(const DmsScenario &scenario)
        : DmsObject(scenario.field_scope.get_enclosing_scope()) {
}

DmsScenario::DmsScenario(DmsFieldScope *enclosing_scope)
        : DmsObject(enclosing_scope) {
}

bool DmsScenario::verify() {
    std::vector<int> int_fields = field_scope.get_all_field_values<int>();
    std::vector<float> float_fields = field_scope.get_all_field_values<float>();
    std::vector<std::string> string_fields = field_scope.get_all_field_values<std::string>();
    std::vector<DmsSerializable*> object_fields = field_scope.get_all_field_values<DmsSerializable*>();

    // Contains any unwanted field
    if (!int_fields.empty() || !float_fields.empty() || !string_fields.empty()) {
        return false;
    }

    for (const auto &field : object_fields) {
        if (typeid(field) != typeid(DmsScenario) || typeid(field) != typeid(DmsEncounter)) {
            return false;
        }
    }

    return true;
}
