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

#include <string>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <vector>
#include <conio.h>
#include <math.h>
#include "EasyFile.h"

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
    double gpa = 0;
    bool isEligible = false;
public:
    student();
    student(std::string, std::string);
    student(std::string, std::string, bool, std::vector<Course>); //firstname, lastname, total average, disciplinary infraction.
    void promptGrades(); // Prompts all the grades of the student, returns true if eligible for HR.
    void updateAverage(); // Updates the average to match current grades.
    void updateEligibility(); // Updates the eligibility for Honor Roll
    void update(); // Updates the entire class
    int getAvg(); // Returns the current student's average
    double getGpa(); // Returns the GPA
    bool hasInfraction(); // Returns whether or not the student has an infraction.
    void changeInfraction(bool);
    std::string getlName(); // Returns the first name
    std::string getfName(); // Returns the last name
    void setfName(std::string); // Sets the first name
    void setlName(std::string); // Sets the last name
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
        FName;LName;Total_Avg;GPA;Disp_Infraction[Y or N];Class1;Grade;Class2;Grade;Class3;Grade...
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
    void setFile(EasyFile); // Sets the classFile to the givenFile.
    void addStudent(student);
    bool readData(); // Reads the data from the classFile
    void fullReport(); // Displays the full report.
    bool fullStudentReport(std::string); // Displays the full report for a specific student. Returns true if successful and false if not.
    void gpaReport(); // Displays the gpa report.
    bool gpaStudentReport(std::string); // Displays the gpa report for a specific student. Returns true if successful and false if not.
    void disciplinaryReport(); // Displays the disciplinary infractions of all students.
    void administrator(); // Enables administrator mode.
    void syncFile(); // Rewrites the file to match new data.
};
