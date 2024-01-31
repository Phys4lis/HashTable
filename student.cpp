#include <iostream>
#include "student.h"

using namespace std;

// Getters
char* Student::getFirstName() {
  return firstName;
}

char* Student::getLastName() {
  return lastName;
}

int Student::getID() {
  return ID;
}

float Student::getGPA() {
  return GPA;
}
