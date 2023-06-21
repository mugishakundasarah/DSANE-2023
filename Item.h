#ifndef ITEM_H
#define ITEM_H
#include "Utils.h"

class Item {
private:
    int id;
    string name;
    int quantity;
    string registrationDate;

public:
    Item(){}
    Item(int itemId, const string& itemName, int itemQuantity, const string& regDate) {
        id = itemId;
        name = itemName;
        quantity = itemQuantity;
        registrationDate = regDate;
    }
    
    bool itemHasErrors(){
        if (this->id <= 0) {
            printOutput("Invalid item ID: ID must be a positive integer");
            return true;
        }

        if (this->name.empty()) {
            printOutput("Invalid item name: Name cannot be empty");
            return true;
        }

        if (this->quantity <= 0) {
            printOutput("Invalid quantity: Quantity must be a positive integer");
            return true;
        }

        regex datePattern(R"(^(19|20)\d{2}-(0[1-9]|1[0-2])-([0-2][1-9]|3[0-1])$)");
        if (!regex_match(this->registrationDate, datePattern)) {
            printOutput("Invalid registration date format: Please use the format 'year-month-day'");
            return true;
        }

        return false;
    }

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    int getQuantity() const {
        return quantity;
    }

    string getRegistrationDate() const {
        return registrationDate;
    }

    void setQuantity(int newQuantity) {
        quantity += newQuantity;
    }
    
    void setId(int newId) {
        id = newId;
    }

    void setName(const string& newName) {
        name = newName;
    }

    void setRegistrationDate(const string& newRegistrationDate) {
        registrationDate = newRegistrationDate;
    }


    // features
    void addItem() {
        // Open the file in append mode
        ofstream outputFile("data.csv", ios::app);

        string newline = to_string(this->id) + "," + this->name + "," + to_string(this->quantity) + "," + this->registrationDate;

        if (outputFile.is_open()) {
            outputFile << newline << endl;
            log("Added " + name + " to stock");
            printOutput("Item added successfully");
        } else {
            printOutput("Unable to open file");
        }

        outputFile.close();
    }
};

#endif