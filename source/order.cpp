#include "../headers/order.h"

#include <iostream>

using namespace std;

/*
  1- Why c++ doesn't allow creating const static member function?
    - Using const means no changes for member data, but changes to what?!
    - Because static member shared between all objects.

  2- Why c++ doesn't allow this pointer to access a static member data?
    -  A static object is shared among all objects and doesn't have its own data
  members So this invalidate the use of this pointer
*/

int Employee::x = 10;

Employee::Employee(string name) : name(name) { cout << "Constructor " << this->name << "\n"; }
Employee::~Employee() { cout << "Destructor " << this->name << "\n"; }

int main() {
  static Employee belal("Belal");
  Employee most("Mostafa");
  most.x = 100;
  cout << most.x << "\n";
  if (true) {
    Employee("Mona");
  }
  static Employee asmaa("Asmaa");

  return 0;
}

/*
  Constructor Belal
  Constructor Mostafa
  Constructor Mona
  Destructor Mona
  Constructor Asmaa
  Destructor Mostafa
  Destructor Asmaa
  Destructor Belal

  Constructor's call are the easy part.

  For destructor, Think in the object's life time
  - Static object ends ONLY with the end of the program.
  - So every static member ends only after complete end of program life time
    - If there are more than static, destruction in reverse order

  - For local objects, once its scope is done
          - Notice mona's scope ends after the if, but most ends after return 0
*/