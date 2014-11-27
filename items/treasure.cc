#include "treasure.h"
#include "item.h"
#include <string>
using namespace std;

Treasure::Treasure(string name) : Item(name), quantity(0) {
}
