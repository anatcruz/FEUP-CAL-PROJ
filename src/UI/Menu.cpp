#include <iostream>
#include <iomanip>
#include "Menu.h"

using namespace std;


void Menu::addOption(string option, function<void()> func) {
    pair<string, function<void()>> opt;
    opt.first = option;
    opt.second = func;
    options.push_back(opt);
}


void Menu::setName(string name) {
    this->name = name;
}

Menu::Menu(string name, bool persistent) {
    this->name = name;
    this->persistent = persistent;
}

void Menu::setOptions(vector<pair<string, function<void()>>> &options) {
    this->options = options;
}

vector<pair<string, function<void()>>> Menu::getOptions() {
    return options;
}

void Menu::display() {
    line(35);
    cout << left << setw(35) << setfill(' ') << name << endl;
    line(35);
    for (int i = 1; i < options.size(); i++) {
        cout << i << ". " << options.at(i).first << endl;
    }
    // Por convenção, a opção 0 é sempre fechar/voltar
    cout << endl << "0. " << options.at(0).first << endl;
}

void Menu::start() {
    int opt;
    while (true) {
        this->display();
        getOption(opt);
        if (opt > 0 && opt < options.size()) {
            options.at(opt).second();
            if (!persistent) { break; }
        } else if (opt == 0) {
            options.at(opt).second();
            break;
        } else {
            cout << "Invalid option, try again." << endl;
        }
    }
}