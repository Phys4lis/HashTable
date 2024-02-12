/* 
 *
 *
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


int main() {
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
  ifstream firstNames("firstNames.txt");
  char firstName[20];
  for (int i = 0; i < 25; i++) {
    firstNames.getline(firstName, 20);
    strcpy(firstNamesArr[i], firstName);
  }
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
      else if (option == 2) {
	Student *randStudent = new Student();
	addRandom(firstNamesArr, lastNamesArr, randStudent, studentList, hashTable, size);
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
  bool hashing = true;
  while (hashing == true) {
    int location = (inputNode->getStudent()->getID())%size;
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

void addRandom(char** firstNamesArr, char** lastNamesArr, Student* &randStudent, vector<Student*> &v, Node** &hashTable, int&size) {
  cout << endl << "How many students would you like to add? " << endl;
  int studentNum;
  cin >> studentNum;
  cin.get();
  for (int i = 0; i < studentNum; i++) {
    int randFirst = rand() % 24;
    int randLast = rand() % 24;
    strcpy(randStudent->firstName, firstNamesArr[randFirst]);
    cout << "first name: " << firstNamesArr[randFirst] << endl;
    strcpy(randStudent->lastName, lastNamesArr[randLast]);
    cout << "last name: " << lastNamesArr[randLast] << endl;;
    int randStudentID = 0;
    int temp = 0;
    bool correctID = false;
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
    while (hashing2 == true) {
      int location2 = (randomNode->getStudent()->getID())%size;
      if (hashTable[location2] == NULL) {
	cout << "first2" << endl;
	cout << "huh" << endl;
	cout << randStudent->getLastName();
	cout << "hi " << randomNode->getStudent()->getLastName();
	hashTable[location2] = randomNode;
	hashing2 = false;
      }
      else if (hashTable[location2]->getNext() == NULL) {
	cout << "second" << endl;
	hashTable[location2]->setNext(randomNode);
	hashing2 = false;
      }
      else if (hashTable[location2]->getNext()->getNext() == NULL) {
	cout << "third" << endl;
	(hashTable[location2]->getNext())->setNext(randomNode);
	hashing2 = false;
      }
      else {
	hashFunction(hashTable, size);
      }
    }
  }
}

void print(Node** &hashTable, int &size) {
  for (int i = 0; i < size; i++) {
    if (hashTable[i] != NULL) {
      cout << hashTable[i]->getStudent()->getFirstName() << " " << hashTable[i]->getStudent()->getLastName() << ", " << hashTable[i]->getStudent()->getID() << " " << hashTable[i]->getStudent()->getGPA() << endl;
      if (hashTable[i]->getNext() != NULL) {
	cout << hashTable[i]->getNext()->getStudent()->getFirstName() << " " << hashTable[i]->getNext()->getStudent()->getLastName() << ", " << hashTable[i]->getNext()->getStudent()->getID() << " " << hashTable[i]->getNext()->getStudent()->getGPA() << endl;
	if (hashTable[i]->getNext()->getNext() != NULL) {
	  cout << hashTable[i]->getNext()->getNext()->getStudent()->getFirstName() << " " << hashTable[i]->getNext()->getNext()->getStudent()->getLastName() << ", " << hashTable[i]->getNext()->getNext()->getStudent()->getID() << " " << hashTable[i]->getNext()->getNext()->getStudent()->getGPA() << endl;
	}
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

// With help from Neel Madala on rehashing
void hashFunction(Node** &hashTable, int &size) {
  size *= 2;
  Node** tempHashTable = new Node* [size];
  for (int i = 0; i < size; i++) {
    tempHashTable[i] = NULL;
  }
  int newLocation;
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
	cout << "does b add" << endl;
	addTable(tempHashTable, temp2, index2, size);
      }
      temp1->setNext(NULL);
      addTable(tempHashTable, temp1, index1, size);
    }
  }
  delete[] hashTable;
  hashTable = tempHashTable;
}


void addTable(Node** &hashTable, Node* &inputNode, int index, int &size) {
  if (hashTable[index] == NULL) {
    cout << "adding 1" << inputNode->getStudent()->getFirstName() << endl;
    hashTable[index] = inputNode;
  }
  else if (hashTable[index]->getNext() == NULL) {
    cout << "adding 2" << inputNode->getStudent()->getFirstName() << endl;
    hashTable[index]->setNext(inputNode);
  }
  else if (hashTable[index]->getNext()->getNext() == NULL) {
    hashTable[index]->getNext()->setNext(inputNode);
  }
  else {
    hashFunction(hashTable, size);
  }
}
