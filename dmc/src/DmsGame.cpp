#include "DmsGame.h"

DmsGame::DmsGame() {
    constants = new DmsObject();
    players = new DmsObject();
    enemies = new DmsObject();
    encounters = new DmsObject();
    scenarios = new DmsObject();
}


DmsGame::~DmsGame() {
}

std::string DmsGame::serialize() {
    return "\nCONSTANTS: \n" + constants->serialize() + 
            "\nPLAYERS: \n" + players->serialize() + 
            "\nENEMIES: \n" + enemies->serialize() + 
            "\nENCOUNTERS: \n" + encounters->serialize() + 
            "\nSCENARIOS: \n" + scenarios->serialize();
}
