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

double euclidianDistance(pair<double, double> point1, pair<double, double> point2) {
    return sqrt(pow((point1.first - point2.first), 2) + pow((point1.second - point2.second), 2));
}

vector<int> removeIdFromVector(vector<int> v, int id){
    for (auto it=v.begin(); it!=v.end(); it++){
        if( (*it) == id){
            v.erase(it);
        }
    }

    return v;
}

void enterWait(const string &message) {
    string str;
    cout << message << endl;
    getline(cin,str);
}
