#ifndef EMPLOYEE
#define EMPLOYEE

#include <iostream>

using namespace std;

class Employee {
 private:
  string name;

 public:
  static int x;
  Employee(string name);
  ~Employee();
};

#endif