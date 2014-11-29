#include "gold.h"
using namespace std;

/*
 * Gold constructor
 */
Gold::Gold(vector<int> pos, int quantity) : Treasure("gold", pos, quantity) {
}

/* 
 * Gold destructor
 */
Gold::~Gold() {
}

/*
 * Purpose: Getter method for quantity
 * Returns: quantity
 */
int Gold::getQuantity() {
    return quantity;
}
