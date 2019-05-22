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

void DmsGame::print(std::ostream &os) const {
    os << std::endl << "CONSTANTS:" << std::endl;
    constants->print(os, true);

    os << std::endl << "PLAYERS:";
    players->print(os, false);

    os << std::endl << std::endl << "ENEMIES:";
    enemies->print(os, false);

    os << std::endl << std::endl << "ENCOUNTERS:";
    encounters->print(os, false);

    os << std::endl << std::endl << "SCENARIOS:";
    scenarios->print(os, false);

    os << std::endl << std::endl;
}
