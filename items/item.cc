#include "item.h"
#include <string>
using namespace std;

Item::Item(string name) : name(name) {
}

string Item::getName() {
    return name;
}
