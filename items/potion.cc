#include "potion.h"
using namespace std;

/*
 * Potion constructor, sets stat and value so that the appropriate
 * PotionDecorator can be created
 */
Potion::Potion(string type, vector<int> pos) : Item(type, pos, 1) {
	switch(type[1]) {
		case 'H':
			stat = "hp";
			if(type[0]=='R')
				value = 10;
			else
				value = -10;
			break;
		case 'A':
			stat = "atk";
			break;
		case 'D':
			stat = "def";
			break;
	}
	//Cases that will only be triggered by atk and def potions
	//Health restore amount for health potions handled in the switch statment
	if(type[0]=='B')
		value = 5;
	else if(type[0]=='W')
		value = -5;
}

/*
 * Purpose: usees the potion on the character c, creating a PotionDecorator
 * with parameter c
 */
void Potion::use(Character &c) {
	PotionDecorator(c, stat, value);
}

/*
 * Potion destructor
 */
Potion::~Potion() {
}
