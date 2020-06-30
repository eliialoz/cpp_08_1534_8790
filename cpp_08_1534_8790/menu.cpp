/*
File: menu.cpp
Description:
Course: 150018 C++ Workshop, Exercise 6, Question 1
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/
#include<iostream>
#include<iomanip>
#include"menu.h"

using namespace std;

MenuOption operator++(MenuOption& rhs) {
	rhs = MenuOption(int(rhs) + 1);
	return rhs;
}

const char* MenuOptionLine[LAST_MENU_OPTION + 1] {
	"Exit",
	"Add to the beginning of the list",
	"Add to the end of the list",
	"Remove first element from list",
	"Search in the list",
	"Clear the list",
	"Check whether the list is empty",
	"Sort the list",
	"Print the max value in the list",
	"Print as a list ",
	"Print as a Bidirectionallist "
};

istream& operator>>(istream& in, MenuOption& rhs) {
	int value;
	in >> value;
	rhs = MenuOption(value);
	return in;
}

ostream& operator<<(ostream& out, MenuOption rhs) {
	out << setw(4) << int(rhs) << "\t--\t" << MenuOptionLine[rhs];
	return out;
}

MenuOption menu() {
	MenuOption chosen;

	cout << endl << "Menu options:" << endl << endl;

	for (chosen = FIRST_MENU_OPTION; chosen <= LAST_MENU_OPTION; ++chosen)
		cout << chosen << endl;
	cout << endl;

	cout << "Please choose a menu option: ";
	cin >> chosen;
	return chosen;
}