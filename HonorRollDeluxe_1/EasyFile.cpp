/*
The cpp file for the EasyFile class. Do not edit.
*/

#include "EasyFile.h"


EasyFile::EasyFile() {
	// Do nothing.
}

EasyFile::EasyFile(std::string filePath) {
	path = filePath;
}

bool EasyFile::readFile() {
	lines.clear(); // Clear the lines vector for a fresh read.
	try {
		std::ifstream file(path);
		std::string curInput = "";
		while (getline(file, curInput)) {
			lines.push_back(curInput);
		}
		file.close();
		resetCursor(); // If a new read is happening, reset the cursor.
		read = true;
		return true;
	}
	catch (...) {
		read = false;
		return false;
	}
}

std::string EasyFile::nextLine() {
	if (cursor >= lines.size()) {
		return "CODE:EOF";
	}
	else {
		return lines.at(cursor++); // Returns the next line. Adds one to cursor.
	}
}

void EasyFile::setCursor(int newPos) {
	cursor = newPos;
}

void EasyFile::resetCursor() {
	cursor = 0;
}

void EasyFile::decrementCursor() {
	--cursor;
}

void EasyFile::decrementCursor(int amount) {
	cursor -= amount;
}

void EasyFile::incrementCursor() {
	++cursor;
}

void EasyFile::incrementCursor(int amount) {
	cursor += amount;
	if (cursor > lines.size() - 1) {
		
	}
}

int EasyFile::size() {
	if (read) {
		return lines.size();
	}
}

void EasyFile::appendString(std::string addition) {
	
	try {
		std::ofstream file;
		file.open(path, std::ios::app);
		file << addition;
		file.close();
	}
	catch (...) {
		std::cout << "Exception handled: EasyFile(\"" << path << "\"\n";
	}
}

void EasyFile::overwriteString(std::string newText) {
	std::ofstream file;
	try {
		file.open(path, std::ios::out);
		file << newText;
		file.close();
	}
	catch (...) {
		std::cout << "Exception handled: EasyFile(\"" << path << "\"\n";
	}
}

void EasyFile::setPath(std::string newPath) {
	path = newPath;
}