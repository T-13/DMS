#include "Resolver.h"

#include <iostream>
#include <vector>

#include "../DmsSerializable.h"
#include "Interpreter.h"

Resolver::Resolver(DmsGame *game_)
        : game(game_) {
}

void Resolver::resolve() {
    std::cout << std::endl << "Resolving ..." << std::endl;

    for (auto &player : game->players->field_scope.get_all_fields<DmsSerializable*>()) {
        if (!static_cast<DmsEnemy*>(player.get_value())->verify()) {
            std::cout << "-> [Invalid] Player:" << player.get_name() << std::endl;
        } else {
            std::cout << "-> [Valid] Player: " << player.get_name() << std::endl;
        }
    }

    for (auto &enemy : game->enemies->field_scope.get_all_fields<DmsSerializable*>()) {
        if (!static_cast<DmsEnemy*>(enemy.get_value())->verify()) {
            std::cout << "-> [Invalid] Enemy" << enemy.get_name() << std::endl;
        } else {
            std::cout << "-> [Valid] Enemy: " << enemy.get_name() << std::endl;
        }
    }

    // Only unresolved object left are encounters
    for (auto &encounter_field : game->encounters->field_scope.get_all_fields<DmsSerializable*>()) {
        // Resolve encounters
        DmsEncounter* encounter = static_cast<DmsEncounter*>(encounter_field.get_value());

        for (auto &enemy_field : encounter->field_scope.get_all_fields<float>()) {
            auto enemy = game->enemies->field_scope.get_field<DmsSerializable*>(enemy_field.get_name());
            if (enemy == nullptr) {
                throw ResolveException(enemy_field.get_name(), ResolveException::VariableUndefined);
            }
            encounter->addSpawner(static_cast<DmsEnemy*>(enemy->get_value()), enemy_field.get_value());
        }
    }

    std::cout << "-> [Valid] Encounters" << std::endl;
    std::cout << std::endl << "Serializing ... " << game->serialize();
    std::cout << "Running ... " << std::endl;

    Interpreter interpreter;
    bool exception = false;
    try {
        interpreter.run(game);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exception = true;
    }

    if (!exception) {
        std::cout << "Game finished! Congratulations" << std::endl;
    }

    // TODO - give DmsObject getField, GetFieldValue and GetFieldName that wraps FieldScope and replace long spaghetis with nicer calls to this function
    // Like wtf is this: game->enemies->field_scope.get_field<DmsSerializable*>(. . . ) xD
}
