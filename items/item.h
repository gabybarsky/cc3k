#ifndef __ITEM_H__
#define __ITEM_H__
#include <string>

class Item {
 protected:
	string name;
	virtual Item() = 0;
	virtual ~Item() = 0;
};
#endif
