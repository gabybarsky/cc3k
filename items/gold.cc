#include "gold.h"
using namespace std;

Gold::Gold(vector<int> pos, int quantity) : Treasure("gold", pos, quantity) {
}

Gold::~Gold() {
}

int Gold::getQuantity() {
    return quantity;
}
