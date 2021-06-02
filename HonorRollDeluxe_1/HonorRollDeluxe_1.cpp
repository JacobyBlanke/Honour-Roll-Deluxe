#include <iostream>
#include "HonorRollClasses.h"
#include <conio.h>

int main() {
  std::string response = "";
  char yn;
  do {
		std::cout << "\n\t\tSee if you make the Honor Roll!\n\n"; // A little title
		student newStudent; // Creating a new student
		newStudent.promptGrades(); // Getting their grades
		newStudent.update(); // Making sure all values are updated
		std::cout << newStudent; // Printing their data
		std::cout << "Would you like to add a new student? (y to add a new student): ";
    getline(std::cin, response);
    yn = tolower(response[0]);

	} while (yn == 'y') ; // Yes / no re-run logic
}