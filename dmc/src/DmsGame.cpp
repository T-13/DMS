#include "DmsGame.h"

DmsGame::DmsGame() {
    constants = new DmsConstant();
    players = new DmsPlayer();
    enemies = new DmsEnemy();
    encounters = new DmsEncounter();
    scenarios = new DmsScenario();
}


DmsGame::~DmsGame() {
    delete constants;
    delete players;
    delete enemies;
    delete encounters;
    delete scenarios;
}

std::string DmsGame::serialize() {
    return "\nCONSTANTS: \n" + constants->serialize() +
            "\nPLAYERS: \n" + players->serialize() +
            "\nENEMIES: \n" + enemies->serialize() +
            "\nENCOUNTERS: \n" + encounters->serialize() +
            "\nSCENARIOS: \n" + scenarios->serialize();
}
