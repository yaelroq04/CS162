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
    char filename[STR_SIZE];
    char choice = ' ';
}