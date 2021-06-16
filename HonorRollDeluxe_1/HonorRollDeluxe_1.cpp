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
#include <iostream>
#include "HonorRollClasses.h"
#include <conio.h>
#include <fstream>
#include "GetData.h"

int main() {

	while (true) {
		EasyFile classList("Classes.txt"); // Opening the classes file
		classList.readFile(); // Reading in its data.
		std::vector<std::string> optionsList = classList.getFileData(); 
		optionsList.push_back("Add a class"); // Adding the "Add a class" option.
		Menu m(optionsList, "\t\tWelcome to the Honor Roll Deluxe Version!\n\n Instructions on use : \n\t->Menus: Use 'W' and 'S' to modify your selection and then SPACE or ENTER to confirm.\n\t->Classes: If you create a new class, then the information from the previous classes will be inaccessible when working with that class.\n\t->Naming a class \"CODE:EOF\" will result in a corrupt file.\n\nSelect a class to continue: \n"); // File selection menu.
		int option = m.getSelectedOption(); // The option that the user selects.
		if (option == optionsList.size() - 1) { // If the "Add a class" option is selected.
			std::cout << "Enter class name: ";
			std::string className;
			getline(std::cin, className);
			std::ofstream newClass;
			newClass.open(className + ".txt"); // Adding the file.
			newClass << "";
			newClass.close();
			classList.appendString("\n" + className); // Adding the file name to the Classes.txt list.
			continue; // Reloading.
		}
		EasyFile chosenFile(optionsList[option] + ".txt"); // Creating the EasyFile.
		ClassCollection currentClass(chosenFile); // Creating the class from the file.
		optionsList = { "Yes", "No" };
		Menu yn(optionsList, "Would you like to add a new student?: \n"); // A menu for yn applications.
		if (currentClass.readData()) {
			do {
				optionsList = { "Enter Student Data", "Enter Admin Mode", "Run Reports", "Exit Program" };
				Menu mainMenu(optionsList, "Data successfully read from file. How would you like to proceed?\n");
				option = mainMenu.getSelectedOption();
				if (option == 0) {
					
					do {
						std::cout << "\n\t\tSee if you make the Honor Roll!\n\n"; // A little title
						student newStudent; // Creating a new student
						newStudent.promptGrades(); // Getting their grades
						newStudent.update(); // Making sure all values are updated
						currentClass.addStudent(newStudent); // Adding the student to the class.
					} while (yn.getSelectedOption() == 0); // Yes / no re-run logic
				}
				else if (option == 1) {
					currentClass.administrator();
					currentClass.syncFile(); // Saving all changes done in admin mode.
				}
				else if (option == 2) {
					do {
						yn.prompt = "Continue Running Reports? \n"; // Changing the prompt to fit the scenario.
						m.options = { "A. Run Full Honor Roll Report", "B. Honor Roll Report for 1 Student", "C. Full GPA Report", "D. GPA Report for 1 Student.", "E. Disciplinary Infractions Report" };
						m.prompt = "Select your desired report: \n";
						option = m.getSelectedOption();
						if (option == 0) { // Complete full report.
							currentClass.fullReport(); // Run the full report if the option is chosen.
						}
						
						else if (option == 1) { // Student full report.
							do {
								std::cout << "\n\tPlease enter the lastname of the student: ";
								std::string name = "";
								getline(std::cin, name);
								if (!currentClass.fullStudentReport(name)) { // If the name was not found..
									m.options = { "Back to Reports Menu", "Try again", "Quit" };
									m.prompt = "Student not found. How would you like to proceed?\n";
								}
								else { // If the name was found..
									m.options = { "Back to Reports Menu", "Enter another student", "Quit" };
									m.prompt = "How would you like to proceed?\n";
								}
								std::cout << "\033[2J\033[1;1H";
								option = m.getSelectedOption();
								if (option == 0) { // Logic for the three options.
									break;
								}
								else if (option == 1) {
									continue;
								}
								else {
									exit(0);
								}
							} while (true);
							
						}
						else if (option == 2) {
							currentClass.gpaReport(); // Run the GPA report.
						}
						else if (option == 3) { // Student GPA report.
							do {
								std::cout << "\n\tPlease enter the lastname of the student: ";
								std::string name = "";
								getline(std::cin, name);
								if (!currentClass.fullStudentReport(name)) {
									m.options = { "Back to Reports Menu", "Try again", "Quit" };
									m.prompt = "Student not found. How would you like to proceed?\n";
								}
								else {
									m.options = { "Back to Reports Menu", "Enter another student", "Quit" };
									m.prompt = "How would you like to proceed?\n";
								}
								std::cout << "\033[2J\033[1;1H";
								option = m.getSelectedOption();
								if (option == 0) { // Logic for the three options.
									break;
								}
								else if (option == 1) {
									continue;
								}
								else {
									exit(0);
								}
							} while (true);
						}
						else if (option == 4) { // Disciplinary Report.
							currentClass.disciplinaryReport();
						}
						std::cout << "\033[2J\033[1;1H";
					} while (yn.getSelectedOption() == 0);
				}
				else if (option == 3) {
					exit(0);
				}
			} while (true);
			
		}
		else {
			Menu errorMenu(std::vector<std::string>{"Exit the program", "Return to the Main Menu"}, "How would you like to proceed?\n");
			if (errorMenu.getSelectedOption() == 0) {
				break;
			}
			else {
				continue;
			}

		}
		
	}
	
}
