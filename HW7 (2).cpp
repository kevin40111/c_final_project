//starter for project 3
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;
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
static const string rankNames[] = {"Instructor",
                             "GradTeachingAsst",
                             "AsstProf",
                             "AssocProf",
                             "Professor",
                             "ResScientist",
                             "Dean",	//ª`·N : ­ì¥»¤Ö¤F¤@­Ó³r¸¹
                             "Unknown"};


enum Qualification{NoSchooling,HighSchool,Undergraduate,Graduate,Doctorate};
static const string qualificationLabels[] = {"NoSchooling",
											"HighSchool",
											"Undergraduate",
											"Graduate",
											"Doctorate"};

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
  Course( const string cn, long cid);              // constructor
  Course( const Course& other);                   // copy constructor
  Course& operator=( const Course& other );  // copy assignment op
  ~Course(){};                                 // destructor

  // comparison operators:
  bool operator==( const Course& other);
  bool operator!=( const Course& other);

  string getCourseName() const;
  void setCourseName( const string cn);
  long getCourseId() const;
  void setCourseId( long cid);

  friend ostream& operator<<( ostream& os, Course aCourse )
  {
    os << aCourse.courseName << "  "  << aCourse.courseId << endl;
    return os;
  }
};
Course::Course()
{
	courseName = "";
	courseId = 0;
}
Course::Course( const string cn, long cid)
{
	courseName = cn;
	courseId = cid;
}
Course::Course( const Course& other)
{
	courseName = other.courseName;
	courseId = other.courseId;
}
Course&  Course::operator=( const Course& other )
{
	if(this != &other)
	{
		courseName = other.courseName;
		courseId = other.courseId;
	}
	return *this;
}
bool Course::operator==( const Course& other)
{
	if(this == &other)
		return true;
	else
		return false;
}
bool Course::operator!=( const Course& other)
{
	if(this != &other)
		return true;
	else
		return false;
}
string Course::getCourseName() const
{
	return courseName;
}
void Course::setCourseName(const string cn)
{
	courseName = cn;
}
long Course::getCourseId() const
{
	return courseId;
}
void Course::setCourseId(long cid)
{
	courseId = cid;
}



class UniversityMember;
const short MaxRoles = 6;   //an arbitrary limit

/////////////      class Person      ///////////////

class Person
{
  string name;
  string address;
  unsigned long ssn;
  Date birthdate;

  UniversityMember* allRoles[MaxRoles];
  unsigned short roleCount;
  UniversityMember* activeRole;

public:

  Person();
  // constructor:
  Person( const string theName, unsigned long theSSN, Date theBirthDate, const string theAddress );

  // copy constructor:
  Person( const Person& other);

  // copy assignment operator:
  Person& operator=( const Person& other);

  // destructor:
  ~Person();

  bool adoptNewRole(UniversityMember* newRole);

  UniversityMember* setActiveRole(UniversityMember* thisRole);

  bool isRoleValid(const UniversityMember* thisRole) const;

  UniversityMember* getActiveRole() const;

  unsigned short getRoleCount() const;

  bool deactivateRole(UniversityMember* thisRole);

  void print();
};


Person::Person()
{
	name = "";
	address = "";
	ssn = 0;
	birthdate.d = 0;
	birthdate.m = 0;
	birthdate.y = 0;
	for(int i=0; i<MaxRoles; i++)
		allRoles[i] = 0;
	roleCount = 0;
	activeRole = 0;
}

Person::Person( const string theName, unsigned long theSSN, Date theBirthDate, const string theAddress )
{
	//initialize the roles to 0
	name = theName;
	address = theAddress;
	ssn = theSSN;
	birthdate = theBirthDate;
	for(int i=0; i<MaxRoles; i++)
		allRoles[i] = 0;
	roleCount = 0;
	activeRole = 0;
}
Person::Person( const Person& other )
{
	name = other.name;
	address = other.address;
	ssn = other.ssn;
	birthdate = other.birthdate;
	roleCount = other.roleCount;
	for(int i=0; i<roleCount; i++)
		allRoles[i] = other.allRoles[i];
	activeRole = other.activeRole;
}
Person& Person::operator=( const Person& other )
{
	if(this != &other)
	{
		name = other.name;
		address = other.address;
		ssn = other.ssn;
		birthdate = other.birthdate;
		roleCount = other.roleCount;
		for(int i=0; i<roleCount; i++)
			allRoles[i] = other.allRoles[i];
		activeRole = other.activeRole;
	}
	return *this;
}
Person::~Person()
{
	//delete [] allRoles;
}

bool Person::adoptNewRole(UniversityMember* newRole)
{
	for(int i=0; i<MaxRoles; i++)
	{
		if(allRoles[i] == 0)
		{
			allRoles[i] = newRole;
			roleCount++;
			return true;
		}
	}
	cout<<"Cannot adopt new role"<<endl;
	return false;
}

UniversityMember* Person::setActiveRole(UniversityMember* thisRole)
{
	if(thisRole != 0)
	{
		UniversityMember* oldRole = activeRole;
		activeRole = thisRole;
		return oldRole;
	}
	return 0;
}

UniversityMember* Person::getActiveRole() const
{
	return activeRole;
}


unsigned short Person::getRoleCount() const
{
	return roleCount;
}

bool Person::deactivateRole(UniversityMember* thisRole)
{
	for(int i=0; i<MaxRoles; i++)
	{
		if(allRoles[i] == thisRole)
		{
			allRoles[i] = 0;
			roleCount--;
			return true;
		}
	}
	return false;
}

///////////////    UniversityMember class    //////////////////

class UniversityMember
{
	UniversityMember* role;
	Person* ownerOfRole;
	Department department;

public:

	UniversityMember();

	UniversityMember(UniversityMember* whichRole, Person* thisPerson);

	UniversityMember(const UniversityMember& other);

	UniversityMember& operator=(const UniversityMember& other);

	virtual ~UniversityMember(){};	//virtual destructor

	bool operator==(const UniversityMember& other);

	Person* roleFor() const
	{
		return ownerOfRole;
	}

	Person* changeOwnerTo(Person* newPerson);

	Department getDepartment() const;

	void setDepartment(Department newDept);

	virtual string toString() const;

	virtual void print() const{};
};


UniversityMember::UniversityMember()
{
	role = 0;
	ownerOfRole = 0;
	department = dUnknown;
}


UniversityMember::UniversityMember(UniversityMember* whichRole, Person* thisPerson)
{
	role = whichRole;
	ownerOfRole = thisPerson;
	department = dUnknown;
}


UniversityMember::UniversityMember(const UniversityMember& other)
{
	role = other.role;
	ownerOfRole = other.ownerOfRole;
	department = other.department;
}


UniversityMember& UniversityMember::operator=(const UniversityMember& other)
{
	if(this == &other)
		return *this;

	role = other.role;
	ownerOfRole = other.ownerOfRole;
	department = other.department;

	return *this;
}

bool UniversityMember::operator==(const UniversityMember& other)
{
	cout<<"inside the overload definition of == for UniversityMember"<<endl;
	return typeid(*this) == typeid(other);
}


Person* UniversityMember::changeOwnerTo(Person* newPerson)
{
	ownerOfRole = newPerson;
	return ownerOfRole;
}


Department UniversityMember::getDepartment() const
{
	return department;
}

void UniversityMember::setDepartment(Department newDept)
{
	department = newDept;
}

string UniversityMember::toString() const
{
	return string("UniversityMember");
}
//////////////////// rest of Person definition ///////////////


bool Person::isRoleValid(const UniversityMember* thisRole) const
{
	for(int i=0; i<MaxRoles; i++)
	{
		if(allRoles[i] != 0 && *allRoles[i] == *thisRole)
			return true;
	}
	return false;
}

void Person::print()
{
	cout<<"Name: "<<name<<endl;
	cout<<"Address: "<<address<<endl;
	cout<<"ID: "<<ssn<<endl;
	cout<<"Birthdate: "<<birthdate;
	cout<<"The allowed roles for this person are: ";

	for(int i=0; i<MaxRoles; i++)
		if(allRoles[i] != 0)
			cout<<allRoles[i]->toString()<<" ";

	cout<<endl;
}




///////////////// derived class Student //////////////


const int MaxCoursesForStudent = 4;


class Student : public UniversityMember
{
  StudentStatus status;
  Course*       enrolled[ MaxCoursesForStudent ];
  int           numCourses;

public:

  Student();

  // constructor:
  Student( StudentStatus theStatus);


  // copy constructor, assignment operator, destructor:
  Student( const Student& other);
  Student& operator=( const Student& other);
  ~Student();

  void setStatus( StudentStatus aStatus );
  StudentStatus getStatus() const;


  bool enrollForCourse(const Course& aCourse);
  bool dropFromCourse(const Course& theCourse);
  void listCoursesRegisteredFor() const;

  string toString() const;
  void print() const;
};


Student::Student() : UniversityMember()
{
	status = sUnknown;

	for(int i=0;i<MaxCoursesForStudent;i++)
		enrolled[i] = 0;

	numCourses = 0;
}

Student::Student( StudentStatus theStatus)
				  : UniversityMember()
{
	status = theStatus;

	for(int i=0; i< MaxCoursesForStudent; i++)
		enrolled[i] = 0;

	numCourses = 0;
}

Student::Student( const Student& other) : UniversityMember(other)
{
	status = other.status;
	numCourses = other.numCourses;

	for(int i=0; i< MaxCoursesForStudent; i++)
		if(other.enrolled[i] != 0)
			this->enrolled[i] = new Course(*(other.enrolled[i]));

}

Student& Student::operator=( const Student& other)
{
	if(this == &other)
		return *this;

	UniversityMember::operator=(other);	//call the base assignment operator

	status = other.status;
	numCourses = other.numCourses;

	//copy the courses correctly:

	for(int i=0; i< MaxCoursesForStudent; i++)
	{
		if(this->enrolled[i] != 0 && other.enrolled[i] == 0)
			delete enrolled[i];
		else if(this->enrolled[i] == 0 && other.enrolled[i] != 0)
			this->enrolled[i] = new Course(*(other.enrolled[i]));
		else if(this->enrolled[i] != 0 && other.enrolled[i] != 0)
			*(this->enrolled[i]) = *(other.enrolled[i]);
	}
	return *this;
}

//destructor
Student::~Student()
{
	for(int i=0; i< MaxCoursesForStudent; i++)
		if(this->enrolled[i] != 0)
			delete enrolled[i];
}

void Student::setStatus( StudentStatus aStatus )
{
	status = aStatus;
}

StudentStatus Student::getStatus() const
{
	return status;
}

bool Student::enrollForCourse(const Course& aCourse)
{
	if(numCourses >= MaxCoursesForStudent)
		return false; //already enrolled too many courses

	for(int i=0; i< MaxCoursesForStudent; i++)
	{
		if(enrolled[i] == 0)
		{
			enrolled[i] = new Course(aCourse);
			numCourses++;
			return true;
		}
	}
	return false;
}

bool Student::dropFromCourse(const Course& theCourse)
{
	for(int i=0; i< MaxCoursesForStudent; i++)
	{
		if(enrolled[i] != 0)
		{
			if(*enrolled[i] == theCourse)
			{
				delete enrolled[i];	//it was dynamically allocated
				enrolled[i] = 0;
				numCourses--;
				return true;
			}
		}
	}
	return false;	//student has not registered for this course
}


void Student::listCoursesRegisteredFor() const
{
	for(int i=0; i< MaxCoursesForStudent; i++)
		if(enrolled[i] != 0)
			cout<<*enrolled[i]<<" ";
	cout<<endl;
}

string Student::toString() const
{
	return string("Student");
}

void Student::print() const
{
	cout<<"*** Informations as a Student ***"<<endl;
	cout<<"Status: "<<statusLabels[(int)status]<<endl;
	cout<<"Department: "<<departmentNames[getDepartment()]<<endl;
	cout<<"Number of courses registed: "<<numCourses<<endl;
	listCoursesRegisteredFor();
}



//////////// derived class Teacher /////////////


const int MaxCoursesForTeacher = 2;
const int MaxGraders = 2;


//////////// derived class Teacher /////////////


class Teacher : public UniversityMember {

  Rank             rank;
  double           salary;
  int              numCourses;   // num of courses taught currently
  int              numGraders;
  Course*          coursesOffered[ MaxCoursesForTeacher ];
  string*          graders[ MaxGraders ];

public:

  Teacher();
  Teacher( Rank theRank);
  Teacher( const Teacher& other );
  Teacher& operator=( const Teacher& other );
  ~Teacher(){};

  // change rank when the teacher is promoted
  void setRank( Rank newRank );
  Rank getRank() const;

  void listCoursesTaught() const;
  // offer this course
  bool ckeckoffer( const Course& aCourse );				//¥t¥~¥[ªº
  bool offerCourse( const Course& aCourse );
  // cancel this course
  bool dropoffer( const Course& theCourse );			//¥t¥~¥[ªº
  bool dropCourse( const Course& theCourse);

  bool ckeckassignGrader( const string newGrader );		//¥t¥~¥[ªº
  bool ckeckdropGrader( const string grader );			//¥t¥~¥[ªº
  bool assignGrader( const string newGrader );
  bool dropGrader( const string grader );
  void listGraders() const;

  double getSalary() const;
  void setSalary( double theSalary );

  string toString() const;
  void print() const;
};

Teacher::Teacher(): UniversityMember()
{
	rank = rUnknown;
	salary = 0;
	numCourses = 0;
	numGraders = 0;
	for(int i=0;i<MaxCoursesForTeacher;i++)
		coursesOffered[i] = NULL;
	for(int i=0;i<MaxGraders;i++)
		graders[i] = NULL;
}

Teacher::Teacher( Rank theRank) :UniversityMember()
{
	rank = theRank;
	salary = 0;
	numCourses = 0;
	numGraders = 0;
	for(int i=0;i<MaxCoursesForTeacher;i++)
		coursesOffered[i] = NULL;
	for(int i=0;i<MaxGraders;i++)
		graders[i] = NULL;
}

Teacher::Teacher( const Teacher& other) : UniversityMember(other)
{
	rank = other.rank;
	salary = other.salary;
	numCourses = other.numCourses;
	numGraders = other.numGraders;
	for(int i=0;i<numCourses;i++)
		coursesOffered[i] = other.coursesOffered[i];
	for(int i=0;i<numGraders;i++)
		graders[i] = other.graders[i];
}
Teacher& Teacher::operator=( const Teacher& other)
{
	if(this != &other)
	{
		UniversityMember::operator=(other);
		rank = other.rank;
		salary = other.salary;
		for(int i=0;i<numCourses;i++)
			delete coursesOffered[i];
		for(int i=0;i<numGraders;i++)
			delete graders[i];
		numCourses = other.numCourses;
		numGraders = other.numGraders;
		for(int i=0;i<numCourses;i++)
			coursesOffered[i] = other.coursesOffered[i];
		for(int i=0;i<numGraders;i++)
			graders[i] = other.graders[i];
	}
	return *this;
}
void Teacher::setRank( Rank newRank )
{
	rank = newRank;
}
Rank Teacher::getRank() const
{
	return rank;
}
void Teacher::listCoursesTaught() const
{
	if(numCourses == 0)
		cout<<"No course taught"<<endl;
	else
	{
		for(int i=0; i< numCourses; i++)
			cout<<"Course "<<i+1<<" : "<<*coursesOffered[i];
	}
}
bool Teacher::ckeckoffer( const Course& aCourse )
{
	if(numCourses==0)
		return true;
	for(int i=0;i<numCourses;i++)
	{
		if(coursesOffered[i]->getCourseId() == aCourse.getCourseId() &&
			coursesOffered[i]->getCourseName() == aCourse.getCourseName())
			return false;
	}
	return true;
}
bool Teacher::offerCourse( const Course& aCourse )
{
	if(ckeckoffer(aCourse)==false)
	{
		cout<<"already taught"<<endl;
		return false;
	}
	else if(numCourses>=MaxCoursesForTeacher)
	{
		cout<<"Exceed max number of coursed, not allow to teach"<<endl;
		return false;
	}
	else
	{
		coursesOffered[numCourses] = new Course(aCourse);
		numCourses++;
		return true;
	}
}
bool Teacher::dropoffer( const Course& theCourse )
{
	if(numCourses==0)
		return false;
	for(int i=0;i<numCourses;i++)
	{
		if(coursesOffered[i]->getCourseId() == theCourse.getCourseId() &&
			coursesOffered[i]->getCourseName() == theCourse.getCourseName())
			return true;
	}
	return false;
}
bool Teacher::dropCourse( const Course& theCourse )
{
	int j=MaxCoursesForTeacher;
	if(dropoffer(theCourse)==false)
	{
		cout<<"Course-> "<<theCourse<<"  has not already enrolled"<<endl;
		return false;
	}
	else
	{
		for(int i=0;i<numCourses;i++)
		{
			if(coursesOffered[i]->getCourseId() == theCourse.getCourseId()
			&& coursesOffered[i]->getCourseName() == theCourse.getCourseName())
				j=i;
		}
		for(int i=0;i<numCourses;i++)
		{
			if(i>j)
			{
				coursesOffered[i-1] = new Course(*coursesOffered[i]);
			}
		}
		coursesOffered[numCourses-1] = NULL;
		numCourses--;
		return true;
	}
}
bool Teacher::ckeckassignGrader( const string newGrader )
{
	if(numGraders==0)
		return true;
	for(int i=0;i<numGraders;i++)
	{
		if(*graders[i] == newGrader)
			return false;
	}
	return true;
}
bool Teacher::assignGrader( const string newGrader )
{
	if(ckeckassignGrader(newGrader)==false)
	{
		cout<<"already assign"<<endl;
		return false;
	}
	else if(numGraders>=MaxGraders)
	{
		cout<<"Exceed max number of grader, not allow to assign"<<endl;
		return false;
	}
	else
	{
		graders[numGraders] = new string(newGrader);
		numGraders++;
		return true;
	}
}
bool Teacher::ckeckdropGrader( const string grader )
{
	if(numGraders==0)
		return false;
	for(int i=0;i<numGraders;i++)
	{
		if(*graders[i] == grader)
			return true;
	}
	return false;
}
bool Teacher::dropGrader( const string grader )
{
	int j=MaxGraders;
	if(ckeckdropGrader(grader)==false)
	{
		cout<<"grader-> "<<grader<<"  has not already assign"<<endl;
		return false;
	}
	else
	{
		for(int i=0;i<numGraders;i++)
		{
			if(*graders[i] == grader)
				j=i;
		}
		for(int i=0;i<numGraders;i++)
		{
			if(i>j)
			{
				graders[i-1] = new string(*graders[i]);
			}
		}
		graders[numGraders-1] = NULL;
		numGraders--;
		return true;
	}
}
void Teacher::listGraders() const
{
	if(numGraders == 0)
		cout<<"No grader assigned to"<<endl;
	else
	{
		for(int i=0; i< numGraders; i++)
			cout<<"Grader "<<i+1<<" : "<<*graders[i]<<endl;
	}
}
double Teacher::getSalary() const
{
	return salary;
}
void Teacher::setSalary( double theSalary )
{
	salary = theSalary;
}
string Teacher::toString() const
{
	return string("Teacher");
}
void Teacher::print() const
{
	//¦W¤l°ÝÃD
	cout<<"*** Informations as a Teacher ***"<<endl;
	//roleFor()->print();
	cout<<"Rank = "<<rankNames[rank]<<"\nSalary = "<<salary<<"\nDepartment = "<<departmentNames[UniversityMember::getDepartment()]<<"\nNumCourses = "<<numCourses<<"\nNumGraders = "<<numGraders;
	cout<<"\nCoursesOffered = \n"<<endl;
	for(int i=0;i<numCourses;i++)
		cout<<*coursesOffered[i]<<endl;
	cout<<"Graders = "<<endl;
	for(int i=0;i<numGraders;i++)
		cout<<*graders[i]<<endl;
}

const unsigned GradCourseLevel = 400;

const unsigned MaxCoursesForGradStudent = 4;


////////// derived class GraduateStudent /////////////


class GraduateStudent : public Student {

  Teacher advisor;
  unsigned short numCourses;

public:

  //constructor:
  GraduateStudent();
  GraduateStudent( StudentStatus theStatus);

  GraduateStudent( const GraduateStudent& other );
  GraduateStudent&  operator=( const GraduateStudent& other );
  ~GraduateStudent(){};


  //need to override the following method inherited from
  //Student class because a grad students cannot enroll in
  //low-level courses
  bool enrollForCourse( const Course& aCourse );

  void changeAdvisor( const Teacher& newAdvisor );

  Teacher getAdvisor() const;

  string toString() const;
  void print() const;
};
GraduateStudent::GraduateStudent(): Student()
{
	numCourses = 0;
}
GraduateStudent::  GraduateStudent( StudentStatus theStatus)
				   : Student(theStatus)

{
	//advisor = theAdvisor;
	numCourses = 0;
}
GraduateStudent::GraduateStudent( const GraduateStudent& other ) :Student(other)
{
	advisor = other.advisor;
	numCourses = other.numCourses;
}
GraduateStudent& GraduateStudent::operator=( const GraduateStudent& other )
{
	if(this != &other)
	{
		Student::operator=(other);
		advisor = other.advisor;
		numCourses = other.numCourses;
	}
	return *this;
}
bool GraduateStudent::enrollForCourse(const Course& aCourse)
{
	if(aCourse.getCourseId() < GradCourseLevel)
	{
		cout<<"Connot regist course at this level"<<endl;
		return false;
	}
	else
	{
		Student::enrollForCourse(aCourse);
		return true;
	}
}
void GraduateStudent::changeAdvisor( const Teacher& newAdvisor )
{
	advisor = newAdvisor;
}

Teacher GraduateStudent::getAdvisor() const
{
	return advisor;
}
string GraduateStudent::toString() const
{
	return string("GraduateStudent");
}
void GraduateStudent::print() const
{
	Student::print();
	cout<<"Advisor = \n";
	advisor.print();
		//<<"¡A"<<departmentNames[advisor.getDepartment()]<<endl;
}


int main()
{
	Course c1("Parallel and Distributed Computing",5708701);
	Course c2("Application of Computational Intelligence in Engineering",5809701);
	Course c3("Systems Engineering and Reliability-based Design",5818701);
	Course c4("Computer Graphics and Visualization",5706701);
	Course c5("Seminar (1)",5901305);
	Course c6("Basic math",101);
	Course c7("Basic mechanical",302);
	Course c8("Basic calculus",110);
	Course c9("Basic physics",202);
	Course c10("Basic chemical",201);


	Person per1("Joe Johns", 012345, Date(1, 2, 1900), "Main Street, USA");

	per1.adoptNewRole(new Student(FullTime) );

	if(per1.isRoleValid( new Teacher() ) )
		cout<<"The teacher role is valid"<<endl;

	if(per1.isRoleValid( new Student() ) )
		cout<<"The student role is valid"<<endl;

	per1.setActiveRole(new Student(FullTime) );

	Student* sp = dynamic_cast<Student*>(per1.getActiveRole());

	if(sp != 0)
		cout<< "The role of the new object is Student"<<endl;

	if(typeid(*(per1.getActiveRole())) == typeid(Student) )
		cout<< "typeid test: The role of the new object is Student"<<endl;

	per1.print();
	sp->setDepartment(Engineering);
	sp->enrollForCourse(c6);
	sp->enrollForCourse(c7);
	sp->enrollForCourse(c8);
	sp->print();

	cout<<"-----------------------------------------------------------------"<<endl;

	Person per2("Jack Ronaldo", 123456, Date(4, 12, 1976), "Main Street, USA");

	per2.adoptNewRole(new Teacher(Professor));

	per2.setActiveRole(new Teacher(Professor) );

	Teacher* tp = dynamic_cast<Teacher*>(per2.getActiveRole());

	per2.print();
	tp->setDepartment(Engineering);
	tp->setSalary(20997);
	tp->assignGrader("Red");
	tp->offerCourse(c2);
	tp->offerCourse(c3);
	tp->print();

	cout<<"-----------------------------------------------------------------"<<endl;

	Person per3("Dick Check", 234567, Date(7, 6, 1989), "Main Street, USA");

	per3.adoptNewRole(new GraduateStudent(FullTime));

	per3.setActiveRole(new GraduateStudent(FullTime));

	GraduateStudent* gp = dynamic_cast<GraduateStudent*>(per3.getActiveRole());


	gp->changeAdvisor(*tp);
	gp->setDepartment(Engineering);
	gp->enrollForCourse(c1);
	gp->enrollForCourse(c2);
	gp->enrollForCourse(c3);
	per3.print();
	gp->print();

    return 0;
}
