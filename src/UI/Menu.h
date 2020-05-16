#ifndef PROJ_MENU_H
#define PROJ_MENU_H

#include <string>
#include <vector>
#include <functional>
#include "../Utils/Utils.h"

using namespace std;

class Menu {
private:
    /**Name displayed at the top of the Menu.
*/
    string name;

    /** Structure that holds Menu options, the first is the option text and the second is the function it will execute.
     */
    vector<pair<string, function<void()>>> options;
public:
    /**Constructor for Menu with name.
     */
    Menu(string name);

    /**Initializes Menu, calls the display function and gets the user options.
     */
    void start();

    /**Prints Menu name and options.
     */
    void display();

    /**
     * @return the options vector.
*/
    vector<pair<string, function<void()>>> getOptions();

    /** Sets the name of the Menu.
*/
    void setName(string name);

    /** Sets the options vector of the Menu.
*/
    void setOptions(vector<pair<string, function<void()>>> &options);

    /** Creates a new menu option, adding a pair to the options vector.
     */
    void addOption(string option, function<void()> func);
};

#endif //PROJ_MENU_H
