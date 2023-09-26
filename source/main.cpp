#include <assert.h>

#include <iostream>

#include "../headers/blackBoxTesting.h"
#include "../headers/codeExtension.h"
#include "../headers/singleton.h"
#include "../headers/studentInfo.h"
#include "../headers/whiteBoxTesting.h"

using namespace std;

/****************************************** Student Info Class ******************************************/
int StudentGradesInfo::statisticsTotalPrint = 0;

void StudentGradesInfo::adjustGrade(double& grade) const {
  if (grade < 0) grade = 0;
  if (grade > this->MAX_GRADES_PER_COURSE) grade = 100;
}

bool StudentGradesInfo::addGrade(double grade, const string& courseName) {
  adjustGrade(grade);

  for (int i = 0; i < (int)this->coursesNames.size(); i++)
    if (this->coursesNames.at(i) == courseName) return false;

  this->coursesNames.push_back(courseName);
  this->grades.push_back(grade);
  return true;
}

void StudentGradesInfo::printAllCourses() const {
  StudentGradesInfo::statisticsTotalPrint++;

  for (int i = 0; i < (int)this->coursesNames.size(); i++)
    cout << "\tCourse name: " << this->coursesNames.at(i) << " = " << this->grades.at(i) << "\n";
}

bool StudentGradesInfo::getCourseGradeInfo(int pos, pair<string, double>& result) const {
  if (pos < 0 || pos >= (int)this->grades.size()) {
    result = make_pair("", -1);
    return false;
  }

  result = make_pair(this->getCourseName(pos), this->getGrade(pos));
  return true;
}

string StudentGradesInfo::getStudentID() const { return this->studentID; }

int StudentGradesInfo::getTotalCoursesCount() const { return (int)this->coursesNames.size(); }

pair<double, int> StudentGradesInfo::getTotalGradesSum() const {
  double sum = 0;
  int total = 0;
  for (int i = 0; i < (int)this->grades.size(); i++) {
    sum += this->grades.at(i);
    total += this->MAX_GRADES_PER_COURSE;
  }
  return make_pair(sum, total);
}

double StudentGradesInfo::getGrade(int pos) const { return this->grades.at(pos); }

string StudentGradesInfo::getCourseName(int pos) const { return this->coursesNames.at(pos); }

/****************************************** Singleton Class ******************************************/

ConfigurationManger* ConfigurationManger::configMan = nullptr;

ConfigurationManger* ConfigurationManger::getInstance(const string& value) {
  // Be careful: initialize once
  if (ConfigurationManger::configMan == nullptr) {
    cout << "Creating a new ConfigurationManger\n";
    ConfigurationManger::configMan = new ConfigurationManger(value);
  }
  return ConfigurationManger::configMan;
}

void ConfigurationManger::freeInstance() {
  if (ConfigurationManger::configMan != nullptr) {
    cout << "Free the instance\n";
    delete ConfigurationManger::configMan;
    ConfigurationManger::configMan = nullptr;
  } else {
    cout << "The instance freed already\n";
  }
}

void ConfigurationManger::load() {
  if (this->isLoaded) {
    return;
  }
  // some have load.
  cout << "Laze Loading...\n";
  this->serversIPs.push_back("10.20.30.40");
  this->serversIPs.push_back("10.20.30.41");
  this->serversIPs.push_back("10.20.30.42");
  this->serversIPs.push_back("10.20.30.43");
  this->AWBServiceURL = "https://dynamodb.us-west-2";
  this->isLoaded = true;
}

string ConfigurationManger::getAWBServiceURL() {
  // Can't be make it const, because it call member function that modify
  // member data.
  this->load();
  return this->AWBServiceURL;
}

ConfigurationManger::~ConfigurationManger() {
  // Note, you shouldn't try to destroy the conf_mgr here!!!
  // The first object destroy it but others still use it (or will reload)!

  // FreeInstance();	// if you uncommented = infinite loop. WHY? Answer is
  // below very bottom

  // Quote: Don’t create problems to solve a problem
}

void f1() {
  ConfigurationManger* mgr = ConfigurationManger::getInstance("/home/abdullah/config.txt");
  cout << mgr->getAWBServiceURL() << "\n";
}

void f2() {
  ConfigurationManger* mgr = ConfigurationManger::getInstance("/home/abdullah/config.txt");
  cout << mgr->getAWBServiceURL() << "\n";
}

/****************************************** Black Box Testing Class ******************************************/

void StudentGradesInfoBlackBoxTesting::testGetTotalCoursesCount() const {
  cout << __func__ << "\n";

  StudentGradesInfo st1("S000123");
  assert(st1.getTotalCoursesCount() == 0);

  st1.addGrade(70, "Math");
  st1.addGrade(70, "programming 1");
  st1.addGrade(85, "programming 2");
  assert(st1.getTotalCoursesCount() == 3);

  st1.addGrade(75, "programming 2");
  st1.addGrade(65, "programming 2");
  st1.addGrade(95, "programming 2");
  assert(st1.getTotalCoursesCount() == 3);

  assert(st1.getStudentID() == "S000123");
}

void StudentGradesInfoBlackBoxTesting::testGetTotalGradesSum() const {
  cout << __func__ << "\n";
  pair<double, int> p;

  StudentGradesInfo st1("S000123");
  p = st1.getTotalGradesSum();
  assert(p.first == 0);
  assert(p.second == 0);

  st1.addGrade(200, "Math");
  p = st1.getTotalGradesSum();
  assert(p.first == this->MAX_GRADE_PER_COURSE);
  assert(p.second == this->MAX_GRADE_PER_COURSE);

  st1.addGrade(70, "Programming 1");
  p = st1.getTotalGradesSum();
  assert(p.first == 70 + this->MAX_GRADE_PER_COURSE);
  assert(p.second == 2 * this->MAX_GRADE_PER_COURSE);

  st1.addGrade(60, "Programming 1");
  p = st1.getTotalGradesSum();
  assert(p.first == 70 + this->MAX_GRADE_PER_COURSE);
  assert(p.second == 2 * this->MAX_GRADE_PER_COURSE);

  st1.addGrade(80, "Programming 1");
  p = st1.getTotalGradesSum();
  assert(p.first == 70 + this->MAX_GRADE_PER_COURSE);
  assert(p.second == 2 * this->MAX_GRADE_PER_COURSE);

  st1.addGrade(85, "OOP");
  p = st1.getTotalGradesSum();
  assert(p.first == 70 + 85 + this->MAX_GRADE_PER_COURSE);
  assert(p.second == 3 * this->MAX_GRADE_PER_COURSE);

  if (false) {
    // This will fail. We should handle the code to not be case sensetive!
    st1.addGrade(85, "PROGramming 2");
    p = st1.getTotalGradesSum();
    assert(p.first == 85 + 70 + MAX_GRADE_PER_COURSE);
    assert(p.second == 3 * MAX_GRADE_PER_COURSE);
  }
}

void StudentGradesInfoBlackBoxTesting::testGetCourseGradeInfo() const {
  cout << __func__ << "\n";
  pair<string, double> p;

  StudentGradesInfo st1("S000123");
  bool res = st1.getCourseGradeInfo(-1, p);
  assert(!res);
  assert(p.first == "");
  assert(p.second == -1);

  res = st1.getCourseGradeInfo(3, p);
  assert(!res);
  assert(p.first == "");
  assert(p.second == -1);

  st1.addGrade(80, "Programming 1");
  res = st1.getCourseGradeInfo(0, p);
  assert(res);
  assert(p.first == "Programming 1");
  assert(p.second == 80);
}

void StudentGradesInfoBlackBoxTesting::testPrintAllCourses() const {
  cout << __func__ << "\n";
  // This function is writing to console! How to test?
  // 1) use Freopen to direct output to file
  // 2) read file content
  // 3) compare to what you expect!
}

void StudentGradesInfoBlackBoxTesting::testAll() const {
  this->testGetCourseGradeInfo();
  this->testGetTotalCoursesCount();
  this->testGetTotalGradesSum();
  this->testPrintAllCourses();
}

/****************************************** White Box Testing Class ******************************************/

void StudentGradesInfoWhiteBoxTesting::testStatisticsTotalPrint(StudentGradesInfo& student) const {
  cout << __func__ << "\n";

  StudentGradesInfo st1("S000123");
  StudentGradesInfo st2("S030012");
  assert(st1.statisticsTotalPrint == 0);

  st1.printAllCourses();
  assert(StudentGradesInfo::statisticsTotalPrint == 1);

  st1.printAllCourses();
  assert(StudentGradesInfo::statisticsTotalPrint == 2);

  st2.printAllCourses();
  assert(StudentGradesInfo::statisticsTotalPrint == 3);
}

void StudentGradesInfoWhiteBoxTesting::testAdjustGrade() const {
  cout << __func__ << "\n";

  StudentGradesInfo st1("S000123");
  double grade1 = -30;
  double grade2 = 120;

  st1.adjustGrade(grade1);
  st1.adjustGrade(grade2);
  assert(grade1 == 0);
  assert(grade2 == 100);
}

void StudentGradesInfoWhiteBoxTesting::testAddGrade() const {
  cout << __func__ << "\n";

  StudentGradesInfo st1("S000123");

  st1.addGrade(80, "Programming 1");
  assert(st1.coursesNames.size() == 1);
  assert(st1.grades.size() == 1);

  st1.addGrade(85, "oop");
  assert(st1.coursesNames.size() == 2);
  assert(st1.grades.size() == 2);

  st1.addGrade(80, "oop");
  assert(st1.coursesNames.size() == 2);
  assert(st1.grades.size() == 2);

  assert(st1.coursesNames.back() == "oop");
}

/****************************************** Code Extension Class ******************************************/

StudentGradesInfoPrinter::StudentGradesInfoPrinter(const StudentGradesInfo& studentInfo) : studentInfo(studentInfo) {}

void StudentGradesInfoPrinter::resetIterator() { this->currentCoursePos = 0; }

bool StudentGradesInfoPrinter::hasNext() const {
  // just make sure still smaller position
  return this->currentCoursePos < this->studentInfo.getTotalCoursesCount();
}

pair<string, double> StudentGradesInfoPrinter::getNext() {
  pair<string, double> result;
  this->studentInfo.getCourseGradeInfo(this->currentCoursePos++, result);
  return result;
}

StudentGradesInfoPrinter::~StudentGradesInfoPrinter() {}

int main() {
  // f1();
  // f2();

  // If we forgot to free, it will be memory leak!
  // We need more elegant solutions!
  // ConfigurationManger::freeInstance();

  // StudentGradesInfo st1("1004");
  // st1.addGrade(85, "C++");
  // st1.addGrade(75, "Data Structures");
  // st1.addGrade(90, "Algorithms");

  // pair<string, double> result;
  // st1.getCourseGradeInfo(1, result);
  // cout << "Course name: " << result.first << " Grade: " << result.second << "\n";

  // pair<double, int> p = st1.getTotalGradesSum();
  // cout << p.first << " / " << p.second << "\n";

  // st1.printAllCourses();

  // StudentGradesInfoBlackBoxTesting().testAll();

  // StudentGradesInfo st1("S0001");

  // StudentGradesInfoWhiteBoxTesting().testAddGrade();

  StudentGradesInfo st1("S000123");
  StudentGradesInfoPrinter printer(st1);

  st1.addGrade(70, "Math");
  st1.addGrade(80, "Programming 1");
  st1.addGrade(90, "OOP");

  int limit = 3;
  cout << "Printing top " << limit << " grades if available\n";
  while (limit-- && printer.hasNext()) {
    pair<string, double> result = printer.getNext();
    cout << "\t" << result.first << " = " << result.second << "\n";
  }

  st1.addGrade(70, "Algorithms");
  st1.addGrade(67, "programming 2");

  printer.resetIterator();
  limit = 3;

  cout << "Printing top " << limit << " grades if available\n";
  while (limit-- && printer.hasNext()) {
    pair<string, double> result = printer.getNext();
    cout << "\t" << result.first << " = " << result.second << "\n";
  }

  return 0;
}

// Because destructor calls destructor  calls destructor   to infinity
// How
// Scope of an object ended, so it calls ~ConfigurationManger(), which calls
// FreeInstance() FreeInstance does: delete ConfigurationManger::conf_mgr;  =>
// which is calling the destructor! Which repeat the same! Hell :)