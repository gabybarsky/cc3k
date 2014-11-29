#include "treasure.h"
#include "item.h"
using namespace std;

Treasure::Treasure(string name, vector<int> pos, int quantity) : Item(name, pos, quantity) {
}

Treasure::~Treasure() {
}
