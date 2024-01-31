#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student{
 public:
  // Getters
  char* getFirstName();
  char* getLastName();
  int getID();
  float getGPA();
  // Variables
  char firstName[20];
  char lastName[20];
  int ID;
  float GPA; 
};
#endif
