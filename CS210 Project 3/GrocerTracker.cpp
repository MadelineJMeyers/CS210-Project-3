#include "GrocerTracker.h"

//Implementation of GrocerTracker Class members.


//Constructor for the GrocerTracker object witout quantity of items
//@param string x - The name of the item being passed to other methods
GrocerTracker::GrocerTracker(std::string x) {
	itemName = x;
	itemQuantity = 1;
}
//Constructor for the GrocerTracker object with quantity of items
//@param string x - The name of the item being passed to other methods
//@param int y - A method of tracking the number of items
GrocerTracker::GrocerTracker(std::string x, int y) {
	itemName = x;
	itemQuantity = y;
}

//Adds items to a set based on input.
void GrocerTracker::addItem() {
    itemQuantity += 1;
}

//Decreases private variable itemQuantity.
void GrocerTracker::removeItem() {
	itemQuantity -= 1;
}

//Overloaded < operator to sort objects into a set
//@param other - A reference to a separate object in the set to be sorted.
//@returns - The result of comparing two objects which sets their place in the set.
bool GrocerTracker::operator<(const GrocerTracker& other) const {
	return itemName.compare(other.getItemName()) < 0;
}



//Gets the name of the item in current memory.
//@returns The name of the item being checked.
std::string GrocerTracker::getItemName() const {
	return itemName;
}

//Gets the total number of items in current memory.
//@returns The total number of the current item being checked.
int GrocerTracker::getItemQuantity()  const {
	return itemQuantity;
}
