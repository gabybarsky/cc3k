#include "gold.h"

Gold::Gold() : Treasure("gold") {
}

Gold::~Gold() {
}

int Gold::getQuantity() {
    return quantity;
}
