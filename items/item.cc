#include "item.h"
#include <string>
using namespace std;

Item::Item(string name, int quantity = 0) : name(name), quantity(quantity) {
}

string Item::getName() {
    return name;
}
