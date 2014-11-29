#include "item.h"
using namespace std;

Item::Item(string name, vector<int> pos, int quantity = 0) : name(name), pos(pos), quantity(quantity) {
}

string Item::getName() {
    return name;
}

vector<int> Item::getPosition() {
	return pos;
}

int Item::getQuantity() { 
	return quantity;
}

Item::~Item(){
}
