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
	int getItemQuantity();
	std::string getItemName() const;
	std::string findItem(std::string& itemName, std::set<GrocerTracker>& grocerItems);
	void outputItemFrequency(std::string fileName, std::set<GrocerTracker>& grocerItems);
	std::set<GrocerTracker>inputItemFrequency(std::string fileName, std::set<GrocerTracker>& grocerItems);
	bool operator<(const GrocerTracker& other) const;

private:
	std::string itemName = "";
	int itemQuantity = -1;
};

#endif // !GROCERTRACKER_H
