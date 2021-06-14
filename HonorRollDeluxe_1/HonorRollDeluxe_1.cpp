/**
  * Names: Jacoby Blanke and Alexei Korolev
  * Program Name: Honour Roll Deluxe
  * Date: 06/11/2021
  * Known Issues: Code is incomplete. All basic requirements are met, but none of the deluxe requirements are yet fulfilled.
  * Changelog:
  *		6/13/21 - Changed File Structure. It is now:
  *			fName
  *			lName
  *			percentAvg
  *			disciplinaryIssue? (Y or N)
  *			numberOfCourses
  *			Course_1
  *			Grade_1
  *			Course_2
  *			Grade_2
  *			...
  *			
  */ 
#include <iostream>
#include "HonorRollClasses.h"
#include <conio.h>
#include <fstream>
#include "GetData.h"

const std::string PASSWORD = "1111";

int main() {

	while (true) {
		EasyFile classList("Classes.txt");
		classList.readFile();
		std::vector<std::string> optionsList = classList.getFileData();
		optionsList.push_back("Add a class");
		Menu m(optionsList, "\t\tWelcome to the Honor Roll Deluxe Version!\n\n Instructions on use : \n\t->Menus: Use 'W' and 'S' to modify your selection and then SPACE or ENTER to confirm.\n\t->Classes: If you create a new class, then the information from the previous classes will be inaccessible when working with that class.\n\t->Naming a class \"CODE:EOF\" will result in a corrupt file.\n\nSelect a class to continue: \n");
		int option = m.getSelectedOption();
		if (option == optionsList.size() - 1) {
			std::cout << "Enter class name: ";
			std::string className;
			getline(std::cin, className);
			std::ofstream newClass;
			newClass.open(className + ".txt");
			newClass << "";
			newClass.close();
			classList.appendString("\n" + className);
			continue;
		}
		EasyFile chosenFile(optionsList[m.getSelectedOption()] + ".txt");
		ClassCollection currentClass(chosenFile);
		if (currentClass.readData()) {
			do {
				optionsList = { "Enter Student Data", "Enter Admin Mode", "Run Reports", "Exit Program" };
				Menu mainMenu(optionsList, "Data successfully read from file. How would you like to proceed?\n");
				option = mainMenu.getSelectedOption();
				if (option == 0) {
					optionsList = { "Yes", "No" };
					Menu yn(optionsList, "Would you like to add a new student? (y to add a new student): \n");
					do {
						std::cout << "\n\t\tSee if you make the Honor Roll!\n\n"; // A little title
						student newStudent; // Creating a new student
						newStudent.promptGrades(); // Getting their grades
						newStudent.update(); // Making sure all values are updated
						currentClass.addStudent(newStudent);
					} while (yn.getSelectedOption() == 0); // Yes / no re-run logic
				}
				else if (option == 1) {
					std::cout << "\n\tPlease enter the password to proceed: ";
					std::string enteredPassword = "";
					getline(std::cin, enteredPassword);
					if (enteredPassword == PASSWORD) {
						// Administrator Mode.
					}
				}
				else if (option == 2) {

				}
				else if (option == 3) {
					exit(0);
				}
			} while (true);
			
		}
		else {
			optionsList.clear();
			optionsList = {"Exit the program", "Return to the Main Menu"};
			Menu errorMenu(optionsList, "How would you like to proceed?\n");
			if (errorMenu.getSelectedOption() == 0) {
				break;
			}
			else {
				continue;
			}

		}
		
	}
	
}
