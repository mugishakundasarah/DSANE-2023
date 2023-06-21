#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>

using namespace std;

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

#endif

