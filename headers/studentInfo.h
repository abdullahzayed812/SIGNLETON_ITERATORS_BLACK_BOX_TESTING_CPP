#ifndef STUDENT_GRADES_INFO
#define STUDENT_GRADES_INFO

#include <iostream>
#include <vector>

using namespace std;

class StudentGradesInfo {
 private:
  string studentID;
  vector<string> coursesNames;
  vector<double> grades;
  const int MAX_GRADES_PER_COURSE = 100;

  static int statisticsTotalPrint;

  void adjustGrade(double& grade) const;

  friend class StudentGradesInfoWhiteBoxTesting;
  // friend class StudentGradesInfoPrinter;

 public:
  StudentGradesInfo(string studentID) : studentID(studentID){};

  bool addGrade(double grade, const string& courseName);
  void printAllCourses() const;
  bool getCourseGradeInfo(int pos, pair<string, double>& result) const;
  string getStudentID() const;
  int getTotalCoursesCount() const;
  pair<double, int> getTotalGradesSum() const;
  double getGrade(int pos) const;
  string getCourseName(int pos) const;
};

#endif