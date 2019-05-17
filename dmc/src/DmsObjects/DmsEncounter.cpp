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

    // Contains any unwanted fields or has no enemies
    if (!object_fields.empty() || !string_fields.empty() || enemies.empty()) {
        return false;
    }

    return true;
}

void DmsEncounter::addSpawner(DmsEnemy *enemy, int amount) {
    enemies.push_back(new DmsDuplicator<DmsEnemy>(enemy, amount));
}

std::string DmsEncounter::serialize(){
    std::string result = "\n";
    for (auto dupe : enemies){
        result += dupe->get_clone()->serialize() + " amount: " + std::to_string(dupe->get_amount()) + "\n";
    }
    return result;
}
