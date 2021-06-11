/**
  * Names: Jacoby Blanke and Alexei Korolev
  * Program Name: Honour Roll Deluxe
  * Date: 06/11/2021
  * Known Issues: Code is incomplete. All basic requirements are met, but none of the deluxe requirements are yet fulfilled.
  */ 
#include <iostream>
#include "HonorRollClasses.h"
#include <conio.h>


#include "GetData.h"
int main() {
	std::vector<std::string> o{"Option 1", "Option 2", "Option 3"};

	Menu m(o, "Select an option: \n"); 
	std::cout<< m.getSelectedOption();
	
	student test;
	test.promptGrades();
	ClassCollection cc;
	cc.setPath("SampleClass.txt");
	cc.addStudent(test);
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
