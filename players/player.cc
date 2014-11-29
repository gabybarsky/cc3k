#include "player.h"
#include <iostream>
#include <string>
using namespace std;

Player::Player(int hp, int atk, int def, int chamber, vector<int>&pos, string race)
                : Character(hp, atk, def, '@', pos),
                  gold(0), chamber(chamber), race(race) {
    floor = 0;
    action = "Player character has spawned.";
}

Player::~Player() {
}

string Player::getRace() {
    return race;
}

int Player::getFloor() {
    return floor;
}

int Player::getChamber() {
    return chamber;
}

void Player::setChamber(int chamber) {
    this->chamber = chamber;
}

string Player::getAction() {
    return action;
}

char Player::getPrevTile() {
    return prevTile;
}

void Player::setPrevTile(char tile) {
    prevTile = tile;
}

void Player::move(string direction) {
    if(direction == "no") {
        position[0]++;
        action = "PC moves North";
    } else if (direction == "so") {
        position[0]--;
        action = "PC moves South";
    } else if (direction == "ea") {
        position[1]++;
        action = "PC moves East";
    } else if (direction == "we") {
        position[1]--;
        action = "PC moves West";
    } else if (direction == "ne") {
        position[0]++;
        position[1]++;
        action = "PC moves NorthEast";
    } else if (direction == "nw") {
        position[0]++;
        position[1]--;
        action = "PC moves NorthWest";
    } else if (direction == "se") {
        position[0]--;
        position[1]++;
        action = "PC moves SouthEast";
    } else if (direction == "sw") {
        position[0]--;
        position[1]--;
        action = "PC moves SouthWest";
    } else {
        cerr<<"Invalid direction"<<endl;
    }
}
