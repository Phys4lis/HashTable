/* This program is essentially student list, but with a hash table (array with linked lists in each index) 
 * Date: 2/12/24
 * Author: Roger Li
 */ 


#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include "student.h"
#include "node.h"
#include "fstream"
#include "iomanip"

using namespace std;

int correctInput();
void add(Student* &s, vector<Student*> &v, Node** &hashTable, int &size);
void addRandom(char** firstNamesArr, char** lastNamesArr, Student* &randStudent, vector<Student*> &v, Node** &hashTable, int&size);
void print(Node** &hashTable, int &size);
void del(Node** &hashTable, int &size);
void hashFunction(Node** &hashTable, int &size);
void addTable (Node** &hashTable, Node* &inputNode, int index, int &size);
void deleteNode(Node* &head, Node* cur, Node* prev, int ID);

int main() {
  // Initialize hash table
  Node** hashTable = new Node* [100];
  int size = 100;
  for (int i = 0; i < 100; i++) {
    hashTable[i] == NULL;
  }
  // Help from Neel Madala on input through a file
  srand(time(NULL));
  char** firstNamesArr = new char*[25];
  char** lastNamesArr = new char*[25];
  for (int i = 0; i < 25; i++) {
    firstNamesArr[i] = new char [20];
    lastNamesArr[i] = new char [20];
  }
  // Copy first names from text file into char double pointer
  ifstream firstNames("firstNames.txt");
  char firstName[20];
  for (int i = 0; i < 25; i++) {
    firstNames.getline(firstName, 20);
    strcpy(firstNamesArr[i], firstName);
  }
  // Copy last names from text file into char double pointer
  ifstream lastNames("lastNames.txt");
  char lastName[20];
  for (int i = 0; i < 25; i++) {
    lastNames.getline(lastName, 20);
    strcpy(lastNamesArr[i], lastName);
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
      // If the user wants to add random students
      else if (option == 2) {
	int studentNum;
	// Prompt user for the amount of students they would like to add
        cout << endl << "How many students would you like to add? " << endl;
	cin >> studentNum;
	cin.get();
	for (int i = 0; i < studentNum; i++) {
	  Student *randStudent = new Student();
	  addRandom(firstNamesArr, lastNamesArr, randStudent, studentList, hashTable, size);
	}
      }
      // Runs through the vector and prints out the students.
      else if (option == 3) {
	print(hashTable, size);
      }
      // Remove a student from the student list based on their student ID.
      else if (option == 4) {
	del(hashTable, size);
      }
      // Quit the program
      else if (option == 5) {
	running = false;
      }
  }
  return 0;
}

// Make sure that the user inputs a valid command
int correctInput() {
  bool leaveLoop = false;
  cout << "Enter one of the following options: ADD, ADDRANDOM, PRINT, DELETE, or QUIT (uppercase)" << endl;
  while (leaveLoop == false) {
    char input[15];
    cin.get(input, 15);
    cin.ignore(15, '\n');
    if (strcmp(input, "ADD") == 0) {
      return 1;
    }
    else if (strcmp(input, "ADDRANDOM") == 0) {
      return 2;
    }
    else if (strcmp(input, "PRINT") == 0) {
      return 3;
    }
    else if (strcmp(input, "DELETE") == 0) {
      return 4;
    }
    else if (strcmp(input, "QUIT") == 0) {
      return 5;
    }
    else {
      cout << "Please enter a valid option." << endl;
    }
  }
  return -1;
}

// Manually add a student
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
    // Make sure the user ID is unique
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
  bool hashing = true;
  // Add node to hash table. If a linked list in hash table ever reaches a length more than 3, rehash.
  while (hashing == true) {
    int location = (inputNode->getStudent()->getID())%size;
    if (hashTable[location] == NULL) {
      hashTable[location] = inputNode;
      hashing = false;
    }
    else if (hashTable[location]->getNext() == NULL) {
      hashTable[location]->setNext(inputNode);
      hashing = false;
    }
    else if (hashTable[location]->getNext()->getNext() == NULL) {
      (hashTable[location]->getNext())->setNext(inputNode);
      hashing = false;
    }
    else {
      hashFunction(hashTable, size);
    }
  }
}

// Randomly add a certain amount of students
void addRandom(char** firstNamesArr, char** lastNamesArr, Student* &randStudent, vector<Student*> &v, Node** &hashTable, int&size) {
  int randFirst = rand() % 24;
  int randLast = rand() % 24;
  strcpy(randStudent->firstName, firstNamesArr[randFirst]);
  strcpy(randStudent->lastName, lastNamesArr[randLast]);
  int randStudentID = 0;
  int temp = 0;
  bool correctID = false;
  // Ensure that user ID is unique
  while (correctID == false) {
    for (vector<Student*>::iterator iter = v.begin(); iter < v.end(); iter++) {
      if (randStudentID == (*iter)->ID) {
	temp++;
      }
    }
    if (temp == 0) {
      randStudent->ID = randStudentID;
      correctID = true;
    }
    else {
      randStudentID++;
      temp = 0;
    }
  }
  float randGPA = (float) (rand() % 401)/100;
  //cout << fixed << setprecision(2) << randGPA;
  randStudent->GPA = randGPA;
  v.push_back(randStudent);
  
  
  Node* randomNode = new Node(randStudent);
  bool hashing2 = true;
  // Add node to hash table. If a linked list in hash table ever reaches a length more than 3, rehash.
  while (hashing2 == true) {
    int location2 = (randomNode->getStudent()->getID())%size;
    if (hashTable[location2] == NULL) {	
      hashTable[location2] = randomNode;
      hashing2 = false;
    }
    else if (hashTable[location2]->getNext() == NULL) {
      hashTable[location2]->setNext(randomNode);
      hashing2 = false;
    }
    else if (hashTable[location2]->getNext()->getNext() == NULL) {
      (hashTable[location2]->getNext())->setNext(randomNode);
      hashing2 = false;
    }
    else {
      hashFunction(hashTable, size);
    }
  }
}

// Print hash table in order of indices
void print(Node** &hashTable, int &size) {
  for (int i = 0; i < size; i++) {
    if (hashTable[i] != NULL) {
      cout << "First name: " << hashTable[i]->getStudent()->getFirstName() << endl;
      cout << "Last name: " << hashTable[i]->getStudent()->getLastName() << endl;
      cout << "ID: " << hashTable[i]->getStudent()->getID() << endl;
      cout << "GPA: " << hashTable[i]->getStudent()->getGPA() << endl;
      if (hashTable[i]->getNext() != NULL) {
	cout << "First name: " << hashTable[i]->getNext()->getStudent()->getFirstName() << endl;
	cout << "Last name: " << hashTable[i]->getNext()->getStudent()->getLastName() << endl;
	cout << "ID: " << hashTable[i]->getNext()->getStudent()->getID() << endl;
	cout << "GPA: " << hashTable[i]->getNext()->getStudent()->getGPA() << endl;
	if (hashTable[i]->getNext()->getNext() != NULL) {
	  cout << "First name: " << hashTable[i]->getNext()->getNext()->getStudent()->getFirstName() << endl;
	  cout << "Last name: " << hashTable[i]->getNext()->getNext()->getStudent()->getLastName() << endl;
	  cout << "ID: " << hashTable[i]->getNext()->getNext()->getStudent()->getID() << endl;
	  cout << "GPA: " << hashTable[i]->getNext()->getNext()->getStudent()->getGPA() << endl;
	}
      }
    }
  }
  cout << endl;
}

// Delete concept from Vikram Vasudevan & Sophia You
void del(Node** &hashTable, int &size) {
  cout << "Please enter the student ID of the student you want to remove from the list." << endl;
  int intInput;
  cin >> intInput;
  cin.get();
  int index = intInput%size;
  deleteNode(hashTable[index], hashTable[index], hashTable[index], intInput);
}

// With help from Neel Madala on rehashing
void hashFunction(Node** &hashTable, int &size) {
  // Double the size of the hash table
  size *= 2;
  // Create a new hash table with double the size and fill it with NULLs;
  Node** tempHashTable = new Node* [size];
  for (int i = 0; i < size; i++) {
    tempHashTable[i] = NULL;
  }
  int newLocation;
  //  Run through every node in old hash table and copy it to the new one.
  for (int i = 0; i < size/2; i++) {
    if (hashTable[i] != NULL) {
      int index1 = (hashTable[i]->getStudent()->getID())%size;
      Node* temp1 = hashTable[i];
      if (hashTable[i]->getNext() != NULL) {
	int index2 = (hashTable[i]->getNext()->getStudent()->getID())%size;
	Node* temp2 = hashTable[i]->getNext();
	if (hashTable[i]->getNext()->getNext() != NULL) {
	  int index3 = (hashTable[i]->getNext()->getNext()->getStudent()->getID())%size;
	  Node* temp3 = hashTable[i]->getNext()->getNext();
	  temp3->setNext(NULL);
	  addTable(tempHashTable, temp3, index3, size);
	}
	temp2->setNext(NULL);
	addTable(tempHashTable, temp2, index2, size);
      }
      temp1->setNext(NULL);
      addTable(tempHashTable, temp1, index1, size);
    }
  }
  delete[] hashTable;
  // Copy new hash table into old
  hashTable = tempHashTable;
}

// Add nodes to hash table
void addTable(Node** &hashTable, Node* &inputNode, int index, int &size) {
  if (hashTable[index] == NULL) {
    hashTable[index] = inputNode;
  }
  else if (hashTable[index]->getNext() == NULL) {
    hashTable[index]->setNext(inputNode);
  }
  else if (hashTable[index]->getNext()->getNext() == NULL) {
    hashTable[index]->getNext()->setNext(inputNode);
  }
  else {
    hashFunction(hashTable, size);
  }
}

// Code from my Linked List Part 2 
void deleteNode(Node* &head, Node* cur, Node* prev, int ID) {
  // Empty list
  if (head == NULL) {
    cout << "List is empty!" << endl;
  }
  // Recurses through to the end of the list without finding a student
  else if (cur == NULL) {
    cout << "This student does not exist in the Linked List!" << endl;
  }
  // Inputted ID matches with a node
  else if (cur->getStudent()->getID() == ID) {
    // Matched node is the head and list only contains head
    if (cur == head && head->getNext() == NULL) {
      head->~Node();
      head = NULL;
    }
    // Matched node is the head and list doesn't only contain the head
    else if (cur == head) {
      Node* tempNode = head->getNext();
      head->~Node();
      head = tempNode;
    }
    // If the deleted node has a next node, change to previous node's next node to the delete node's next node
    else if (cur != head && cur->getNext() != NULL) {
      prev->setNext(cur->getNext());
      cur->~Node();
    }
    // If the deleted node doesn't have a next node 
    else if (cur != head && cur->getNext() == NULL) {
      prev->setNext(NULL);
      cur->~Node();
    }
  }
  // Recursion with current going to the next node
  else {
    deleteNode(head, cur->getNext(), cur, ID);
  }
}
