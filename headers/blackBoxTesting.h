#ifndef STUDENT_GRADES_INFO_BLACK_BOX_TESTING
#define STUDENT_GRADES_INFO_BLACK_BOX_TESTING 1

class StudentGradesInfoBlackBoxTesting {
 private:
  const int MAX_GRADE_PER_COURSE = 100;

 public:
  void testGetTotalCoursesCount() const;
  void testGetTotalGradesSum() const;
  void testGetCourseGradeInfo() const;
  void testPrintAllCourses() const;
  void testAll() const;
};

#endif