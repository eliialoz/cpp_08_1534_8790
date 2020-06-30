/*
File: main.cpp
Description:
Course: 150018 C++ Workshop, Exercise 6, Question 1
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/
#include <iostream>
#include "funcs.h"
#include "List.h"
#include "BidirectionalList.h"
#include "menu.h"

using namespace std;

int main() {
	BidirectionalList<int> ls1;
	MenuOption choice;

	while ((choice = menu()) != EXIT) {
		int num;
		switch (choice) {
		case ADD:
			cout << "Enter 5 numbers: ";
			for (int i = 0; i < 5; i++) {
				cin >> num;
				ls1.add(num);
			}
			break;

		case ADD_TO_END:
			cout << "Enter 5 numbers: ";
			for (int i = 0; i < 5; i++) {
				cin >> num;
				ls1.addToEnd(num);
			}
			break;

		case REMOVE_FIRST:
			try
			{
				ls1.removeFirst();
			}
			catch (const char* str)
			{
				cout << str << endl;
			}
			break;
		case SEARCH:
			cout << "Enter a number: ";
			cin >> num;
			cout << "the number is" << ((ls1.search(num)) ? " " : " not ") << "in the list." << endl;
			break;

		case CLEAR:
			ls1.clear();
			break;

		case EMPTY:
			if (ls1.isEmpty())
				cout << "Empty" << endl;
			else
				cout << "Not empty" << endl;
			break;
		case SORT:
			sort<List<int>::Iterator>((ls1.begin()), ls1.end(),
				[](List<int>::Iterator::Reference numA, List<int>::Iterator::Reference numB)
				{
					if (numA > numB)
						return 1;
					if (numA < numB)
						return -1;

					return 0;
				});
			break;

		case MAX:
			cout << "the max value is - " << *(max<List<int>::Iterator>(ls1.begin(), ls1.end())) << endl;
			break;

		case PRINT_END:
			//using BidirectionalIterator(rend & rbegin return BidirectionalIterator)
			for (auto itReverse = ls1.rend(); itReverse != ls1.rbegin();cout << ((--itReverse != ls1.rbegin()) ? " , " : "\n"))
				cout << *itReverse;
			break;
		case PRINT:
			//using ForwardIterator(rend & rbegin return ForwardIterator)
			for (auto itForward = ls1.begin(); itForward != ls1.end(); cout << ((++itForward != ls1.end()) ? " , " : "\n"))
				cout << *itForward;
			break;
		default:
			cout << "ERROR!" << endl;
		
		}
	}
	return 0;
}

