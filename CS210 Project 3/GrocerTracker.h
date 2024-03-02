#ifndef GROCERTRACKER_H
#define GROCERTRACKER_H

#include <iostream>
#include <fstream>
#include <string>
#include <set>

class GrocerTracker
{
public:

	GrocerTracker(std::string itemName);
	GrocerTracker(std::string itemName, int numberOfItems);

	void addItem();
	void removeItem();
	int getItemQuantity() const;
	std::string getItemName() const;
	bool operator<(const GrocerTracker& other) const;

private:
	std::string itemName = "";
	int itemQuantity = -1;
};

#endif // !GROCERTRACKER_H
