#include "Utils.h"

void line(int size, char ch) {
    // Prints a line of specified size with specified character
    cout << setfill(ch) << setw(size) << "" << endl << setfill(' ');
}

void cinERR(const string &message) {
    cerr << message;
    cout << endl;
    cin.clear();
}

void getOption(int &dest, const string &message) {
    // Tries to get a valid int option from cin to use in a switch-case
    string str;

    while (true) {
        try {
            cout << endl << message;
            getline(cin, str);
            cout << endl;
            dest = stoi(str);
            break;
        }
        catch (invalid_argument &e) {
            str = "";
            cinERR("ERROR: Invalid entry, try again");
        }
    }
}