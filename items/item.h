#ifndef __ITEM_H__
#define __ITEM_H__
#include <string>

class Item {
 protected:
    std::string name;
	int quantity;
	Item(std::string name, int quantity);
	~Item();
 public:
    std::string getName();
	int getQuantity();
};
#endif
