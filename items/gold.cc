#include "gold.h"

Gold::Gold(int quantity) : Treasure("gold", quantity) {
}

Gold::~Gold() {
}

int Gold::getQuantity() {
    return quantity;
}
