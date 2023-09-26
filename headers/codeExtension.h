#ifndef CODE_EXTENSION
#define CODE_EXTENSION 1

#include "./studentInfo.h"

class StudentGradesInfoPrinter {
 private:
  const StudentGradesInfo& studentInfo;
  int currentCoursePos = 0;

 public:
  // Make it object by reference to feel updates. Const to never change its content as printer
  StudentGradesInfoPrinter(const StudentGradesInfo& studentInfo);

  void resetIterator();
  bool hasNext() const;
  pair<string, double> getNext();

  ~StudentGradesInfoPrinter();
};

#endif

/*

You just learned 2 things:

1- Open–closed principle
"Software entities ... should be open for extension, but closed for modification."
We managed to extend the functionality of the class to ore controlled printing. We did not need to change original code

2- Iterator Design Pattern
- HasNext / GetNext is a general strategy to allow iterating on something
- STL has iterators on several containers

*/