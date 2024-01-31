#include <iostream>
#include "node.h"


using namespace std;

// Constructor
Node::Node(Student* newStudent) {
  stu = newStudent;
  next = NULL;
}

// Destructor
Node::~Node() {
  delete stu;
  next = NULL;
}

// Getters
Node* Node::getNext() {
  return next;
}

Student* Node::getStudent() {
  return stu;
}

// Setters
void Node::setNext(Node* n) {
  next = n;
}
