#include "item.h"
using namespace std;

/*
 * Item constructor
 */
Item::Item(string name, vector<int> pos, int quantity = 0) : name(name), pos(pos), quantity(quantity) {
}

/*
 * Purpose: Getter method for name
 * Returns: name
 */
string Item::getName() {
    return name;
}

/*
 * Purpose: Getter method for position
 * Returns: pos
 */
vector<int> Item::getPosition() {
	return pos;
}

/*
 * Purpose: Getter method for quantity
 * Returns: quantity
 */
int Item::getQuantity() { 
	return quantity;
}

/*
 * Item destructor
 */
Item::~Item(){
}
