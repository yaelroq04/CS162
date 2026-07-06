/******************************************************************************
# Author: Yael Roque
# Assignment: Assignment 1 - Structs Review (Bird Watching)
# Date: 22/06/2026
# Description: Function definitions for loading, inserting, adding,
#              printing, and writing bird records.
# Input: A bird data file and keyboard input for new birds.
# Output: Bird listings to the screen and a saved output file.
# Sources: Assignment 1 specifications
#*****************************************************************************/
#include "birdFunctions.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
using namespace std;

//Name: loadBirds()
//Desc: Reads birds from the input file into the array in sorted order
//      by name. Stops at end-of-file or when the array is full.
//input: An empty Bird array and the input file name as a c-string
//output: None
//return: int (number of birds loaded, or ERROR if the file won't open)
int loadBirds(Bird birds[], const char filename[]) {
    ifstream inFile;
    Bird newBird;
    char weightStr[STR_SIZE] = "";
    char sightStr[STR_SIZE] = "";
    char rareStr[STR_SIZE] = "";
    char headerLine[STR_SIZE] = "";
    int count = 0;

    inFile.open(filename);

    if(inFile.is_open()) {
        inFile.getline(headerLine, STR_SIZE);

        while (count < ARR_SIZE && inFile.getline(newBird.name, STR_SIZE, ';')) {
            inFile.getline(newBird.location, STR_SIZE, ';');
            inFile.getline(weightStr, STR_SIZE, ';');
            inFile.getline(sightStr, STR_SIZE, ';');
            inFile.getline(rareStr, STR_SIZE, ';');
            inFile.getline(newBird.description, STR_SIZE);

            newBird.weight = atof(weightStr);
            newBird.sightings = atoi(sightStr);
            newBird.rarity = atoi(rareStr);

            insert(count, newBird, birds);
            count++;
        }
        inFile.close();
    }
    else {
        count = ERROR;
    }

    return count;
}

//Name: insert()
//Desc: Places a new bird into its correct sorted position by shifting
//      the later birds up one slot to make room.
//input: The current bird count, the bird to add, and the Bird array
//output: None
//return: None
void insert(int count, Bird toAdd, Bird birds[]) {
    int i = count;

    if (count < ARR_SIZE) {
        while (i > 0 && strcmp(birds[i - 1].name, toAdd.name) > 0) {
            birds[i] = birds[i - 1];
            i--;
        }
        birds[i] = toAdd;
    }
}

//Name: addBird()
//Desc: Prompts the user for a new bird's information, validates the
//      number fields, then inserts the bird in sorted order.
//input: The Bird array and the current count passed by reference
//output: Prompts and confirmation messages to the screen
//return: None
void addBird(Bird birds[], int& count) {
    Bird newBird;
    char weightStr[STR_SIZE] = "";
    char sightStr[STR_SIZE] = "";
    char rareStr[STR_SIZE] = "";

    // Only prompt for a new bird if there is room in the array.
    if (count < ARR_SIZE) {
        cout << "What is the new bird's name: ";
        cin.getline(newBird.name, STR_SIZE);

        cout << "What is the location of the new bird: ";
        cin.getline(newBird.location, STR_SIZE);

        cout << "How much does the new bird weigh in ounces: ";
        cin.getline(weightStr, STR_SIZE);
        newBird.weight = atof(weightStr);

        while (newBird.weight <= MIN_WEIGHT || newBird.weight > MAX_WEIGHT) {
            cout << "Please enter a weight between " << MIN_WEIGHT
                 << " and " << MAX_WEIGHT << ": ";
            cin.getline(weightStr, STR_SIZE);
            newBird.weight = atof(weightStr);
        }

        cout << "How many sightings are there: ";
        cin.getline(sightStr, STR_SIZE);
        newBird.sightings = atoi(sightStr);

        while (newBird.sightings <= 0 || newBird.sightings > MAX_COUNT) {
            cout << "Please enter a number between 1 and "
                 << MAX_COUNT << ": ";
            cin.getline(sightStr, STR_SIZE);
            newBird.sightings = atoi(sightStr);
        }

        cout << "How rare on a scale of 1 to 10 is the new bird: ";
        cin.getline(rareStr, STR_SIZE);
        newBird.rarity = atoi(rareStr);

        while (newBird.rarity <= 0 || newBird.rarity > 10) {
            cout << "Please enter a number between 1 and 10 inclusive: ";
            cin.getline(rareStr, STR_SIZE);
            newBird.rarity = atoi(rareStr);
        }

        cout << "Please provide a short description of the new bird: ";
        cin.getline(newBird.description, STR_SIZE);

        insert(count, newBird, birds);
        count++;

        cout << endl << "The new bird was successfully added to the list."
             << endl;
    }
    else {
        cout << endl << "The bird list is full. No room to add a new bird."
             << endl;
    }
}

//Name: printBirds()
//Desc: Prints every bird in the array on its own line with a line
//      number and aligned columns.
//input: The Bird array and the current count
//output: A formatted listing of all birds to the screen
//return: None
void printBirds(Bird birds[], int count) {
    int i = 0;

    cout << endl << "The birds in the database are:" << endl;
    cout << left
         << setw(4)  << " "
         << setw(20) << "Name"
         << setw(12) << "Location"
         << setw(6)  << "oz."
         << setw(7)  << "Sights"
         << setw(5)  << "Rare"
         << "Description" << endl;
    cout << setw(4)  << " "
         << setw(20) << "----"
         << setw(12) << "--------"
         << setw(6)  << "---"
         << setw(7)  << "------"
         << setw(5)  << "----"
         << "-----------" << endl;

    cout << fixed << showpoint << setprecision(1);

    for (i = 0; i < count; i++) {
        cout << setw(3) << (i + 1) << ": "
             << setw(20) << birds[i].name
             << setw(12) << birds[i].location
             << setw(6)  << birds[i].weight
             << setw(7)  << birds[i].sightings
             << setw(5)  << birds[i].rarity
             << birds[i].description << endl;
    }
}

//Name: writeBirds()
//Desc: Writes every bird in memory back to an output file, one bird
//      per line, in the same semicolon-separated format as the input.
//input: The Bird array, the current count, and the output file name
//output: A saved data file
//return: None
void writeBirds(Bird birds[], int count, const char filename[]) {
    ofstream outFile;
    int i = 0;

    outFile.open(filename);

    if (outFile.is_open()) {
        for (i = 0; i < count; i++) {
            outFile << birds[i].name << ";"
                    << birds[i].location << ";"
                    << birds[i].weight << ";"
                    << birds[i].sightings << ";"
                    << birds[i].rarity << ";"
                    << birds[i].description << endl;
        }
        outFile.close();
        cout << endl << "The file " << filename
             << " has been written." << endl;
    }
    else {
        cout << endl << "The file " << filename
             << " could not be written." << endl;
    }
}