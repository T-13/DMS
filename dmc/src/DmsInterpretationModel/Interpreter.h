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
            m_msg = "UnknownError{\n" + msg + "\n}\n";
        } else if (type == GameOver) {
            m_msg = "Game Over <=> All players are dead! \n";
        }else {
            m_msg = "Error{\n" + msg + "\n}\n";
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
    bool run(DmsGame *game) {
        mt = std::mt19937(rd);
        dist = std::uniform_real_distribution<float>(0.0f, 1.0f);

        try {
            // Set current game
            current_game = game;
            // Start current game
            run(game->starting_scenario);
        } catch (std::exception e) {
            if (typeid(e) != typeid(RuntimeException)) {
                throw new RuntimeException(e.what(), RuntimeException::State::UnknownError);
            } else {
                throw e;
            }
        }
        
    };

    template<class T>
    void run(T *dmsObject);

private:
    DmsGame *current_game;

    std::random_device rd;
    std::mt19937 mt;
    std::uniform_real_distribution<float> dist;

    float get_random_float() {
        return dist(mt);
    }

    int get_random_int(int min, int max) {
        std::uniform_int_distribution uid(min, max);
        return uid(mt);
    }

    void attack(DmsCharacter* attacker, DmsCharacter*defender);
    int getEnemy(std::vector<DmsEnemy*> enemies);
};

template<>
inline void Interpreter::run(DmsScenario *scenario){
    std::cout << "Running scenario: " << scenario->field_scope.get_field<std::string>("name")->get_value() << std::endl;
    auto encounter_cloners = scenario->getEncounters();
    for (int i = 0; i < encounter_cloners.size(); ++i) {
        for (int j = 0; j < encounter_cloners[i]->get_amount(); ++j) {
            DmsEncounter a = *encounter_cloners[i]->get_clone();
        }
    }
}

template<>
inline void Interpreter::run(DmsEncounter *encounter){
    std::cout << "Running encounter: " << encounter->field_scope.get_field<std::string>("name")->get_value() << std::endl;

    auto enemy_cloners = encounter->getSpawners();
    std::vector<DmsEnemy*> enemies;
    std::vector<DmsPlayer*> players;
    std::vector<DmsCharacter*> characters;

    // Spawn correct amount of correct enemy
    for (auto enemy_cloner : enemy_cloners) {
        for (int i = 0; i < enemy_cloner->get_amount(); ++i) {
            DmsEnemy *enemy = enemy_cloner->get_clone();
            enemies.push_back(enemy);
            characters.push_back(enemy);
        }
    }

    // Put players in vector
    for (auto player : current_game->players->field_scope.get_all_fields<DmsSerializable*>()) {
        players.push_back((DmsPlayer*)player.get_value());
        characters.push_back((DmsCharacter*)player.get_value());
    }
    
    // sort DmsCharacters acording to speed using a lambda expression
    std::sort(characters.begin(), characters.end(), [](DmsCharacter* a, DmsCharacter* b) {
        return a->field_scope.get_field<float>("speed") > b->field_scope.get_field<float>("speed");   
    });

    // Run Dmg simulation
    while(!enemies.empty() && !players.empty()) {
        for(auto character : characters){
            // Only if character is alive
            if (character->field_scope.get_field<float>("hp")->get_value() > 0.0f) {
                // Enemy is attacking
                if (typeid(character) == typeid(DmsEnemy*)) {
                    int target = get_random_int(0, players.size()-1);
                    DmsPlayer *defender = players.at(target);
                    attack(character, defender);

                    if (defender->field_scope.get_field<float>("hp")->get_value() <= 0){
                        std::cout << defender->field_scope.get_field<std::string>("name")->get_value() << " has died!" << std::endl;
                        players.erase(players.begin() + target);
                    }

                // Player is attacking
                } else {
                    int target = getEnemy(enemies);
                    DmsEnemy *defender = enemies.at(target);
                    attack(character, defender);

                    if (defender->field_scope.get_field<float>("hp")->get_value() <= 0){
                        std::cout << defender->field_scope.get_field<std::string>("name")->get_value() << " has died!" << std::endl;
                        enemies.erase(enemies.begin() + target);
                    }
                }
            }
        }
    }

    // clear memorry
    for (auto enemy : enemies) {
        delete enemy;
        throw new RuntimeException("DIE!!!!", RuntimeException::State::GameOver);
    }

    if (players.empty()) {
        std::cout << "Game over" << std::endl;
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

int Interpreter::getEnemy(std::vector<DmsEnemy*> enemies) {
    int i = 1;
    std::cout << "Enemies: " << std::endl;
    for(auto enemy : enemies) {
        std::cout << "[" << i++ << "] " << enemy->serialize() << std::endl; 
    }

    int result;
    std::cout << "Choose which enemy to attack: ";
    std::cin >> result;
    
    return result - 1;
}


