//starter for project 1



//////// enumerations for symbolic data members //////////


enum StudentStatus{FullTime, PartTime, Exchange, sUnknown};

static const string statusLabels[] = {"full-time","part-time",
                                      "exchange","unknown"};


enum Department{Accounting, Business, Engineering, Mathematics,
                Physics, Arts, Chemistry, dUnknown};

static const string departmentNames[] = {"Accounting",
                                         "Business",
                                         "Engineering",
                                         "Mathematics",
                                         "Physics",
                                         "Arts",
                                         "Chemistry",
                                         "Unknown"};

enum Rank {Instructor,GradTeachingAsst,AsstProf,
           AssocProf,Professor,ResScientist,Dean,rUnknown};


static string rankNames[] = {"Instructor",
                             "GradTeachingAsst",
                             "AsstProf",
                             "AssocProf",
                             "Professor",
                             "ResScientist",
                             "Dean"
                             "Unknown"};





///////////////   utility class Date   ////////////////


class Date {
public:
  int d, m, y;
  static Date today;
  Date( int dd=0, int mm=0, int yy=0 )
  {
    dd ? d = dd : today.d;
    mm ? m = mm : today.m;
    yy ? y = yy : today.y;
  }
  friend ostream& operator<<( ostream&, Date );
};

ostream& operator<<( ostream& os, Date dt )
{
  os << dt.m << "-" << dt.d << "-" << dt.y << endl;
  return os;
}


Date Date::today( 12, 25, 2003 );



/////////////     utility class Course      ///////////////


class Course{

  string courseName;
  long   courseId;

public:

  Course();                                  // no-arg constructor
  Course( const string, long );              // constructor
  Course( const Course& );                   // copy constructor
  Course& operator=( const Course& other );  // copy assignment op  
  ~Course();                                 // destructor

  // comparison operators:
  bool operator==( const Course& );
  bool operator!=( const Course& );

  string getCourseName() const;
  void setCourseName( const string );
  long getCourseId() const;
  void setCourseId( long );

  friend ostream& operator<<( ostream& os, Course aCourse )
  {
    os << aCourse.courseName << "  "  << aCourse.courseId << endl;
    return os;
  }
};


/////////////     base class Person      ///////////////

class Person{

  string name;
  string address;
  unsigned long ssn;
  Date birthdate;
  
public:
    
  Person();
  // constructor:
  Person( const string theName, unsigned long theSSN, Date theBday, const string theAddress );

  // copy constructor:
  Person( const Person& );
  
  // copy assignment operator:
  Person& operator=( const Person& );

  // destructor:
  ~Person();

  void setName( const string theName );
  string getName() const;
  void setAddress( const string theAddress );
  string getAddress() const;
  Date getBirthDate() const;
  unsigned long getIdentification() const;
  void setIdentification( unsigned long newID );
  
  virtual void print() const;
};


const int MaxCoursesForStudent = 4;


///////////////// derived class Student //////////////


class Student : virtual public Person {

  StudentStatus status;
  Department    department;
  Course*       enrolled[ MaxCoursesForStudent ];
  int           numCourses; 
  
public:

  Student();

  // constructor:
  Student( const string theName, 
           unsigned long theSSN, 
	       const Date  theBirthDate,
           const string theAddress, 
           StudentStatus theStatus,
           Department theDepartment );


  // copy constructor, assignment operator, destructor:
  Student( const Student& );
  Student& operator=( const Student& );
  ~Student();

  void setStatus( StudentStatus aStatus );
  StudentStatus getStatus() const;
  void setDepartment( Department dept );
  Department getDepartment() const;

  bool enrollForCourse(const Course& aCourse);
  bool dropFromCourse(const Course& theCourse);
  void listCoursesRegisteredFor() const;

  void print() const;
};




const int MaxCoursesForTeacher = 2;
const int MaxGraders = 2;

//////////// derived class Teacher /////////////


class Teacher : virtual public Person {
  
  Rank             rank;
  double           salary;
  Department       department;
  int              numCourses;   // num of courses taught currently
  int              numGraders;
  Course*          coursesOffered[ MaxCoursesForTeacher ];
  string*          graders[ MaxGraders ]; 
  
public:

  Teacher();
  Teacher( const string theName, long theSSN, const Date theBirthDate,
           const string theAddress, Rank theRank, Department theDepartment);
  Teacher( const Teacher& other );
  Teacher& operator=( const Teacher& other );
  ~Teacher();

  void setDepartment( Department dept );
  Department getDepartment() const;

  // change rank when the teacher is promoted
  void setRank( Rank newRank );
  Rank getRank() const;

  void listCoursesTaught() const;
  // offer this course
  bool offerCourse( const Course& aCourse );
  // cancel this course
  bool dropCourse( const Course& theCourse);

  bool assignGrader( const string newGrader );
  bool dropGrader( const string grader );
  void listGraders() const;

  double getSalary() const;
  void setSalary( double theSalary );

  void print() const;
};




const unsigned GradCourseLevel = 400;

const unsigned MaxCoursesForGradStudent = 4;


////////// derived class GraduateStudent /////////////


class GraduateStudent : public Student {
  
  Teacher advisor;
  unsigned short numCourses;

public:
  
  //constructor:
  GraduateStudent();
  GraduateStudent( const string theName,
                   unsigned long theSSN,
                   const Date theBirthDate,
                   const string theAddress,
                   StudentStatus theStatus,
                   Department theDepartment,
                   const Teacher& theAdvisor);
  
  GraduateStudent( const GraduateStudent& other );
  GraduateStudent&  operator=( const GraduateStudent& other );
  ~GraduateStudent(){}


  //need to override the following method inherited from 
  //Student class because a grad students cannot enroll in 
  //low-level courses
  bool enrollForCourse( const Course& aCourse );

  void changeAdvisor( const Teacher& newAdvisor );

  Teacher getAdvisor() const;

  void print() const;
};



//////////// derived class GradTeachAsst ///////////////


class GradTeachAsst : public GraduateStudent, public Teacher {

public:

  //constructor:
  GradTeachAsst();
  GradTeachAsst( const string theName,
                 unsigned long theSSN,
                 const Date theBirthDate,
                 const string theAddress,
                 StudentStatus theStatus,
                 Department studentDepartment,    // (A)
                 const Teacher& theAdvisor,
                 Department teachingDepartment,    // compare to A
				 Rank theRank = GradTeachingAsst);


  GradTeachAsst( const GradTeachAsst& other );
  GradTeachAsst& operator=( const GradTeachAsst& other );
  ~GradTeachAsst();

  void setStudentDepartment( Department dept );
  Department getStudentDepartment() const;
  
  void setTeachingDepartment( Department dept );
  Department getTeachingDepartment() const;
  
  // this method must be overridden because for a GradTeachAsst
  // the rank cannot be changed
  bool setRank( Rank newRank );

  // this method must be overridden because of name conflict
  // from two different bases  
  void print() const;   
};

