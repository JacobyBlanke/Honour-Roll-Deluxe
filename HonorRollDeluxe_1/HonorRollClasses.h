/**  
  * Name: Jacoby Blanke
  * Program Name: Honor Roll
  * Date: 02/07/2021
  * Extra: N/A
  */
#include <string>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <vector>
#include <conio.h>
#include <math.h>
#include "EasyFile.h"

EasyFile Addresses("Classes.txt");

class Course;

class student
{
private:
  	// Constructable //
	std::string fName = "", lName = "";
	bool hasDisciplineIssue = false;

	// Non-constructable //
	std::vector<Course> courses;
	int average = 0;
	bool isEligible = false;
public:
  student();
  student(std::string, std::string);
  void promptGrades(); // Prompts all the grades of the student, returns true if eligible for HR.
	void updateAverage(); // Updates the average to match current grades.
	void updateEligibility(); // Updates the eligibility for Honor Roll
	void update(); // Updates the entire class
	int getAvg(); // Returns the current student's average
  friend std::ostream& operator<<(std::ostream&, const student&);
};

class Course {
private:
	// Constructable //
	std::string courseName = "";
	int grade = 0;

public:
	// Constructors //
	Course();
	Course(std::string);
	Course(int);
	Course(std::string, int);
  
	// Methods //
	int getGrade(void); // Returns the current grade of this course;
	void setGrade(int); // Sets the current grade to a given value
	friend std::ostream& operator<<(std::ostream&, const Course&); // Overloading the '<<' operator for printing.
};

class Class {
private: 
	// Contructable //
	std::string className = "";
	std::vector<student> students;
	EasyFile classFile;
	// Unconstructable //
	bool readSuccessful = false;
public: 
	// Constructors //
	Class();
	Class(std::string);
	Class(std::vector<student>);
	Class(EasyFile);
	Class(std::string, std::vector<student>);
	Class(std::vector<student>, EasyFile);
	Class(std::string, EasyFile);
	Class(std::string, std::vector<student>, EasyFile);

	// Methods //
	void setPath(std::string);
	void setFile(EasyFile);
	void addStudent(student);
	void removeStudent(student);
	bool readData();
};