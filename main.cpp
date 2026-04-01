#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

// COMSC-210 | Lab 23 | Ian Kusmiantoro

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();




    return 0;
}

// main_menu() displays the menu, obtains, validates and returns the user's choice
// parameters: none
// returns: int - user's validated choice
int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Quit" << endl;
    cout << "Choice --> ";

    int choice;
    cin >> choice;

    while (choice < 1 || choice > 4) {
        cout << "Invalid choice, try again --> ";
        cin >> choice;
    }

    return choice;
}

void add_goat(list<Goat> &trip, string names[], string colors[]) {
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];
    int age = rand() % MAX_AGE;

    trip.push_back(Goat(name, age, color));
}

int select_goat(list<Goat> trip) {
    int i = 1; // Starting with 1 for human counting system
    for (Goat goat : trip) {
        cout << "[" << i << "] ";
        cout << goat.get_name();
        cout << " (" << goat.get_age() << ", ";
        cout << goat.get_color() << ")" << endl;
        i++;
    }
    cout << "Choice --> ";

    int choice;
    cin >> choice;

    while (choice < 1 || choice > trip.size()) {
        cout << "Invalid choice, try again --> ";
        cin >> choice;
    }

    return choice - 1; // Adjusted to 0 based index to work with lists
}

void delete_goat(list<Goat> &trip) {
    int index = select_goat(trip);
    auto it = trip.begin();
}