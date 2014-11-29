#include "treasure.h"
#include "item.h"
#include <string>
using namespace std;

Treasure::Treasure(string name, int quantity) : Item(name, quantity) {
}

Treasure::~Treasure() {
}
