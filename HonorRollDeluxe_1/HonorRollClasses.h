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
#include <ncurses.h>
#include <math.h>
#include "EasyFile.h"

<<<<<<< HEAD
=======


>>>>>>> 822b0e9e41a366e0e76894e39c2781d38518d210
class Course;

class student
{
private:
  	// Constructable //
	std::string fName = "", lName = "";
	bool hasDisciplineIssue = false;
	std::vector<Course> courses;
	int average = 0;

	// Non-constructable //
	bool isEligible = false;
public:
  student();
  student(std::string, std::string);
  void sort_classes();
  void promptGrades(); // Prompts all the grades of the student, returns true if eligible for HR.
	void updateAverage(); // Updates the average to match current grades.
	void updateEligibility(); // Updates the eligibility for Honor Roll
	void update(); // Updates the entire class
	int getAvg(); // Returns the current student's average
	std::string getSaveString(); // Returns the student's data in a string for saving.
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
	std::string getName(void); // Returns the name of the course;
	void setGrade(int); // Sets the current grade to a given value

	friend std::ostream& operator<<(std::ostream&, const Course&); // Overloading the '<<' operator for printing.
};

class ClassCollection {
private: 
	// Contructable //
	std::string className = "";
	std::vector<student> students;
	EasyFile classFile;
	// ---- File Structure ---- //
	/*
		FName;LName;Total_Avg;Disp_Infraction[Y or N];Class1;Grade;Class2;Grade;Class3;Grade... 
	*/

	// Unconstructable //
	bool readSuccessful = false;
public: 
	// Constructors //
	ClassCollection();
	ClassCollection(std::string);
	ClassCollection(std::vector<student>);
	ClassCollection(EasyFile);
	ClassCollection(std::string, std::vector<student>);
	ClassCollection(std::vector<student>, EasyFile);
	ClassCollection(std::string, EasyFile);
	ClassCollection(std::string, std::vector<student>, EasyFile);

	// Methods //
	void setPath(std::string);
	void setFile(EasyFile);
	void addStudent(student);
	void removeStudent(student);
	bool readData();
};
