#include "DmsGame.h"

DmsGame::DmsGame() {
    constants = new DmsObject();
    players = new DmsObject();
    enemies = new DmsObject();
    encounters = new DmsObject();
    scenarios = new DmsObject();
}

DmsGame::~DmsGame() {
    delete constants;
    delete players;
    delete enemies;
    delete encounters;
    delete scenarios;
}

std::string DmsGame::serialize() {
    return  "\nCONSTANTS:\n" + constants->serialize(true) + "\n" +
            "PLAYERS:" + players->serialize(false) + "\n" +
            "\nENEMIES:" + enemies->serialize() + "\n" +
            "\nENCOUNTERS:" + encounters->serialize() + "\n" +
            "\nSCENARIOS:" + scenarios->serialize() + "\n" +
            "\n";
}
