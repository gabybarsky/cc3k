#ifndef __ITEM_H__
#define __ITEM_H__
#include <string>

class Item {
 protected:
    std::string name;
	Item(std::string name);
	virtual ~Item() = 0;
 public:
    std::string getName();
};
#endif
