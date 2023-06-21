#include "Item.h"

vector<Item> items;

void appendItemToList(int id, const string& name, int quantity, const string& registrationDate) {
    bool itemExists = false;
    for (Item& item : items) {
        if (item.getId() == id && item.getRegistrationDate() == registrationDate) {
            item.setQuantity(quantity);
            itemExists = true;
            break;
        }
    }

    if (!itemExists) {
        Item newItem(id, name, quantity, registrationDate);
        items.push_back(newItem);
    }
}

bool compareItems(const Item& item1, const Item& item2) {
    return item1.getName() < item2.getName();
}

void listItems(){
    ifstream file("data.csv");
    string line;
    vector<string> splitLine;

    if(!file.is_open()){
        printOutput("Unable to open file");
    }

    if (!file.is_open()) {
        cout << "Unable to open file" << endl;
        return;
    }

    while (getline(file, line)) {
        splitLine = split(line, ',');
        int id = stoi(splitLine[0]);
        string itemName = splitLine[1];
        int quantity = stoi(splitLine[2]);
        string regDate = splitLine[3];

        appendItemToList(id, itemName, quantity, regDate);
    }
    file.close();

    // Sort the items alphabetically by item name
    sort(items.begin(), items.end(), compareItems);

    // Print the sorted items
    for (const Item& item : items) {
        cout << "\t Item ID: " << item.getId() << "\t Item Name: " << item.getName() << "\t Quantity: " << item.getQuantity() << "\t Reg Date: " << item.getRegistrationDate() << endl;
    }
    items.clear();
    log("Listed items in stock");
}

void showHelpMenu(){
    cout << "-----------------------------------------------------------------" << endl;
    cout << "*                  Commands syntaxes                              *" << endl;
    cout << "-----------------------------------------------------------------" << endl; 

    cout << "\t itemadd <item_id> <item_name> <quantity> <registration_date>" << endl;
    cout << "\t itemslist" << endl;
    // cout << "\t help                                                                 :Prints user manual" << endl;
    // cout << "\t Exit                                                                 :Exits the program" << endl;
    cout << endl;
}


void showWelcome(){
    cout << "=========================================================" << endl;
    cout << endl;
    cout << "*      Welcome to Item Recording System!                  *" << endl;
    cout << endl;
    cout << "*  *******************************************  *          " << endl;
    cout << endl;
    cout << "=========================================================" << endl;
    cout<< endl;
    cout << "Need a help? Type 'help' then press Enter key." << endl;
    cout << endl;
}



int main() {
    log("system initialised");
    showWelcome();
    string featureRequest;
    string featureRequestToken;
    vector<string> featureRequestArray; 
    bool exit = false;
    while(!exit){
        featureRequest = getUserInput(featureRequest);
        // split data into an array to handle user input
        featureRequestArray = split(featureRequest, ' ');
        // get command 
        string command = featureRequestArray[0];

        // convert command to uppercase
        command = toUpper(command);
        if(command == "ITEMADD"){
            if(featureRequestArray.size() != 5){
                printOutput("ERROR: Invalid arguments");
                continue;
            }
            try {
                // get all arguments
                int id = stoi(featureRequestArray[1]);
                string name = featureRequestArray[2];
                int quantity = stoi(featureRequestArray[3]);
                string registrationDate = featureRequestArray[4];

                Item item(id, name, quantity, registrationDate);
                if(!item.itemHasErrors()){
                    item.addItem();
                }
            } catch (const exception& e) {
                printOutput("ERROR: Invalid argument format");
            }
        }else if(command == "ITEMSLIST"){
            if(featureRequestArray.size() != 1){
                printOutput("Error: No arguments required");
                continue;
            }
            listItems();
        }
        else if(command == "HELP"){
            if(featureRequestArray.size() != 1){
                printOutput("Help command has no arguments");
                continue;
            }
            showHelpMenu();
        }
        else if(command == "EXIT"){
            if(featureRequestArray.size() != 1){
                printOutput("Exit has no arguments");
                continue;
            }
            exit = true;
            break;
        }
        else{
            printOutput("ERROR: Invalid command");
        }

        // clear the input data
        featureRequest = "";
        featureRequestArray.clear();
    }
    log("System shutdown");
    return 0;
}
