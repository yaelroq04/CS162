#ifndef CS_162_ASSIGNMENT_1_BIRDFUNCTIONS_H
#define CS_162_ASSIGNMENT_1_BIRDFUNCTIONS_H
#include <fstream>

//Constants
const int STR_SIZE = 128;
const int ARR_SIZE = 40;
const int MAC_COUNT = 100;
const int ERROR = -1;
const double MIN_WEIGHT = 0.05;
const double MAX_WEIGHT = 1600.0;

//Struct
struct Bird {
    char name[STR_SIZE];
    char location[STR_SIZE];
    double weight;
    int sightings;
    int rarity;
    char description[STR_SIZE];
};

//Prototypes
int loadBirds(Bird birds[], const char filename[]);
void writeBirds(Bird birds[], int count, const char filename[]);
void insert(Bird birds[], Bird toAdd, int count);
void addBird(Bird birds[], int& count);
void printBirds(Bird birds[], int count);

#endif //CS_162_ASSIGNMENT_1_BIRDFUNCTIONS_H