#include "decorator.h"
using namespace std;

Decorator::Decorator(Character &c) : c(c){
}

Decorator::~Decorator() {
	delete &c;
}
