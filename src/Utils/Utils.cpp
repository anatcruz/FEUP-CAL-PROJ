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

void getOptionList(vector<int> &dest, const string &message, function<bool(int)> cond) {
    string str;

    while (true) {
        try {
            cout << endl << message;
            getline(cin, str);
//            cout << endl;
            if (!cond(stoi(str))) {
                str = "";
                cinERR("ERROR: Invalid entry, try again");
                continue;
            }
            dest.push_back(stoi(str));
        }
        catch (invalid_argument &e) {
            if (str == "*") {
                return;
            }
            str = "";
            cinERR("ERROR: Invalid entry, try again");
        }
    }
}

void getDouble(double &dest, const string &message) {
    // Tries to get a valid int option from cin to use in a switch-case
    string str;

    while (true) {
        try {
            cout << endl << message;
            getline(cin, str);
            cout << endl;
            dest = stod(str);
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

double angle(pair<double, double> point1, pair<double, double> point2) {
    double x = point2.first - point1.first;
    double y = point2.second - point2.second;
    return atan2(y, x);
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
