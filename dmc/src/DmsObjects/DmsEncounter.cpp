#include "DmsEncounter.h"

#include <typeinfo>

#include "DmsEnemy.h"
#include "DmsPlayer.h"

DmsEncounter::DmsEncounter() {
}

DmsEncounter::DmsEncounter(const DmsEncounter &encounter)
        : DmsObject(encounter) {
    // Delete
    for(auto enemies_cloner : enemies){
        delete enemies_cloner;
    }
    // Clear vecotr
    enemies.clear();
    // Fill with original's cloner's clones
    for(auto enemies_cloner : encounter.enemies) {
        enemies.push_back(new DmsDuplicator<DmsEnemy>(*enemies_cloner));
    }
}

DmsEncounter::DmsEncounter(DmsFieldScope *enclosing_scope)
        : DmsObject(enclosing_scope) {
}

bool DmsEncounter::verify() {
    auto float_fields = field_scope.get_all_fields<float>();
    auto string_fields = field_scope.get_all_fields<std::string>();
    auto object_fields = field_scope.get_all_fields<DmsSerializable*>();

    // Contains any unwanted fields or has no enemies
    if (!object_fields.empty() || !string_fields.empty() || enemies.empty()) {
        return false;
    }

    return true;
}

void DmsEncounter::addSpawner(DmsEnemy *enemy, int amount) {
    enemies.push_back(new DmsDuplicator<DmsEnemy>(enemy, amount));
}

std::string DmsEncounter::serialize() {
    std::string result = "\n";
    auto float_fields = field_scope.get_all_fields<float>();
    for (auto dupe : float_fields) {
        result += dupe.get_name() + " -> amount: " + std::to_string(int(dupe.get_value())) + "\n";
    }
    return result;
}
