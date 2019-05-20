#pragma once

#include <exception>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>

#include "../DmsGame.h"
#include "../DmsObjects/DmsDuplicator.h"
#include "../DmsObjects/DmsEncounter.h"
#include "../DmsObjects/DmsEnemy.h"
#include "../DmsObjects/DmsPlayer.h"
#include "../DmsObjects/DmsScenario.h"


class RuntimeException: public std::exception {
public:
    enum State {
        GameOver,
        UnknownError,
    };

    RuntimeException(std::string msg, int type) {
        if (type == UnknownError) {
            m_msg = "UnknownError{\n" + msg + "\n}";
        } else if (type == GameOver) {
            m_msg = "Game Over! All players are dead!";
        } else {
            m_msg = "Error{\n" + msg + "\n}";
        }
    }

    const char* what() const noexcept override {
        return m_msg.c_str();
    }

private:
    std::string m_msg;
};

class Interpreter {
public:
    void run(DmsGame *game) {
        m_generator = std::mt19937(std::random_device()());
        dist = std::uniform_real_distribution<float>(0.0f, 1.0f);

        try {
            // Set current game
            current_game = game;
            // Start current game
            run_scenario(game->starting_scenario);
        } catch (const std::exception &e) {
            if (typeid(e) != typeid(RuntimeException)) {
                throw RuntimeException(e.what(), RuntimeException::State::UnknownError);
            } else {
                throw;
            }
        }
    }

private:
    void run_scenario(DmsScenario *scenario);
    void run_encounter(DmsEncounter *encounter);

    DmsGame *current_game;

    std::mt19937 m_generator;
    std::uniform_real_distribution<float> dist;

    float get_random_float() {
        return dist(m_generator);
    }

    int get_random_int(int min, int max) {
        std::uniform_int_distribution<> uid(min, max);
        return uid(m_generator);
    }

    void attack(DmsCharacter * attacker, DmsCharacter *defender);
    int get_enemy(std::vector<DmsEnemy*> enemies);
};

void Interpreter::run_scenario(DmsScenario *scenario){
    std::cout << "Running scenario: " << scenario->field_scope.get_field<std::string>("name")->get_value() << std::endl;
    auto encounter_cloners = scenario->getEncounters();
    for (auto &encounter_cloner : encounter_cloners) {
        for (int j = 0; j < encounter_cloner->get_amount(); ++j) {
            DmsEncounter *a = encounter_cloner->get_clone();
            run_encounter(a);
        }
    }
}

void Interpreter::run_encounter(DmsEncounter *encounter){
    std::cout << "Running encounter: " << encounter->field_scope.get_field<std::string>("name")->get_value() << std::endl;

    auto enemy_cloners = encounter->getSpawners();
    std::vector<DmsEnemy*> enemies;
    std::vector<DmsPlayer*> players;
    std::vector<DmsCharacter*> characters;

    // Spawn correct amount of correct enemy
    for (auto &enemy_cloner : enemy_cloners) {
        for (int i = 0; i < enemy_cloner->get_amount(); ++i) {
            DmsEnemy *enemy = enemy_cloner->get_clone();
            enemies.push_back(enemy);
            characters.push_back(enemy);
        }
    }

    // Put players in vector
    for (auto &player : current_game->players->field_scope.get_all_fields<DmsSerializable*>()) {
        if (static_cast<DmsPlayer*>(player.get_value())->field_scope.get_field<float>("hp")->get_value() > 0) {
            players.push_back(static_cast<DmsPlayer*>(player.get_value()));
            characters.push_back(static_cast<DmsCharacter*>(player.get_value()));
        }
    }

    // Sort DmsCharacters acording to speed using a lambda expression
    std::sort(characters.begin(), characters.end(), [](DmsCharacter *a, DmsCharacter *b) {
        return a->field_scope.get_field<float>("speed") < b->field_scope.get_field<float>("speed");
    });

    // Run damage simulation
    while (!enemies.empty() && !players.empty()) {
        for (auto &character : characters){
            // std::cout << "Players alive: " << players.size() << std::endl;

            // Only if character is alive
            if (character->field_scope.get_field<float>("hp")->get_value() > 0.0f) {
                if (std::find(players.begin(), players.end(), character) == players.end()) {
                    // Enemy is attacking
                    int target = get_random_int(0, players.size() - 1);
                    DmsPlayer *defender = players.at(target);
                    attack(character, defender);

                    if (defender->field_scope.get_field<float>("hp")->get_value() <= 0){
                        players.erase(players.begin() + target);
                        std::cout << defender->field_scope.get_field<std::string>("name")->get_value() << " has died!" << std::endl;
                    }
                } else {
                    // Player is attacking
                    int target = get_enemy(enemies);
                    DmsEnemy *defender = enemies.at(target);
                    attack(character, defender);

                    if (defender->field_scope.get_field<float>("hp")->get_value() <= 0){
                        std::cout << defender->field_scope.get_field<std::string>("name")->get_value() << " has died!" << std::endl;
                        enemies.erase(enemies.begin() + target);
                    }
                }
            }

            if (enemies.empty() || players.empty()) {
                std::cout << "Encounter finished" << std::endl;
                break;
            }
        }

        // TODO - Give good cout for game states - general cout improvements - more information - etc.
        // TODO improve couts overall !!!
    }
    if (players.empty()) {
        throw RuntimeException("DIE!!!!", RuntimeException::State::GameOver);
    }
}

void Interpreter::attack(DmsCharacter *attacker, DmsCharacter *defender) {
    float hit_roll = get_random_float();
    // Attacker hit defender
    if (hit_roll < attacker->field_scope.get_field<float>("hit_chance")->get_value()) {
        float dmg = attacker->field_scope.get_field<float>("dmg")->get_value();
        auto hp = defender->field_scope.get_field<float>("hp");

        std::cout << attacker->field_scope.get_field<std::string>("name")->get_value() << " has hit " << defender->field_scope.get_field<std::string>("name")->get_value();
        std::cout << " for " << dmg << " damage" << std::endl;
        std::cout << defender->field_scope.get_field<std::string>("name")->get_value() << "'s hp went from " << hp->get_value() << " to ";
        // Set new hp value
        hp->set_value(hp->get_value() - dmg, true);
        std::cout << hp->get_value() << std:: endl;
    } else {
        std::cout << attacker->field_scope.get_field<std::string>("name")->get_value() << " has missed " << defender->field_scope.get_field<std::string>("name")->get_value() << std::endl;
    }
}

int Interpreter::get_enemy(std::vector<DmsEnemy*> enemies) {
    std::cout << "Enemies: " << std::endl;
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        std::cout << "[" << std::distance(enemies.begin(), it) << "] " << (*it)->serialize() << std::endl;
    }

    int result;
    std::cout << "Choose which enemy to attack: ";
    std::cin >> result;

    return result - 1;
}


