#include "nodes.h"
#define MAIN_MENU 0
#define GOTO_MENU 1

/* Andy Fleischer - CS202 - Program 3 - 8/6/2021
 * ----------------------------------------------
 * This file tests the sports hierarchy. User is
 * able to make different events, display events,
 * remove events, and more. This file uses the
 * overloaded operators to call proper functions.
*/


using namespace std;

void help(int);
void running(Running&);
void swimming(Swimming&);
void baseball(Baseball&);

int main()
{
    cout << "~~~~~~~~~~~~~~~" << endl;
    cout << "   Olympics!   " << endl;
    cout << "~~~~~~~~~~~~~~~" << endl;
    cout << endl;
    
    Running run_event;
    Swimming swim_event;
    Baseball bb_event;
    BST athletes;

    //main menu loop
    char input;
    do
    {
        help(MAIN_MENU);
        cout << ">> ";
        cin >> input;
        cin.ignore(1000, '\n'); cin.clear();

        Athlete temp;
        char name[50];

        //check which input
        switch (input)
        {
            case '0': break;
            case '1': cin >> temp;
                      athletes += temp;
                      break;
            case '2': cout << "Name: ";
                      cin.get(name, 50);
                      cin.ignore(1000, '\n'); cin.clear();
                      athletes -= name;
                      break;
            case '3': cout << athletes;
                      break;
            case '4': athletes.remove_all();
                      break;
            case '5': running(run_event); break;
            case '6': swimming(swim_event); break;
            case '7': baseball(bb_event); break;
            //case '5': certain_event(athletes); break;
            default: cout << "Invalid command." << endl;
        }
    }
    while (input != '0'); 

    return 0;
}



void help(int menu)
{
    cout << endl;
    switch (menu)
    {
        case MAIN_MENU: cout << "--------MENU--------" << endl;
                        cout << "0 - Quit" << endl;
                        cout << "1 - Add athlete" << endl;
                        cout << "2 - Remove athlete" << endl;
                        cout << "3 - Display" << endl;
                        cout << "4 - Remove all" << endl;
                        cout << "5 - Add running event" << endl;
                        cout << "6 - Add swimming event" << endl;
                        cout << "7 - Add baseball event" << endl;
                        //cout << "5 - Go to an athlete's event" << endl;
                        cout << "--------------------" << endl;
                        break;
        case GOTO_MENU: cout << "--------EVENT-------" << endl;
                        cout << "0 - Back" << endl;
                        cout << "1 - Display" << endl;
                        cout << "2 - Remove from athlete" << endl;
                        cout << "3 - Add skill" << endl;
                        cout << "4 - Remove skill" << endl;
                        cout << "--------------------" << endl;
                        break;
        default: break;
    }
    cout << endl;
}

void running(Running& run_event)
{
    cin >> run_event;
    cout << endl << "Here is your running event:" << endl;
    cout << run_event;
}

void swimming(Swimming& swim_event)
{
    cin >> swim_event;
    cout << endl << "Here is your swimming event:" << endl;
    cout << swim_event << endl;
}

void baseball(Baseball& bb_event)
{
    cin >> bb_event;
    cout << endl << "Here is your baseball event:" << endl;
    cout << bb_event << endl;
}
