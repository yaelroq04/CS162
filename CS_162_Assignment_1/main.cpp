/******************************************************************************
# Author: Yael Roque
# Assignment: Assignment 1 - Structs Review (Bird Watching)
# Date: 22/06/2026
# Description: Loads bird records from a file into an array of structs,
#              lets the user print and add birds through a menu, and
#              writes the data back to a file on exit.
# Input: An input file name and menu choices from the keyboard.
# Output: A welcome message, bird listings, prompts, and an output file.
# Sources: Assignment 1 specifications
#*****************************************************************************/

#include <iostream>
#include <cstring>
#include <cctype>
#include "birdFunctions.h"
using namespace std;

int main() {
    Bird birds[ARR_SIZE];
    int count = 0;
    char filename[STR_SIZE] = "";
    char outFilename[STR_SIZE] = "";
    char choice = ' ';
    ifstream testFile;

    cout << "Time for some bird spotting!" << endl << endl;

    cout << "What is the file name to open? ('exit' if you don't "
         << "have one): ";
    cin.getline(filename, STR_SIZE);
    testFile.open(filename);

    while (!testFile.is_open() && strcmp(filename, "exit") != 0 &&
           strcmp(filename, "quit") != 0) {
        cout << "File " << filename << " did not open. Please try "
             << "again or type 'exit': ";
        cin.getline(filename, STR_SIZE);
        testFile.open(filename);
           }

    if (testFile.is_open()) {
        testFile.close();
        count = loadBirds(birds, filename);
        cout << endl << count << " birds were successfully loaded."
             << endl;
        printBirds(birds, count);

        do {
            cout << endl << "What would you like to do? (P)rint the "
                 << "list, (A)dd, or (Q)uit? ";
            cin >> choice;
            cin.ignore(1000, '\n');
            choice = toupper(choice);

            if (choice == 'P') {
                printBirds(birds, count);
            }
            else if (choice == 'A') {
                addBird(birds, count);
            }
            else if (choice == 'Q') {
                cout << endl << "What file name would you like to use "
                     << "for the output file: ";
                cin.getline(outFilename, STR_SIZE);
                writeBirds(birds, count, outFilename);
            }
            else {
                cout << endl << choice << " is not a valid option. "
                     << "Please try again." << endl;
            }
        } while (choice != 'Q');
    }
    else {
        cout << endl << "Exit was entered, so no birds were loaded."
             << endl;
    }

    cout << endl << "Keep those cameras ready! Until next time." << endl;

    return 0;
}