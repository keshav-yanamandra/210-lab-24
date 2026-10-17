// Keshav Yanamandra
// COMSC-210-5293, Fall 2026
// Lab 24
// started from my Lab 23 code

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <set>

#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string [], string []);
void display_trip(set<Goat> trip);
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

    set<Goat> trip;

    again = true;

    while (again) {
        int choice = main_menu();

        if (choice == 1) {
            add_goat(trip, names, colors);
        }
        else if (choice == 2) {
            delete_goat(trip);
        }
        else if (choice == 3) {
            display_trip(trip);
        }        
        else if (choice == 4) {
            again = false;
        }
    }

    return 0;
}


int main_menu() {
    int choice;

    cout << "*** GOAT MANAGER 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Quit" << endl;
    cout << "Choice --> ";

    while (!(cin >> choice) || choice < 1 || choice > 4) {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid choice. Try again." << endl;
        cout << "Choice --> ";
    }

    return choice;
}

//add_goat had a problem - when I added a lot of goats and when the same goat was added, the message was saying goat added but it was not. 
//so I am fixing by checking if the size of trip increased or not before printing that goat is added
void add_goat(set<Goat> &trip, string names[], string colors[]) {
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];
    int age = rand() % (MAX_AGE + 1);
    int oldSize = trip.size();

    Goat newGoat(name, age, color);
    //trip.push_back(newGoat);
    trip.insert(newGoat);

    cout << endl;
    if (trip.size() > oldSize) {
        cout << "Added: " << name << " (" << age << ", " << color << ")" << endl;
    }
    else {
        cout << "There's already a goat named " << name << " - not added." << endl;
    }

    cout << endl;
}

void display_trip(set<Goat> trip) {
    if (trip.empty()) {
        cout << endl;
        cout << "There are no goats in the trip." << endl;
        cout << endl;
        return;
    }

    cout << endl;
    cout << "Goats:" << endl;

    for (Goat g : trip) {
        cout << "    "
             << g.get_name() << " ("
             << g.get_age() << ", "
             << g.get_color() << ")" << endl;
    }

    cout << endl;
}

int select_goat(set<Goat> trip) {
    int number = 1;
    int choice;

    for (Goat g : trip) {
        cout << "    [" << number << "] "
             << g.get_name() << " ("
             << g.get_age() << ", "
             << g.get_color() << ")" << endl;

        number++;
    }

    cout << "Choice --> ";

    while (!(cin >> choice)) {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid choice. Try again." << endl;
        cout << "Choice --> ";
    }

    return choice;
}

void delete_goat(set<Goat> &trip) {
    if (trip.empty()) {
        cout << "There are no goats to delete." << endl;
        return;
    }

    int choice = select_goat(trip);

    if (choice < 1 || choice > trip.size()) {
        cout << "Invalid goat number." << endl;
        return;
    }

    set<Goat>::iterator it = trip.begin();

    for (int i = 1; i < choice; i++) {
        it++;
    }

    string name = it->get_name();

    trip.erase(it);

    cout << name << " was deleted." << endl;
}
