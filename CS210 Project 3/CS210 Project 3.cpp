// Developer: Madeline Meyers
// Date: February 25, 2024
// Purpose: To illustrate the frequency of items purchased this program allows the user to search for a specific item and it's frequency or to display all items purchased and represented as either a numeric value or a histogram.

#include <iostream>
#include <fstream>
#include "GrocerTracker.h"


//Handles taking input from a file and returns a set of objects from the input.
//@param fileName - The name of the input file.
//@param grocerItems - An existing set to hold information.
//@returns - A sorted set of objects.
std::set<GrocerTracker> inputItemFrequency(std::string fileName, std::set<GrocerTracker>& inputItems) {
    std::ifstream inStream;
    std::string name;
    inStream.open(fileName);

    if (!inStream.is_open()) {

        std::cerr << "Error opening file\n";
        return inputItems;

    }


    while (inStream >> name) {

        GrocerTracker* grocerPtr = new GrocerTracker(name);
        auto existingItem = inputItems.find(*grocerPtr);

        if (existingItem != inputItems.end()) {

            GrocerTracker* newPtr = new GrocerTracker(existingItem->getItemName(), existingItem->getItemQuantity());
            inputItems.erase(*existingItem);

            newPtr->addItem();
            inputItems.insert(*newPtr);
            delete grocerPtr;
            delete newPtr;

        }
        else {

            inputItems.insert(*grocerPtr);
            delete grocerPtr;
        }
    }



    inStream.close();

    return inputItems;
}


//Outputs the formatted item frequency to a separate file.
//@param fileName - The name of the file for the information.
//@param grocerItems - The set of item frequencies to be output.
void outputItemFrequency(std::string fileName, std::set<GrocerTracker>& outputItems) {
    std::ofstream outStream;
    outStream.open(fileName);

    if (!outStream.is_open()) {

        std::cerr << "Error opening file: " << fileName << std::endl;

    }

    for (GrocerTracker item : outputItems) {

        outStream << item.getItemName() << " " << item.getItemQuantity() << std::endl;

    }

    outStream.close();
}

//Searches a set of objects for a specific item and returns the name and value as a string.
//@param itemName - The name of the object being searched for.
//@param grocerItems - An initialized set of objects to search through.
//@returns - A string containing the name and value of the object if one was found or a message letting the user know the object does not exist in the file.
std::string findItem(std::string& itemName, std::set<GrocerTracker>& searchedItems) {
    std::string found;
    auto searchedArea = searchedItems.find(itemName);

    if (searchedArea != searchedItems.end()) {

        found = (*searchedArea).getItemName() + " " + std::to_string((*searchedArea).getItemQuantity());

    }
    else {

        found = "Not in file";

    }

    return found;
}

//Appends a string of characters n times. Used to display histogram for menu options.
//@param n - The number of times a character should be appended to the output string.
//@param c - The character to append into the output string.
//@returns - A string of characters c of n size.
std::string nCharString(size_t n, char c) {
    std::string charString;
    size_t i;

    for (i = 0; i < n; i++) {

        charString = charString + c;

    }

    return charString;

}

//Validates user input for choice of menu options, user must enter a value between 0 and the maximum value set by the parameter.
//@param maxChoice - The maximum value set for a menu of options.
//@returns - The number entered by the user that is at most the same value as the maximum value.
unsigned int getMenuChoice(unsigned int maxChoice) {

    unsigned int userChoice;
    bool choice = false;

    while (choice == false) {

        std::cin >> userChoice;
       
        if (userChoice >= 0 && userChoice <= maxChoice) {

            choice = true;
            break;

        }

        else {

            break;

        }

    }

    return userChoice;
}

//This function handles outputting the information to the console for the user to see
//@param grocerItems - a set of items to be shown on the console.
//@param option - Option to choose if the output is shown numerically or as a histogram.
void displayItems(std::set<GrocerTracker>& grocerItems, int option) {

    if (option == 1) {

        for (GrocerTracker item : grocerItems) {

            std::cout << item.getItemName() << " " << item.getItemQuantity() << std::endl;

        }

    }
    if (option == 2) {

        for (GrocerTracker item : grocerItems) {

            std::cout << item.getItemName() << " " << nCharString(item.getItemQuantity(), '*') << std::endl;

        }

    }

}






int main()
{
    std::string itemName = "";
    std::string userItemName = "";
    const int MAX = 4;
    int userChoice = 0;
    bool active = true;
    std::cin.exceptions(std::ios::failbit);
    
    //GrocerTracker grocerItem(itemName);
    std::set<GrocerTracker> itemFrequency;

    itemFrequency = inputItemFrequency("inventory.txt", itemFrequency);
    outputItemFrequency("frequency.dat", itemFrequency);



    std::cout << "Welcome To Corner Grocer's inventory system.\n" << std::endl;
    
    while (active == true) {

        std::cout << "Please choose one of the following options\n"
            << "Option 1: The quantity of a specific item displayed numerically\n"
            << "Option 2: The quantity of all items displayed numerically\n"
            << "Option 3: The quantity of all items displayed as a histogram\n"
            << "Option 4: Exit Program" << std::endl;

        try {

            userChoice = getMenuChoice(MAX);

        }

        catch (std::ios_base::failure) {    //If user inputs a non integer value set the choice value to -1, clear the failbit, and place entered data into a string.
            userChoice = -1;
            std::cin.clear();
            std::getline(std::cin, itemName);
            std::cout << "Please enter a valid option (1-4)" << std::endl;
            system("pause");
            system("cls");
        }

            switch (userChoice) {
            case 1: //Output specified item numerically.
                itemFrequency.clear();
                itemFrequency = inputItemFrequency("inventory.txt", itemFrequency); //Set reinitializes prior to output to account for potential changes in the data.
                std::cout << "Enter the name of the item you want to search for:\n";
                std::cin >> userItemName;
                std::cout << findItem(userItemName, itemFrequency) << std::endl;
                system("pause");
                system("cls");
                break;

            case 2: //Output information numerically
                itemFrequency.clear();
                itemFrequency = inputItemFrequency("inventory.txt", itemFrequency);
                displayItems(itemFrequency, 1);
                system("pause");
                system("cls");
                break;

            case 3: //Output information as histogram
                itemFrequency.clear();
                itemFrequency = inputItemFrequency("inventory.txt", itemFrequency);
                displayItems(itemFrequency, 2);
                system("pause");
                system("cls");
                break;

            case 4: //Exit program
                outputItemFrequency("frequency.dat", itemFrequency); //Outputs before closing to account for any changes that may have occured during the use of the program.
                std::cout << "Thank you for using the Corner Grocer's inventory system, goodbye!" << std::endl;
                active = false;
                break;

            default:
                break;

            }
        

    }


    return 0;
}

