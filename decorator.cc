#include "decorator.h"
using namespace std;

/*
 * Decorator constructor
 */
Decorator::Decorator(Character &c) : c(c){
}

/*
 * Decorator destructor, takes ownership of the Character
 */
Decorator::~Decorator() {
	delete &c;
}
