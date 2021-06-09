/**  
  * Name: Jacoby Blanke
  * Program Name: Honor Roll
  * Date: 02/07/2021
  * Extra: N/A
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
const int TABLE_SPACES = 25; // A constant used for table spaceing (CHANGING THIS WILL SCREW UP OUTPUT)

const int PASSING_AVG = 90; // The min grade average needed for passing 
const int PASSING_COURSES = 5; // The min course number needed for passing

void sort_classes() 
{
    std::ifstream infile("Classes.txt");
    std::string line;
    int count = 0, count2 = 0;
    std::vector<std::vector<std::string>> data;
    size_t pos;
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

    for (int i = 0; i < data.size(); i++) 
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            std::cout << data[i][j] << std::endl;
        }
    }
}

std::vector<std::string> getFullName() 
{
  std::string givenName = "", arr[2] = {"", ""}, tester, token;
  std::size_t pos;
  for (;;) {
    std::cout << "Please enter your full name: ";
    getline(std::cin, givenName);
    if (givenName.length() > 1)
      break;
    std::cout << "\nInvalid name. Please have more than 1 character.\n" << std::endl;
  }
   

  std::istringstream iss(givenName, std::istringstream::in);
  int i = 0;
  while(iss >> arr[i])
    i++;
    
  return std::vector<std::string>{arr[1], arr[0]};
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


void student::promptGrades() { // Prompts the user for grades.
    std::cout << "Enter the number of courses you take (" + std::to_string(MIN_COURSES) + " - " + std::to_string(MAX_COURSES) + "): ";
    int courseNum = 0;
    while (!getValidInt(courseNum)) {
      std::cout << "\n\tInvalid. Make sure it is between " + std::to_string(MIN_COURSES) + " and " + std::to_string(MAX_COURSES) + " inclusevely\n";
    }
    for (int i = 0; i < courseNum; i++) {
      std::string courseName = "";
      std::cout << "Enter the name of course " + std::to_string(i+1) + " (1 - " + std::to_string(COURSE_NAME_LIMIT) + " characters): ";
      getline(std::cin, courseName);
      std::remove_if(courseName.begin(), courseName.end(), isspace);
      while (courseName.length() < 1) {
        std::cout << "\n\tInvalid. Please enter a valid name: ";
        getline(std::cin, courseName);
        std::remove_if(courseName.begin(), courseName.end(), isspace);
      }
      if (courseName.length() > COURSE_NAME_LIMIT) {
        courseName = courseName.substr(0, 20); // Clipping the name to COURSE_NAME_LIMIT characters
      }
      std::cout << "Please enter the average for " + courseName + " (" + std::to_string(MIN_SCORE) + " - " + std::to_string(MAX_SCORE) + "): ";
      int courseAvg = 0;
      while (!getValidInt(courseAvg)) {
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
}

void student::updateEligibility() 
{
    isEligible = (average >= PASSING_AVG && courses.size() >= PASSING_COURSES && !hasDisciplineIssue); // Condition for determining Honor Roll
}

int student::getAvg()
{
    return average;
}

void student::update() 
{
    updateAverage(); // Average must be updated prior to eligibility
    updateEligibility();
}

std::string student::getSaveString() {
    std::string fin = fName + ";" + lName + ";" + std::to_string(average) + ";";
    (hasDisciplineIssue) ? fin += "Y;" : fin += "N;";
    for (Course i : courses) {
        fin += i.getName() + ";" + std::to_string(i.getGrade());
    }
    fin += "\n";
    return fin;
}

std::ostream& operator<<(std::ostream& output, const student& aStudent) 
{    
    output << "\n\t" << aStudent.fName << " " << aStudent.lName << "\n\nClass" << std::string(20, ' ') << "Grade\n"; // The name and table labels
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

void Course::setGrade(int newGrade) {
    grade = newGrade;
}

std::ostream& operator<<(std::ostream& output, const Course& aCourse) 
{
    output << aCourse.courseName << std::string(aCourse.courseName.length(), ' ') << aCourse.grade << std::endl; // Outputting the course data according to the spacing constant
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
#pragma endregion
