#include "DmsScenario.h"

#include <string>

#include "DmsEncounter.h"

DmsScenario::DmsScenario() {
}

DmsScenario::DmsScenario(const DmsScenario &scenario)
        : DmsObject(scenario.field_scope.get_enclosing_scope()) {
}

DmsScenario::DmsScenario(DmsFieldScope *enclosing_scope)
        : DmsObject(enclosing_scope) {
}

DmsScenario::~DmsScenario(){
    for (auto cloner : encounters) {
        delete cloner;
    }
}

bool DmsScenario::verify() {
    auto float_fields = field_scope.get_all_fields<float>();
    auto string_fields = field_scope.get_all_fields<std::string>();
    auto object_fields = field_scope.get_all_fields<DmsSerializable*>();

    // Contains any unwanted fields or has no encounters
    if (!float_fields.empty() || !string_fields.empty() || !object_fields.empty() || encounters.empty()) {
        return false;
    }

    return true;
}

void DmsScenario::addEncounter(DmsEncounter *encounter, int amount) {
    encounters.push_back(new DmsDuplicator<DmsEncounter>(encounter, amount));
}

std::string DmsScenario::serialize() {
    std::string result = "\n";
    for (auto dupe : encounters) {
        result += dupe->get_clone()->serialize() + " amount: " + std::to_string(dupe->get_amount()) + "\n";
    }
    return result;
}
