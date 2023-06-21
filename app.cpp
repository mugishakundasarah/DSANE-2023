#include <iostream>
#include <vector>
#include <cctype>
#include <sstream>
#include <fstream>
#include <ctime>
#include <regex>

using namespace std;

struct Item {
    int id;
    string name;
    int quantity;
    string registrationDate;
};

vector<Item> items;

// util functions
void log(const string& message) {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char timestamp[80];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localTime);

    ofstream logfile("system.log", ios::app);
    if (logfile.is_open()) {
        logfile << "[" << timestamp << "] " << message << endl;
        logfile.close();
    } else {
        cout << "Unable to open log file." << endl;
    }
}

string getUserInput(string input) {
    cout << "Console > ";
    getline(cin, input);
    return input;
}

string toUpper(string input) {
    for(int i = 0; i < input.length(); i++) {
        input[i] = toupper(input[i]);
    }
    return input;
}

void printOutput(string output){
    cout << "\t" << output << endl;
}

vector<string> split(string str, char delimeter){
    stringstream ss(str);
    string token;
    vector<string> tokens;
    while (getline(ss, token, delimeter))
    {   
        tokens.push_back(token);
    }
    return tokens;
}

void appendItemToList(int id, const string& name, int quantity, const string& registrationDate) {
    bool itemExists = false;
    for (Item& item : items) {
        if (item.id == id && item.registrationDate== registrationDate) {
            item.quantity += quantity;
            itemExists = true;
            break;
        }
    }

    if (!itemExists) {
        Item newItem;
        newItem.id = id;
        newItem.name = name;
        newItem.quantity = quantity;
        newItem.registrationDate = registrationDate;
        items.push_back(newItem);
    }
}

// features
void addItem(int id, string name, int quantity, string registrationDate) {
    // Open the file in append mode
    ofstream outputFile("data.csv", ios::app);

    string newline = to_string(id) + "," + name + "," + to_string(quantity) + "," + registrationDate;
    
    if (outputFile.is_open()) {
        outputFile << newline << endl;
        log("Added " + name + " to stock");
        printOutput("Item added successfully");
    } else {
        printOutput("Unable to open file");
    }
    
    outputFile.close();
}

bool compareItems(const Item& item1, const Item& item2) {
    return item1.name < item2.name;
}

void listItems(){
    ifstream file("data.csv");
    string line;
    vector<string> splitLine;

    if(!file.is_open()){
        printOutput("Unable to open file");
    }

    if (!file.is_open()) {
        cout << "\t Unable to open file" << endl;
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

    sort(items.begin(), items.end(), compareItems);
    for (const Item& item : items) {
        cout << "\t Item ID: " << item.id << "\t Item Name: " << item.name << "\t Quantity: " << item.quantity << "\t Reg Date: " << item.registrationDate << endl;
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
 
    bool itemHasErrors(int id, string name, int quantity, string registrationDate){
        if (id <= 0) {
            printOutput("Invalid item ID: ID must be a positive integer");
            return true;
        }

        if (name.empty()) {
            printOutput("Invalid item name: Name cannot be empty");
            return true;
        }

        if (quantity <= 0) {
            printOutput("Invalid quantity: Quantity must be a positive integer");
            return true;
        }

        regex datePattern(R"(^(19|20)\d{2}-(0[1-9]|1[0-2])-([0-2][1-9]|3[0-1])$)");
        if (!regex_match(registrationDate, datePattern)) {
            printOutput("Invalid registration date format: Please use the format 'year-month-day'");
            return true;
        }

        return false;
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

        // read featureRequest into an object to split it
        stringstream ss(featureRequest);
        while(ss >> featureRequestToken){
            featureRequestArray.push_back(featureRequestToken);
        }

        // get command 
        string command = featureRequestArray[0];

        // convert command to uppercase
        command = toUpper(command);
        if(command == "ITEMADD"){
            if(featureRequestArray.size() != 5){
                printOutput("ERROR: Invalid arguments");
                continue;
            }

            try
            {
                int id = stoi(featureRequestArray[1]);
                string name = featureRequestArray[2];
                int quantity = stoi(featureRequestArray[3]);
                string registrationDate = featureRequestArray[4];
                if(!itemHasErrors(id, name, quantity, registrationDate)){
                    addItem(id, name, quantity, registrationDate);
                }
            }
            catch(const std::exception& e)
            {
                cout << "Invalid arguments " << endl;
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
