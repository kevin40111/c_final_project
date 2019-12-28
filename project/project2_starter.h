/////////////     mixin classes for project 2      ///////////////


//another enum type for project 2
enum Qualification{NoSchooling,HighSchool,Undergraduate,Graduate,Doctorate};


class M_QualifiedToTeach
{
public:

  virtual void setDepartment(Department dept) = 0;
  virtual Department getDepartment() const =0;

  virtual void listCoursesQuailfuedToTeach() const =0;
  virtual double getYearOfExperience() const =0;

  virtual Qualification getHighestDegree() const = 0;  
  virtual double getSalary() const =0;
};


class M_CanBecomestudent
{
public:
  virtual void setDepartment(Department dept) = 0;
  virtual Department getDepartment() const =0;

  virtual void enrollForCourse(const Course& aCourse) = 0;
  virtual void dropFromCourse(const Course& theCourse) = 0;
  virtual void listCoursesRegisteredFor() const = 0;  

  virtual Qualification getStudentQualification() const = 0;  
};


