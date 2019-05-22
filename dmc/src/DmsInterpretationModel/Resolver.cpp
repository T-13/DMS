#include "Resolver.h"

#include <iostream>
#include <vector>

#include "../DmsSerializable.h"
#include "Interpreter.h"

#include "lib/rang.hpp"

Resolver::Resolver(DmsGame *game_)
        : game(game_) {
}

void Resolver::resolve() {
    for (auto &player : game->players->field_scope.get_all_fields<DmsSerializable*>()) {
        if (!static_cast<DmsEnemy*>(player.get_value())->verify()) {
            std::cout << "-> "
                << rang::fgB::red << "[Invalid]" << rang::fg::reset
                << " Player:" << player.get_name() << std::endl;
            throw ResolveException(player.get_name(), ResolveException::VariableFailedVerification);
        } else {
            std::cout << "-> "
                << rang::fgB::green << "[Valid]" << rang::fg::reset
                << " Player: " << player.get_name() << std::endl;
        }
    }

    for (auto &enemy : game->enemies->field_scope.get_all_fields<DmsSerializable*>()) {
        if (!static_cast<DmsEnemy*>(enemy.get_value())->verify()) {
            std::cout << "-> "
                << rang::fgB::red << "[Invalid]" << rang::fg::reset
                << " Enemy" << enemy.get_name() << std::endl;
            throw ResolveException(enemy.get_name(), ResolveException::VariableFailedVerification);
        } else {
            std::cout << "-> "
                << rang::fgB::green << "[Valid]" << rang::fg::reset
                << " Enemy: " << enemy.get_name() << std::endl;
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

    std::cout << "-> " << rang::fgB::green << "[Valid]" << rang::fg::reset << " Encounters" << std::endl
        << std::endl << rang::style::bold << "Serializing ..." << rang::style::reset;
    game->print(std::cout);
    std::cout << rang::style::bold << "Running ..." << rang::style::reset << std::endl;

    Interpreter interpreter;
    bool exception = false;
    try {
        interpreter.run(game);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exception = true;
    }

    if (!exception) {
        std::cout << rang::style::bold
            << rang::fg::green << "=>" << rang::fg::reset
            << "   Game Finished!   "
            << rang::fg::green << "<=" << rang::fg::reset << std::endl
            << rang::fg::green << "=>" << rang::fg::reset
            << "  Congratulations!  "
            << rang::fg::green << "<=" << rang::fg::reset
            << rang::style::reset << std::endl;
    }


    // TODO - give DmsObject getField, GetFieldValue and GetFieldName that wraps FieldScope and replace long spaghetis with nicer calls to this function
    // Like wtf is this: game->enemies->field_scope.get_field<DmsSerializable*>(. . . ) xD
}
