/**
  * Names: Jacoby Blanke and Alexei Korolev
  * Program Name: Honour Roll Deluxe
  * Date: 06/11/2021
  * Known Issues: Code is incomplete. All basic requirements are met, but none of the deluxe requirements are yet fulfilled.
  */ 

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class EasyFile {
private: 
    // Constructable //
    std::string path = "";

    // Unconstructable //
    std::vector<std::string> lines;
    bool read = false;
    int cursor = 0;
public: 
    // Constructors //
    EasyFile();
    EasyFile(std::string);

    // Read methods //
    bool readFile(); // Reads the file at the filepath.
    std::string nextLine(); // Gets the next line.
    std::vector<std::string> getFileData(); // Returns the enture vector of information.
    void setCursor(int); // Sets the cursor to a position
    void resetCursor(); // Resets the cursor to 0
    void decrementCursor(); // Decrements by 1
    void decrementCursor(int); // Decrements by x
    void incrementCursor(); // Increments by 1
    void incrementCursor(int); // Increments by x
    int getCursor(); // Returns the cursor.
    bool hasFile();
    int size();

    // Write methods //
    void appendString(std::string); // Adds a string onto the end of a file.
    void overwriteString(std::string); // Completely overwrites the file.

    // Others //
    void setPath(std::string); // Sets the path of the EasyFile
};
