#ifndef __ITEM_H__
#define __ITEM_H__
#include <string>
#include <vector>

class Item {
 protected:
    std::string name;
	std::vector<int> pos;
	int quantity;
	Item(std::string name, std::vector<int> pos, int quantity);
	~Item();
 public:
    std::string getName();
	std::vector<int> getPosition();
	int getQuantity();
};
#endif
