/*
File: menu.h
Description:
Course: 150018 C++ Workshop, Exercise 6, Question 1
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/
#ifndef __MENU_H
#define __MENU_H

enum MenuOption {
	EXIT, ADD, ADD_TO_END, REMOVE_FIRST, SEARCH, CLEAR, EMPTY, SORT, MAX, PRINT, PRINT_B,
	FIRST_MENU_OPTION = EXIT, LAST_MENU_OPTION = PRINT_B
};

MenuOption menu();

#endif // __MENU_H