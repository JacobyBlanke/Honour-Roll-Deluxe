/**
  * Names: Jacoby Blanke and Alexei Korolev
  * Program Name: Honour Roll Deluxe
  * Date: 06/11/2021
  * Known Issues: Code is incomplete. All basic requirements are met, but none of the deluxe requirements are yet fulfilled.
  */ 


#include "GetData.h"


using std::cin;
using std::cout;

bool getValidInt(int& t_int) {
	std::string intScratch = "";
	bool isValid = true;

	getline(cin, intScratch);
	//remove all whitespace
	std::regex r("\\s+");
	intScratch = std::regex_replace(intScratch, r, "");
	//rev 2 make sure only valid characters for an integer number are in the string
	isValid = intScratch.find_first_not_of("-0123456789") == std::string::npos;
	//Only 1 '-' allowed
	if (std::count(intScratch.begin(), intScratch.end(), '-' )> 1) {
		isValid = false;
	}
	//make sure '-' is first char only
	else if (std::count(intScratch.begin(), intScratch.end(), '-') > 0) {
		if (intScratch.at(0) != '-') {
			isValid = false;
		}
	}
	//convert ONLY if string is contains valid integer characters
	//all errors caught 
	if (isValid) {
		try {
			t_int = stoi(intScratch);
		}
		catch (...) { //<---catches ALL errors - may want to give the user a more specific message.  Shown in next function
			//bad user entry - don't care what it is, return invalid
			isValid = false;
		}
	}
	return isValid;
}

//No exponant notation... yet
bool getValidFloat(float& t_float) {
	std::string floatScratch = "";
	bool isValid = true;

	getline(cin, floatScratch);
	//remove all whitespace
	std::regex r("\\s+");
	floatScratch = std::regex_replace(floatScratch, r, "");
	//rev 2 make sure only valid characters for an integer number are in the string
	isValid = floatScratch.find_first_not_of("-.0123456789") == std::string::npos;
	//Only 1 '-' allowed
	if (std::count(floatScratch.begin(), floatScratch.end(), '-') > 1) {
		isValid = false;
	}
	//make sure '-' is first char only
	else if (std::count(floatScratch.begin(), floatScratch.end(), '-') > 0) {
		if (floatScratch.at(0) != '-') {
			isValid = false;
		}
	}
	//Only 1 '.' allowed
	if (std::count(floatScratch.begin(), floatScratch.end(), '.') > 1) {
		isValid = false;
	}
	// convert ONLY if string is contains valid integer characters
	//all errors caught 
	if (isValid) {
		try {
			t_float = stof(floatScratch);
		}
		catch (const std::invalid_argument) {
			cout << "You did not enter a valid  floating point number: " << std::endl;
			isValid = false;
		}

		catch (const std::out_of_range) {
			cout << "That number is too large: " << std::endl;
			isValid = false;
		}

		catch (const std::exception& e)
		{
			cout << "Undefined error. Please renter your data: " << e.what() << std::endl;
			isValid = false;
		}
	}
	return isValid;
}
bool getValidDouble(double& t_double) {
	std::string doubleScratch = "";
	bool isValid = true;

	getline(cin, doubleScratch);
	//remove all whitespace
	std::regex r("\\s+");
	doubleScratch = std::regex_replace(doubleScratch, r, "");
	//rev 2 make sure only valid characters for an integer number are in the string
	isValid = doubleScratch.find_first_not_of("-.0123456789") == std::string::npos;
	//Only 1 '-' allowed
	if (std::count(doubleScratch.begin(), doubleScratch.end(), '-') > 1) {
		isValid = false;
	}
	//make sure '-' is first char only
	else if (std::count(doubleScratch.begin(), doubleScratch.end(), '-') > 0) {
		if (doubleScratch.at(0) != '-') {
			isValid = false;
		}
	}
	//Only 1 '.' allowed
	if (std::count(doubleScratch.begin(), doubleScratch.end(), '.') > 1) {
		isValid = false;
	}
	// convert ONLY if string is contains valid integer characters
	//all errors caught 
	if (isValid) {
		try {
			t_double = stod(doubleScratch);
		}
		catch (...) {
			//bad user entry - don't care what it is, return invalid
			isValid = false;
		}
	}
	return isValid;
}


Menu::Menu() {
	// Do nothing
}

Menu::Menu(std::vector<std::string> givenOptions, std::string givenPrompt) {
	options = givenOptions;
	prompt = givenPrompt;
}

int Menu::getSelectedOption() {
	char enteredChar = 'a';
	do {
		std::string printData = "";
		printData += prompt;
		for (int i = 0; i < options.size(); i++) {
			if (i == currentSelected) {
				printData += " > " + options[i] + " < \n";
			}
			else {
				printData += "    " + options[i] + "   \n";
			}
		}
		std::cout << printData;
		enteredChar = (_getch());
		if (std::tolower(enteredChar) == 'w') {
			currentSelected = std::max(0, --currentSelected);
		}
		else if (std::tolower(enteredChar) == 's') {
			currentSelected = std::min((long)options.size() - 1, (long)++currentSelected);
		}
		std::cout << "\033[2J\033[1;1H";
	} while (!std::isspace(enteredChar));
	return currentSelected;
}
