#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

// COMSC-210 | Lab 23 | Ian Kusmiantoro

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;
const int ADD = 1, DELETE = 2, LIST = 3, QUIT = 4;

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

    list<Goat> trip; // the actual list
    int choice = -1;
    while (choice != QUIT) { // Loop till the user quits
        choice = main_menu();

        if (choice == ADD) {
            add_goat(trip, names, colors);
        }
        else if (choice == DELETE) {
            delete_goat(trip);
        }
        else if (choice == LIST) {
            display_trip(trip);
        }
        cout << endl; // Just to fix formatting stuff
    }

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

// add_goat() creates a new goat and pushes it to the back of the trip list
// parameters: list<Goat> &trip - list to append to
// returns: void
void add_goat(list<Goat> &trip, string names[], string colors[]) {
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];
    int age = rand() % MAX_AGE;

    trip.push_back(Goat(name, age, color));
}

// select_goat() displays the trip, prompts and validates user for a goat choice
// parameters: list<Goat> trip - list to choose from
// returns: int - index of the chosen goat
int select_goat(list<Goat> trip) {
    if (trip.empty()) { // Guard Clause
        cout << "List is empty" << endl;
        return -1; // -1 is just a dummy number to indicate an error
        // But theoretically it'll never be accessed since the calling function
        // delete_goat() already has its own guard clause
    }

    display_trip(trip); // Reuse display trip for efficiency
    cout << "Choice --> ";

    int choice;
    cin >> choice;

    while (choice < 1 || choice > trip.size()) { // User input is 1-based
        cout << "Invalid choice, try again --> ";
        cin >> choice;
    }

    return choice - 1; // Adjusted to 0 based index to work with lists
}

// delete_goat() removes goat from index inputted by user
// parameters: list<Goat> &trip - list to delete from
// returns: void
void delete_goat(list<Goat> &trip) {
    if (trip.empty()) {
        cout << "List is empty" << endl;
        return;
    }

    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index);
    trip.erase(it);
}

// display_trip() displays the goats on the trip list
// parameters: list<Goat> trip - list to display
// returns: void
void display_trip(list<Goat> trip) {
    if (trip.empty()) {
        cout << "List is empty" << endl;
        return;
    }

    int i = 1; // Starting with 1 for human counting system
    for (Goat goat : trip) {
        cout << "[" << i << "] ";
        cout << goat.get_name();
        cout << " (" << goat.get_age() << ", ";
        cout << goat.get_color() << ")" << endl;
        i++;
    }
}