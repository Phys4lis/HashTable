#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include "student.h"
#include "node.h"

using namespace std;

int correctInput();
void add(Student* &s, vector<Student*> &v, Node** (&nodeArray)[100]);
void print(vector<Student*> v);
void del(vector<Student*> &v);
void hashFunction(Node* (&hashTable)[100], Node* &inputNode);

int main() {
  Node** hashTable = new Node* [100];
  for (int i = 0; i < 100; i++) {
    hashTable[i] == NULL;
  }
  vector<Student*> studentList;
  bool running = true;
  while (running == true) {
    int option = correctInput();
      //If the user wants to add a new student
      if (option == 1) {
	Student *student = new Student();
	add(student, studentList, hashTable);
      }
      // Runs through the vector and prints out the students.
      else if (option == 2) {
	print(studentList);
      }
      // Remove a student from the student list based on their student ID.
      else if (option == 3) {
	del(studentList);
      }
      // Quit the program
      else if (option == 4) {
	running = false;
      }
  }
  return 0;
}

int correctInput() {
  bool leaveLoop = false;
  cout << "Enter one of the following options: ADD, PRINT, DELETE, or QUIT (uppercase)" << endl;
  while (leaveLoop == false) {
    char input[15];
    cin.get(input, 15);
    cin.ignore(15, '\n');
    if (strcmp(input, "ADD") == 0) {
      return 1;
    }
    else if (strcmp(input, "PRINT") == 0) {
      return 2;
    }
    else if (strcmp(input, "ADD") == 0) {
      return 3;
    }
    else if (strcmp(input, "QUIT") == 0) {
      return 4;
    }
    else {
      cout << "Please enter a valid option." << endl;
    }
  }
  return -1;
}

void add(Student* &s, vector<Student*> &v, Node** (&hashTable)[100]) {
  // Prompt first name
  cout << "Please enter a first name." << endl;
  char input[20];
  cin.get(input, 20);
  cin.get();
  strcpy(s->firstName, input);
  // Prompt last name
  cout << "Please enter a last name." << endl;
  cin.get(input, 20);
  cin.get();
  strcpy(s->lastName, input);
  // Prompt id
  bool correctID = false;
  while (correctID == false) {
    cout << "Please enter an ID." << endl;
    int intInput;
    cin >> intInput;
    cin.get();
    int temp = 0;
    for (vector<Student*>::iterator iter = v.begin(); iter < v.end(); iter++) {
      if (intInput == (*iter)->ID) {
        temp++;
      }
    }
    if (temp == 0) {
      s->ID = intInput;
      correctID = true;
    }
    else {
      cout << "That ID is already being used!" << endl;
    }
  }
  // Prompt gpa
  cout << "Please enter a gpa." << endl;
  float floatInput;
  cin >> floatInput;
  cin.get();
  s->GPA = floatInput;
  // Add the struct pointer to the vector
  v.push_back(s);

  Node* inputNode = new Node(s);
  hashFunction(hashTable, inputNode);
    
  cout << endl;
}

void print(vector<Student*> v) {
  cout << "Here's a list of the current students:" << endl;
  // Got help with iterators & dereferencing from Lucas Johnson 
  for (vector<Student*>::iterator iter = v.begin(); iter < v.end(); iter++) {
    // Output each student's information. Precision code from geeksforgeeks.org
    cout << (*iter)->firstName << " " << (*iter)->lastName << ", " << fixed << setprecision(2) << (*iter)->ID << ", " << (*iter)->GPA << endl;
  }
  cout << endl;
}

void del(vector<Student*> &v) {
  cout << "Please enter the student ID of the student you want to remove from the list." << endl;
  int intInput;
  cin >> intInput;
  cin.get();
  for (vector<Student*>::iterator iter = v.begin(); iter != v.end(); iter++) {
    // If any id matches with the inputted id, remove that student from the list.
    if (intInput == (*iter)->ID) {
      // Remove the pointer from the heap 
      delete *iter;
      // Remove the element from the vector
      v.erase(iter);
      return;
    }
  }
  cout << endl;
}

// Fixed array declaration in prototype with help from MiiNiPaa at https://cplusplus.com/forum/beginner/167788/
void hashFunction(Node** (&hashTable)[100], Node* &inputNode) {
  int location = (inputNode->getStudent()->getID())%100;
  if (hashTable[location] == NULL) {
    hashTable[location] = inputNode;
  }
}
