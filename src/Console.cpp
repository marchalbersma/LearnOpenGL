#include <Console.h>
#include <iostream>

using namespace std;

const char* Console::getUserChoice(const char* name, const char* options[], const int optionCount)
{
    cout << "Select a " << name << " from the following options:" << endl;

    for (int i = 0; i < optionCount; i++)
    {
        cout << i + 1 << ". " << options[i] << endl;
    }

    int choice;
    bool valid = false;

    while (!valid)
    {
        cout << endl << "Enter the number of your choice:" << endl;
        cin >> choice;

        if (cin.fail())
        {
            cerr << "Error: number is invalid" << endl;
        }
        else if (choice < 1)
        {
            cerr << "Error: number can not be less than 1" << endl;
        }
        else if (choice > optionCount)
        {
            cerr << "Error: number can not be greater than " << optionCount << endl;
        }
        else
        {
            valid = true;
        }

        if (!valid)
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    return options[choice - 1];
}
