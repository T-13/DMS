#include "DmsGame.h"

DmsGame::DmsGame() {
    constants = new DmsObject();
    players = new DmsObject();
    enemies = new DmsObject();
    encounters = new DmsObject();
    scenarios = new DmsObject();
}

DmsGame::~DmsGame() {
    // TODO Delete recursively
    delete constants;
    delete players;
    delete enemies;
    delete encounters;
    delete scenarios;
}

std::string DmsGame::serialize() {
    return  "\nCONSTANTS: \n" + constants->serialize() + "\n" +
            "PLAYERS: \n" + players->serialize() +
            "ENEMIES: \n" + enemies->serialize() +
            "ENCOUNTERS: \n" + encounters->serialize() +
            "SCENARIOS: \n" + scenarios->serialize();
}
