#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include "student.h"
#include "node.h"

using namespace std;

int correctInput();
void add(Student* &s, vector<Student*> &v, Node** &nodeArray, int &size);
void print(Node** &hashTable, int &size);
void del(Node** &hashTable, int &size);
void hashFunction(Node** &hashTable, int &size);

int main() {
  Node** hashTable = new Node* [100];
  int size = 100;
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
	add(student, studentList, hashTable, size);
      }
      // Runs through the vector and prints out the students.
      else if (option == 2) {
	print(hashTable, size);
      }
      // Remove a student from the student list based on their student ID.
      else if (option == 3) {
	del(hashTable, size);
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

void add(Student* &s, vector<Student*> &v, Node** &hashTable, int &size) {
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
  int location = (inputNode->getStudent()->getID())%100;
  bool hashing = true;
  while (hashing == true) {
    if (hashTable[location] == NULL) {
      cout << "first" << endl;
      hashTable[location] = inputNode;
      hashing = false;
    }
    else if (hashTable[location]->getNext() == NULL) {
      cout << "second" << endl;
      hashTable[location]->setNext(inputNode);
      hashing = false;
    }
    else if (hashTable[location]->getNext()->getNext() == NULL) {
      cout << "third" << endl;
      (hashTable[location]->getNext())->setNext(inputNode);
      hashing = false;
    }
    else {
      hashFunction(hashTable, size);
    }
  }
  cout << "size: " << size << endl;
  cout << endl;
}

void print(Node** &hashTable, int &size) {
  for (int i = 0; i < size; i++) {
    if (hashTable[i] != NULL) {
      if (hashTable[i]->getNext() != NULL) {
	if (hashTable[i]->getNext()->getNext() != NULL) {
	  cout << hashTable[i]->getStudent()->getFirstName() << " " << hashTable[i]->getStudent()->getLastName() << ", " << hashTable[i]->getStudent()->getID() << " " << hashTable[i]->getStudent()->getGPA() << endl;
	  cout << hashTable[i]->getNext()->getStudent()->getFirstName() << " " << hashTable[i]->getNext()->getStudent()->getLastName() << ", " << hashTable[i]->getNext()->getStudent()->getID() << " " << hashTable[i]->getNext()->getStudent()->getGPA() << endl;
	  cout << hashTable[i]->getNext()->getNext()->getStudent()->getFirstName() << " " << hashTable[i]->getNext()->getNext()->getStudent()->getLastName() << ", " << hashTable[i]->getNext()->getNext()->getStudent()->getID() << " " << hashTable[i]->getNext()->getNext()->getStudent()->getGPA() << endl;
	}
	else {
	  cout << hashTable[i]->getStudent()->getFirstName() << " " << hashTable[i]->getStudent()->getLastName() << ", " << hashTable[i]->getStudent()->getID() << " " << hashTable[i]->getStudent()->getGPA() << endl;
	  cout << hashTable[i]->getNext()->getStudent()->getFirstName() << " " << hashTable[i]->getNext()->getStudent()->getLastName() << ", " << hashTable[i]->getNext()->getStudent()->getID() << " " << hashTable[i]->getNext()->getStudent()->getGPA() << endl;
	}
      }
      else {
	cout << hashTable[i]->getStudent()->getFirstName() << " " << hashTable[i]->getStudent()->getLastName() << ", " << hashTable[i]->getStudent()->getID() << " " << hashTable[i]->getStudent()->getGPA() << endl;
      }
    }
  }
  cout << endl;
}

void del(Node** &hashTable, int &size) {
  cout << "Please enter the student ID of the student you want to remove from the list." << endl;
  int intInput;
  cin >> intInput;
  cin.get();
}

void hashFunction(Node** &hashTable, int &size) {
  Node** tempHashTable = hashTable;
  size *= 2;
  hashTable = new Node* [size];
  for (int i = 0; i < size; i++) {
    hashTable[i] = NULL;
  }
  int newLocation;
  for (int i = 0; i < size; i++) {
    if (hashTable[i] != NULL) {
      if (hashTable[i]->getNext() != NULL) {
	if (hashTable[i]->getNext()->getNext() != NULL) {
	  newLocation = (tempHashTable[i]->getStudent()->getID())%(size);
	  hashTable[newLocation] = tempHashTable[i];
	  
	  newLocation = (tempHashTable[i]->getNext()->getStudent()->getID())%(size);
	  hashTable[newLocation]->setNext(tempHashTable[i]->getNext());
	  
	  newLocation = (tempHashTable[i]->getNext()->getNext()->getStudent()->getID())%(size);
	  (hashTable[newLocation]->getNext())->setNext(tempHashTable[i]->getNext()->getNext());
	}
	else {
	  newLocation = (tempHashTable[i]->getStudent()->getID())%(size);
	  hashTable[newLocation] = tempHashTable[i];
	  
	  newLocation = (tempHashTable[i]->getNext()->getStudent()->getID())%(size);
	  hashTable[newLocation]->setNext(tempHashTable[i]->getNext());
	}
      }
      else {
	newLocation = (tempHashTable[i]->getStudent()->getID())%(size);
	hashTable[newLocation] = tempHashTable[i];
      }
    }
  }
}
