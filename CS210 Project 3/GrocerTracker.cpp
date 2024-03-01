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
//@param itemName - A string representing the name of the item to be added to a set.
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

//Handles taking input from a file and returns a set of objects from the input.
//@param fileName - The name of the input file.
//@param grocerItems - An existing set to hold information.
//@returns - A sorted set of objects.
std::set<GrocerTracker> GrocerTracker::inputItemFrequency(std::string fileName, std::set<GrocerTracker>& grocerItems) {
    std::ifstream inStream;
    std::string name;
    inStream.open(fileName);

    if (!inStream.is_open()) {

        std::cerr << "Error opening file\n";
        return grocerItems;

    }


    while (inStream >> name) {

        GrocerTracker* grocerPtr = new GrocerTracker(name);
        auto existingItem = grocerItems.find(*grocerPtr);

        if (existingItem != grocerItems.end()) {

            grocerPtr->itemName = existingItem->itemName;
            grocerPtr->itemQuantity = existingItem->itemQuantity;
            grocerItems.erase(*existingItem);

            grocerPtr->addItem();
        }

        grocerItems.insert(*grocerPtr);
        delete grocerPtr;

    }



    inStream.close();

    return grocerItems;
}


//Outputs the formatted item frequency to a separate file.
//@param fileName - The name of the file for the information.
//@param grocerItems - The set of item frequencies to be output.
void GrocerTracker::outputItemFrequency(std::string fileName, std::set<GrocerTracker>& grocerItems) {
    std::ofstream outStream;
    outStream.open(fileName);

    if (!outStream.is_open()) {

        std::cerr << "Error opening file: " << fileName << std::endl;

    }

    for (GrocerTracker item : grocerItems) {

        outStream << item.getItemName() << " " << item.getItemQuantity() << std::endl;

    }

    outStream.close();
}

//Searches a set of objects for a specific item and returns the name and value as a string.
//@param itemName - The name of the object being searched for.
//@param grocerItems - An initialized set of objects to search through.
//@returns - A string containing the name and value of the object if one was found or a message letting the user know the object does not exist in the file.
std::string GrocerTracker::findItem(std::string& itemName, std::set<GrocerTracker>& grocerItems) {
    std::string found;
    auto searchedArea = grocerItems.find(itemName);

    if (searchedArea != grocerItems.end()) {

        found = (*searchedArea).getItemName() + " " + std::to_string((*searchedArea).itemQuantity);

    }
    else {

        found = "Not in file";

    }

    return found;
}



//Gets the name of the item in current memory.
//@returns The name of the item being checked.
std::string GrocerTracker::getItemName() const {
	return itemName;
}

//Gets the total number of items in current memory.
//@returns The total number of the current item being checked.
int GrocerTracker::getItemQuantity()  {
	return itemQuantity;
}
