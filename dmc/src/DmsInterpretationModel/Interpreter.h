#pragma once

#include <exception>
#include <string>
#include <iostream>
#include <algorithm>

#include "../DmsGame.h"
#include "../DmsObjects/DmsDuplicator.h"
#include "../DmsObjects/DmsEncounter.h"
#include "../DmsObjects/DmsEnemy.h"
#include "../DmsObjects/DmsPlayer.h"
#include "../DmsObjects/DmsScenario.h"


class RuntimeException: public std::exception {
public:
    enum State {
        UnknownError,
    };

    RuntimeException(std::string msg, int type) {
        if (type == UnknownError) {
            m_msg = "UnknownError{\n" + msg + "\n}\n";
        } else {
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
};

template<>
inline void Interpreter::run(DmsScenario *scenario){
    auto encounter_cloners = scenario->getEncounters();
    for (int i = 0; i < encounter_cloners.size(); ++i) {
        for (int j = 0; j < encounter_cloners[i]->get_amount(); ++j) {
            DmsEncounter a = *encounter_cloners[i]->get_clone();
        }
    }
}

template<>
inline void Interpreter::run(DmsEncounter *encounter){
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
        int i = 0;
        int j = 0;

        if (i <)

    }

    // clear memorry
    for (auto enemy : enemies) {
        delete enemy;
    }
}



