/**
  * Names: Jacoby Blanke and Alexei Korolev
  * Program Name: Honour Roll Deluxe
  * Date: 06/16/2021
  * Known Issues:
        + Using arrow keys in the menus will result in an error warning.
  * Changelog:
  *		6/13/21 - Changed File Structure. It is now:
  *			fName
  *			lName
  *			disciplinaryIssue? (Y or N)
  *			numberOfCourses
  *			Course_1
  *			Grade_1
  *			Course_2
  *			Grade_2
  *			...
  * Extra: User can create and manage multiple classes with unique files and students.
  */

#include <string>
#include <iostream>
#include <regex>
#include <conio.h>
/*
GetData.h

Original made by: Ms. DiGiovanna
Edited by: Alexei Korolev and Jacoby Blanke
8.0 Worksheets
5 / 17 / 21
Extras:
Arrays 1 : Prints the minimum and maximum in addition to the average.
Arrays 2 : Displays the number of numbers close to the favorite number aside from the favorite number.
Arrays 3 : Finds the number of comparisons made to find the desired value.
Arrays 4 : If the ticket was not winning, it prints the distance to the nearest ticket.
Arrays 5 : Finds the more efficient sorting algorithm.
Added :
    Printing the number of even numbers in W. 1 Q. 3
    Reprompting numbers outside of the number range in W. 5 Q. 1
    Printing the array before sorting W. 5 Q. 1
*/

#pragma once

bool getValidInt(int&);
bool getValidFloat(float&);
bool getValidDouble(double&); 

class Menu {
public:
    Menu();
    Menu(std::vector<std::string>, std::string);
    std::vector<std::string> options; // All the options
    std::string prompt = "";
    int currentSelected = 0;
    int getSelectedOption(); // Returns the index of the option.
};

