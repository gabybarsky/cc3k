#include "gold.h"
using namespace std;

/*
 * Gold constructor
 */
Gold::Gold(vector<int> pos, int quantity, bool avail) : Treasure("gold", pos, quantity) {
    available = avail;
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

/*
 * Purpose: Check if gold is available for pickup
 * Returns: true if it is, false otherwise
 */
bool Gold::isAvailable() {
    return available;
}

/*
 * Purpose: Setter method for available
 * Returns: nothing
 */
void Gold::setAvailable(bool avail) {
    available = avail;
}
