/**
  * Names: Jacoby Blanke and Alexei Korolev
  * Program Name: Honour Roll Deluxe
  * Date: 06/11/2021
  * Known Issues: Code is incomplete. All basic requirements are met, but none of the deluxe requirements are yet fulfilled.
  */

#include "HonorRollClasses.h"
#include "GetData.h"
#include <vector>
#include <string_view>
#include <sstream>
#include <fstream>
#include <string>

const int MAX_COURSES = 8; // The maximum number of courses allowed
const int MAX_SCORE = 120; // The maximum grade allowed
const int MIN_SCORE = 0; // The minimum score allowed (0 is recommended)
const int MIN_COURSES = 1; // The minimum number of courses allowed (1 is recommended)
const int COURSE_NAME_LIMIT = 20; // Limit in characters for the course name
const int DISIPLINARY_CHANCE = 5; // The chance in percent for a disciplinary issue to arise.
const int TABLE_SPACES = 28; // A constant used for table spaceing (CHANGING THIS WILL SCREW UP OUTPUT)

const int PASSING_AVG = 90; // The min grade average needed for passing
const int PASSING_COURSES = 5; // The min course number needed for passing

char holderChar = ' ';

void build_student()
{
    std::ifstream infileClass("Classes.txt");
    std::string line;
    int count = 0, count2 = 0, count3 = 0;
    std::vector<std::vector<std::string>> data;
    size_t pos;
    std::vector<std::string> classesLocations;
    while (std::getline(infileClass, line))
    {
        classesLocations.push_back(line);
        count3++;
    }

    for (int i = 0; i < classesLocations.size(); i++)
    {
     std::ifstream infile(classesLocations[i] + ".txt");
     while (std::getline(infile, line))
     {
         while ((pos = line.find(";")) != std::string::npos)
         {
             data[count][count2] = line.substr(0,line.find(";"));
             line.erase(0, pos + 1);
             count2++;
         }
         count++;
     }
    }
    /*std::vector<Course> courses;
    for (int i = 4; i < (data.size() - 4 ); i++)
    {
      courses.push_back(new Course(data[0][i], data[0][i+1]));
    }
    student person = new student(data[0][0], data[0][1], std::stoi(data[0][2]), data[0][3], courses);*/

}

std::vector<std::string> getFullName()
{
    std::string givenName = "", arr[2] = { "", "" }, tester, token;
    std::size_t pos;
    for (;;) {
        std::cout << "Please enter your full name: ";
        getline(std::cin, givenName);
        if (givenName.length() > 0)
            break;
        std::cout << "\nInvalid name. Please have 1 or more character.\n" << std::endl;
    }
    std::vector<std::string> splitName;
    std::string curSeg = "";
    for (char i : givenName) {
        if (!isspace(i)) {
            curSeg += i;
        }
        else if (curSeg != "") {
            splitName.push_back(curSeg);
            curSeg = "";
        }
    }
    if (curSeg != "")
        splitName.push_back(curSeg);
    /*std::istringstream iss(givenName, std::istringstream::in);
    int i = 0;
    while (iss >> arr[i])
        i++;
    if (arr[0] == "") {
        arr[0] = arr[1];
        arr[1] = "";
    }*/
    if (splitName.size() > 1)
        return std::vector<std::string>{splitName[splitName.size() - 1], splitName[0]};
    else
        return std::vector<std::string>{splitName[0]};
}

student::student()
{
    srand((unsigned)time(0)); // Making the time unsigned avoids any glitchy problems
    std::vector<std::string> name = getFullName();
    if (name.size() == 1) {
        lName = name.at(0); // If there is 1 name, assign it as a last name
    }
    else {
        fName = name.at(1); // If there are 2 names, then assign the variables respectively.
        lName = name.at(0);
    }
}

student::student(std::string firstName, std::string lastName)
{
  fName = firstName;
  lName = lastName;
}

student::student(std::string firstName, std::string lastName, int avgGrade, bool disciplineInfraction, std::vector<Course> classesNamesAndGrades)
{
  fName = firstName;
  lName = lastName;
  hasDisciplineIssue = disciplineInfraction;
  average = avgGrade;
  courses = classesNamesAndGrades; 
}

void student::promptGrades() { // Prompts the user for grades.
    std::cout << "Enter the number of courses you take (" + std::to_string(MIN_COURSES) + " - " + std::to_string(MAX_COURSES) + "): ";
    int courseNum = 0;
    while (!getValidInt(courseNum) || courseNum < MIN_COURSES || courseNum > MAX_COURSES) {
      std::cout << "\n\tInvalid. Make sure it is between " + std::to_string(MIN_COURSES) + " and " + std::to_string(MAX_COURSES) + " inclusevely: ";
    }
    for (int i = 0; i < courseNum; i++) {
      std::string courseName = "";
      std::cout << "Enter the name of course " + std::to_string(i+1) + " (1 - " + std::to_string(COURSE_NAME_LIMIT) + " characters): ";
      getline(std::cin, courseName);
      while (courseName.length() < 1) {
        std::cout << "\n\tInvalid. Please enter a valid name: ";
        getline(std::cin, courseName);
      }
      if (courseName.length() > COURSE_NAME_LIMIT) {
        courseName = courseName.substr(0, 20); // Clipping the name to COURSE_NAME_LIMIT characters
      }
      std::cout << "Please enter the average for " + courseName + " (" + std::to_string(MIN_SCORE) + " - " + std::to_string(MAX_SCORE) + "): ";
      int courseAvg = 0;
      while (!getValidInt(courseAvg) || courseAvg < MIN_SCORE || courseAvg > MAX_SCORE) {
        std::cout << "\n\tInvalid. Please keep the average between " + std::to_string(MIN_SCORE) + " and " + std::to_string(MAX_SCORE) + ": ";
      }
      Course newCourse = Course(courseName, courseAvg); // Making a new course obj to store the data
      courses.push_back(newCourse); // Adding the course to the student
    }
    update(); // Making sure everything is updated
}

void student::updateAverage() // Updates the average to work with new values
{
    int totalSum = 0; // The total sum of all the grades; used for averaging.
    for (Course i : courses) {
        totalSum += i.getGrade();
    }
    average = round(static_cast<double>(totalSum) / courses.size()); // Calculating the rounded average. I like to use static_cast<double> rather than (double)
    gpa = round(10.0 * average / 25) / 10.0;
}

void student::updateEligibility()
{
    isEligible = (average >= PASSING_AVG && courses.size() >= PASSING_COURSES && !hasDisciplineIssue); // Condition for determining Honor Roll
}

int student::getAvg()
{
    return average;
}

std::string student::getlName() {
    return lName;
}

std::string student::getfName() {
    return fName;
}

double student::getGpa() {
    return gpa;
}

void student::setfName(std::string newName) {
    fName = newName;
}

void student::setlName(std::string newName) {
    lName = newName;
}

bool student::hasInfraction() {
    return hasDisciplineIssue;
}

void student::update()
{
    updateAverage(); // Average must be updated prior to eligibility
    updateEligibility();
}

std::string student::getSaveString() {
    std::string fin = fName + "\n" + lName + "\n" + std::to_string(average) + "\n";
    (hasDisciplineIssue) ? fin += "Y\n" : fin += "N\n";
    fin += std::to_string(courses.size()) + "\n";
    for (Course i : courses) {
        fin += i.getName() + "\n" + std::to_string(i.getGrade()) + "\n";
    }
    return fin;
}

std::ostream& operator<<(std::ostream& output, const student& aStudent)
{
    output << "\n\t" << aStudent.fName << " " << aStudent.lName << "\n\nClass" << std::string(TABLE_SPACES - 5, ' ') << "Grade\n"; // The name and table labels
    for (Course i : aStudent.courses) {
        std::cout << i; // Print each course
    }
    std::string dsp = (aStudent.hasDisciplineIssue) ? "YES" : "NO"; // Logic for printing whether or not there is a disciplinary issue.
    std::string statement = (aStudent.isEligible) ? "Congratulations " + aStudent.fName + " " + aStudent.lName + "! You have made the honor roll.\n" : "I'm sorry " + aStudent.fName + " " + aStudent.lName + " but you didn't qualify for the honor roll."; // Logic for eligibility
    output << "\nAverage: " << aStudent.average << "\nDisciplinary Infraction: " << dsp << std::endl << std::endl << statement << std::endl << std::endl; // Printint all the statements out.
    return output;
}

Course::Course() {}

Course::Course(std::string name)
{
    courseName = name;
}
Course::Course(int avg)
{
    grade = avg;
}
Course::Course(std::string name, int avg)
{
    courseName = name;
    grade = avg;
}

int Course::getGrade()
{
    return grade;
}

std::string Course::getName() {
    return courseName;
}

std::ostream& operator<<(std::ostream& output, const Course& aCourse)
{
    output << aCourse.courseName << std::string(TABLE_SPACES - aCourse.courseName.length(), ' ') << aCourse.grade << std::endl; // Outputting the course data according to the spacing constant
    return output;
}
#pragma endregion

#pragma region Class

ClassCollection::ClassCollection()
{

}

ClassCollection::ClassCollection(std::string name)
{
    className = name;
}


ClassCollection::ClassCollection(std::vector<student> givenStudents) {
    students = givenStudents;

}

ClassCollection::ClassCollection(EasyFile file) {
    classFile = file;
}

ClassCollection::ClassCollection(std::string name, std::vector<student> givenStudents) {
    className = name;
    students = givenStudents;
}

ClassCollection::ClassCollection(std::vector<student> givenStudents, EasyFile file) {
    students = givenStudents;
    classFile = file;
}

ClassCollection::ClassCollection(std::string name, EasyFile file) {
    className = name;
    classFile = file;
}

ClassCollection::ClassCollection(std::string name, std::vector<student> givenStudents, EasyFile file) {
    className = name;
    students = givenStudents;
    classFile = file;
}

void ClassCollection::setPath(std::string path) {
    classFile.setPath(path);
}

void ClassCollection::setFile(EasyFile file) {
    classFile = file;
}

#pragma endregion
void ClassCollection::addStudent(student s) {
    students.push_back(s);
    classFile.appendString(s.getSaveString());
}

bool ClassCollection::readData() {
    if (classFile.hasFile()) {
        classFile.readFile();
        std::string currentLine = classFile.nextLine();
        while (currentLine != "CODE:EOF" && abs(classFile.getCursor() - classFile.size()) > 5) {
            try {
                std::string fName = currentLine;
                std::string lName = classFile.nextLine();
                int avg = stoi(classFile.nextLine());
                bool issue = (classFile.nextLine()[0] == 'Y') ? true : false;
                int courseNum = stoi(classFile.nextLine());
                std::vector<Course> foundCourses;
                for (int i = 0; i < courseNum; i++) {
                    std::string courseName = classFile.nextLine();
                    int courseGrade = stoi(classFile.nextLine());
                    Course newCourse(courseName, courseGrade);
                    foundCourses.push_back(newCourse);
                }
                student newStudent(fName, lName, avg, issue, foundCourses);
                newStudent.update();
                students.push_back(newStudent);
                currentLine = classFile.nextLine();
            }
            catch (...) {
                std::cout << "An error occured when reading file data. The file may be corrupted or incomplete.";
                return false;
            }
        }
    }
    else {
        std::cout << "No file detected.";
        return false;
    }
}

void ClassCollection::fullReport() {
    std::vector<student> sortCopy = students; // Copying the students vector in order to not accidentally mutate the orignal.
    bool flag = true;
    while (flag) { // Sorting the students alphabetically.
        flag = false;
        for (int i = 1; i < sortCopy.size(); i++) {
            if (sortCopy[i - 1].getlName().compare(sortCopy[i].getlName()) > 0) { // Alphabetical logic.
                student temp = sortCopy[i - 1]; // Student swap logic
                sortCopy[i - 1] = sortCopy[i];
                sortCopy[i] = temp;
                flag = true;
            }
            else if (sortCopy[i - 1].getlName().compare(sortCopy[i].getlName()) == 0) {
                if (sortCopy[i - 1].getfName().compare(sortCopy[i].getfName()) > 0) { // Sorting by first name if the lastname is identical.
                    student temp = sortCopy[i - 1]; // Student swap logic
                    sortCopy[i - 1] = sortCopy[i];
                    sortCopy[i] = temp;
                    flag = true;
                }
            }
        }
    }
    for (student i : sortCopy) {
        std::cout << i;
    }
    std::cout << "\nPress any key to continue: "; 
    holderChar = _getch(); // A way of pausing.
}

bool ClassCollection::fullStudentReport(std::string name) {
    bool flag = false;
    std::vector<student> foundStudents;
    for (student i : students) { // Looping through the students and finding those with the needed lastname
        if (i.getlName() == name) {
            flag = true;
            foundStudents.push_back(i);
        }
    }
    if (foundStudents.size() > 1) { // If there are multiple students with the same last name...
        std::vector<std::string> studentNames(foundStudents.size());
        for (int i = 0; i < foundStudents.size(); i++) {
            studentNames[i] = foundStudents[i].getfName() + ", " + foundStudents[i].getlName();

        }studentNames.push_back("Back to Menu"); // Return option
        Menu choice(studentNames, "Multiple Students with the lastname " + name + " were found. How would you like to proceed?\n");
        int option = choice.getSelectedOption();
        if (option < foundStudents.size()) {
            std::cout << foundStudents[option];
            std::cout << "\nPress any key to continue: ";
            holderChar = _getch(); // A way of pausing.
            return true;
        }
        else {
            return false;
        }
    }
    else if (foundStudents.size() == 1) {
        std::cout << foundStudents[0];
        std::cout << "\nPress any key to continue: ";
        holderChar = _getch(); // A way of pausing.
        return true;
    }
    else {
        return false;
    }
    return flag;
}

void ClassCollection::gpaReport() {
    std::vector<student> sortCopy = students; // Copying the students vector in order to not accidentally mutate the orignal.
    bool flag = true;
    while (flag) { // Sorting the students by gpa.
        flag = false;
        for (int i = 1; i < sortCopy.size(); i++) {
            if (sortCopy[i - 1].getAvg() < sortCopy[i].getAvg()) { // Numerical logic
                student temp = sortCopy[i - 1]; // Student swap logic
                sortCopy[i - 1] = sortCopy[i];
                sortCopy[i] = temp;
                flag = true;
            }
            else if (sortCopy[i - 1].getAvg() == sortCopy[i].getAvg()) {
                if (sortCopy[i - 1].getlName().compare(sortCopy[i].getlName()) > 0) { // Sorting by lastname if the gpa is identical.
                    student temp = sortCopy[i - 1]; // Student swap logic
                    sortCopy[i - 1] = sortCopy[i];
                    sortCopy[i] = temp;
                    flag = true;
                }else if (sortCopy[i - 1].getlName().compare(sortCopy[i].getlName()) == 0) {
                    if (sortCopy[i - 1].getfName().compare(sortCopy[i].getfName()) > 0) { // Sorting by first name if the lastname is identical.
                        student temp = sortCopy[i - 1]; // Student swap logic
                        sortCopy[i - 1] = sortCopy[i];
                        sortCopy[i] = temp;
                        flag = true;
                    }
                }
            }
        }
    }
    std::cout << "Name" << std::string(TABLE_SPACES - 4, ' ') << "GPA\n";
    for (student i : sortCopy) {
        std::cout << i.getfName() + ' ' + i.getlName() << std::string(TABLE_SPACES - (i.getfName().length() + i.getlName().length() + 1), ' ') << i.getAvg() << std::endl;
    }
    std::cout << "\nPress any key to continue: ";
    holderChar = _getch(); // A way of pausing.
}
bool ClassCollection::gpaStudentReport(std::string name) {
    bool flag = false;
    std::vector<student> foundStudents;
    for (student i : students) { // Looping through the students and finding those with the needed lastname
        if (i.getlName() == name) {
            flag = true;
            foundStudents.push_back(i);
        }
    }
    if (foundStudents.size() > 1) { // If there are multiple students with the same last name...
        std::vector<std::string> studentNames(foundStudents.size());
        for (int i = 0; i < foundStudents.size(); i++) {
            studentNames[i] = foundStudents[i].getfName() + ", " + foundStudents[i].getlName();

        }studentNames.push_back("Back to Menu"); // Return option
        Menu choice(studentNames, "Multiple Students with the lastname " + name + " were found. How would you like to proceed?\n");
        int option = choice.getSelectedOption();
        if (option < foundStudents.size()) {
            std::cout << foundStudents[option].getfName() + ' ' + foundStudents[option].getlName() << std::string(TABLE_SPACES - (foundStudents[option].getfName().length() + foundStudents[option].getlName().length() + 1), ' ') << foundStudents[option].getAvg() << std::endl;
            std::cout << "\nPress any key to continue: ";
            holderChar = _getch(); // A way of pausing.
            return true;
        }
        else {
            return false;
        }
    }
    else if (foundStudents.size() == 1) {
        std::cout << foundStudents[0].getfName() + ' ' + foundStudents[0].getlName() << std::string(TABLE_SPACES - (foundStudents[0].getfName().length() + foundStudents[0].getlName().length() + 1), ' ') << foundStudents[0].getAvg() << std::endl;
        std::cout << "\nPress any key to continue: ";
        holderChar = _getch(); // A way of pausing.
        return true;
    }
    else {
        return false;
    }
    return flag;
}

void ClassCollection::disciplinaryReport() {
    bool flag = false;
    std::vector<student> foundStudents;
    for (student i : students) { // Looping through the students and finding those with infractions
        if (i.hasInfraction()) {
            flag = true;
            foundStudents.push_back(i);
        }
    }

    while (flag) { // Sorting the students by gpa.
        flag = false;
        for (int i = 1; i < foundStudents.size(); i++) {
            if (foundStudents[i - 1].getlName().compare(foundStudents[i].getlName()) > 0) { // Alphabetical logic.
                student temp = foundStudents[i - 1]; // Student swap logic
                foundStudents[i - 1] = foundStudents[i];
                foundStudents[i] = temp;
                flag = true;
            }
            else if (foundStudents[i - 1].getlName().compare(foundStudents[i].getlName()) == 0) {
                if (foundStudents[i - 1].getfName().compare(foundStudents[i].getfName()) > 0) { // Sorting by first name if the lastname is identical.
                    student temp = foundStudents[i - 1]; // Student swap logic
                    foundStudents[i - 1] = foundStudents[i];
                    foundStudents[i] = temp;
                    flag = true;
                }
            }
        }
    }
    std::cout << "Num" << std::string(TABLE_SPACES - 3, ' ') << "Student\n";
    for (int i = 0; i < foundStudents.size(); i++) {
        std::cout << std::to_string(i + 1) << std::string(TABLE_SPACES - std::to_string(i + 1).length(), ' ') << foundStudents[i].getfName() << ' ' << foundStudents[i].getlName() << std::endl;
    }
}

#pragma endregion
