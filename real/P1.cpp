#include <iostream>
#include <string.h>
#include <typeinfo>
using namespace std;


enum StudentStatus{FullTime, PartTime, Exchange, sUnknown};

static const string statusLabels[] = {"full-time", "part-time", "exchange", "unknown"};


enum Department{Accounting, Business, Engineering, Mathematics, Physics, Arts, Chemistry, dUnknown};

static const string departmentNames[] = {
	"Accounting",
	"Business",
	"Engineering",
	"Mathematics",
	"Physics",
	"Arts",
	"Chemistry",
	"Unknown"
};

enum Rank {Instructor,GradTeachingAsst,AsstProf, AssocProf,Professor,ResScientist,Dean,rUnknown};

static const string rankNames[] = {
	"Instructor",
	"GradTeachingAsst",
	"AsstProf",
	"AssocProf",
	"Professor",
	"ResScientist",
	"Dean",
	"Unknown"
};

class Date {

public:
	int d, m, y;
	static Date today;

	Date( int dd=0, int mm=0, int yy=0 ){
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


class Course {

  	string courseName;
  	long   courseId;

public:

  	Course();                                  // no-arg constructor
  	Course( const string cn, long cid);              // constructor
  	Course( const Course& other);                   // copy constructor
  	Course& operator=( const Course& other );  // copy assignment op
  	~Course(){};                                 // destructor


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

class Person {
  string name;
  string address;
  unsigned long ssn;
  Date birthdate;

public:
  Person();
  Person( const string theName, unsigned long theSSN, Date theBday, const string theAddress );
  Person( const Person& other);
  Person& operator=( const Person& other);
  ~Person(){};
  void setName( const string theName );
  string getName() const;
  void setAddress( const string theAddress );
  string getAddress() const;
  Date getBirthDate() const;
  unsigned long getIdentification() const;
  void setIdentification( unsigned long newID );
  virtual void print() const;
};

Person::Person()
{
	name = "";
	address = "";
	ssn = 0;
	birthdate.d = 0;
	birthdate.m = 0;
	birthdate.y = 0;
}

Person::Person( const string theName, unsigned long theSSN, Date theBday, const string theAddress )
{
	name = theName;
	address = theAddress;
	ssn = theSSN;
	birthdate.d = theBday.d;
	birthdate.m = theBday.m;
	birthdate.y = theBday.y;
}

Person::Person( const Person& other)
{
	name = other.name;
	address = other.address;
	ssn = other.ssn;
	birthdate.d = other.birthdate.d;
	birthdate.m = other.birthdate.m;
	birthdate.y = other.birthdate.y;
}

Person& Person::operator=( const Person& other)
{
	if( this != &other)
	{
		name = other.name;
		address = other.address;
		ssn = other.ssn;
		birthdate.d = other.birthdate.d;
		birthdate.m = other.birthdate.m;
		birthdate.y = other.birthdate.y;
	}
	return *this;
}

void Person::setName( const string theName )
{
	name = theName;
}

string Person::getName() const
{
	return name;
}

void Person::setAddress( const string theAddress )
{
	address = theAddress;
}

string Person::getAddress() const
{
	return address;
}

Date Person::getBirthDate() const
{
	return birthdate;
}

unsigned long Person::getIdentification() const
{
	return ssn;
}

void Person::setIdentification( unsigned long newID )
{
	ssn = newID;
}

void Person::print() const
{
	cout<<"Name = "<<name<< endl;
	cout<<"Address = "<<address<<endl;
	cout<<"SSN = "<<ssn<< endl;
	cout<<"Birthdate = "<<birthdate;
}

const int MaxCoursesForStudent = 4;

class Student : virtual public Person {

  	StudentStatus status;
  	Department    department;
  	Course*       enrolled[ MaxCoursesForStudent ];
  	int           numCourses;

public:
  	Student();
  	Student (
  		const string theName,
   		unsigned long theSSN,
	    const Date  theBirthDate,
        const string theAddress,
        StudentStatus theStatus,
        Department theDepartment
	);
  Student( const Student& other);
  Student& operator=( const Student& other);
  ~Student(){};
  void setStatus( StudentStatus aStatus );
  StudentStatus getStatus() const;
  void setDepartment( Department dept );
  Department getDepartment() const;
  bool checkenrolled(const Course& aCourse);	//另外加的
  bool dropenrolled(const Course& aCourse);		//另外加的
  bool enrollForCourse(const Course& aCourse);
  bool dropFromCourse(const Course& theCourse);
  void listCoursesRegisteredFor() const;
  void print() const;
};

Student::Student() : Person() {
	status = sUnknown;
	department = dUnknown;
	for(int i=0;i<MaxCoursesForStudent;i++)
		enrolled[i] = NULL;
	numCourses = 0;
}

Student:: Student( const string theName,unsigned long theSSN,const Date  theBirthDate,const string theAddress,StudentStatus theStatus,Department theDepartment ) : Person(theName,theSSN,theBirthDate,theAddress) {
	status = theStatus;
	department = theDepartment;
	for(int i=0;i<MaxCoursesForStudent;i++)
		enrolled[i] = NULL;
	numCourses = 0;
}

Student::Student( const Student& other) : Person(other) {
	status = other.status;
	department = other.department;
	numCourses = other.numCourses;
	for(int i=0;i<numCourses;i++)
	{
		enrolled[i] = new Course();
		enrolled[i]->setCourseId(other.enrolled[i]->getCourseId());
		enrolled[i]->setCourseName(other.enrolled[i]->getCourseName());
	}
}

Student& Student::operator=( const Student& other) {
	if(this != &other)
	{
		Person::operator=(other);
		status = other.status;
		department = other.department;
		for(int i=0;i<numCourses;i++)
			delete enrolled[i];
		numCourses = other.numCourses;
		for(int i=0;i<numCourses;i++)
		{
			enrolled[i] = new Course();
			enrolled[i]->setCourseId(other.enrolled[i]->getCourseId());
			enrolled[i]->setCourseName(other.enrolled[i]->getCourseName());
		}
	}
	return *this;
}

void Student::setStatus( StudentStatus aStatus )
{
	status=aStatus;
}

StudentStatus Student::getStatus() const
{
	return status;
}

void Student::setDepartment( Department dept )
{
	department = dept;
}

Department Student::getDepartment() const
{
	return department;
}

bool Student::checkenrolled(const Course& aCourse)
{
	if(numCourses==0)
		return true;
	for(int i=0;i<numCourses;i++)
	{
		if(enrolled[i]->getCourseId() == aCourse.getCourseId()
			&& enrolled[i]->getCourseName() == aCourse.getCourseName())
			return false;
	}
	return true;
}

bool Student::dropenrolled(const Course& aCourse)
{
	if(numCourses==0)
		return false;
	for(int i=0;i<numCourses;i++)
	{
		if(enrolled[i]->getCourseId() == aCourse.getCourseId()
			&& enrolled[i]->getCourseName() == aCourse.getCourseName())
			return true;
	}
	return false;
}

bool Student::enrollForCourse(const Course& aCourse)
{
	if(checkenrolled(aCourse)==false)
	{
		cout<<"Course-> "<< aCourse <<"  has already enrolled"<<endl;
		return false;
	}
	else if(numCourses>=MaxCoursesForStudent)
	{
		cout<< "Exceed max number of coursed, not allow to regist" <<endl;
		return false;
	}
	else
	{
		enrolled[numCourses] = new Course(aCourse);
		numCourses++;
		return true;
	}
}

bool Student::dropFromCourse(const Course& theCourse)
{
	int j=MaxCoursesForStudent;
	if(dropenrolled(theCourse)==false)
	{
		cout<<"Course-> "<<theCourse<<"  has not already enrolled"<<endl;
		return false;
	}
	else
	{
		for(int i=0;i<numCourses;i++)
		{
			if(enrolled[i]->getCourseId() == theCourse.getCourseId()
			&& enrolled[i]->getCourseName() == theCourse.getCourseName())
				j=i;
		}
		for(int i=0;i<numCourses;i++)
		{
			if(i>j)
			{
				enrolled[i-1] = new Course(*enrolled[i]);
			}
		}
		enrolled[numCourses-1] = NULL;
		numCourses--;
		return true;
	}
}

void Student::listCoursesRegisteredFor() const
{
	if(numCourses == 0)
		cout<<"No course registed"<<endl;
	else
	{
		for(int i=0; i< numCourses; i++)
			cout<<"Course "<<i+1<<" : "<<*enrolled[i];
	}
}

void Student::print() const
{
	Person::print();
	cout<<"Status = "<<statusLabels[status]<< endl;
	cout <<"Department = "<<departmentNames[department]<< endl;
	cout <<"NumCoursse = "<<numCourses<< endl;
	cout <<"Enrolled = ";
	for(int i=0;i<numCourses;i++)
	{
		cout<<*enrolled[i]<<endl;
	}

	cout<<endl;
}


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
  ~Teacher(){};

  void setDepartment( Department dept );
  Department getDepartment() const;
  void setRank( Rank newRank );
  Rank getRank() const;
  void listCoursesTaught() const;
  bool ckeckoffer( const Course& aCourse );
  bool offerCourse( const Course& aCourse );
  bool dropoffer( const Course& theCourse );
  bool dropCourse( const Course& theCourse);
  bool ckeckassignGrader( const string newGrader );
  bool ckeckdropGrader( const string grader );
  bool assignGrader( const string newGrader );
  bool dropGrader( const string grader );
  void listGraders() const;

  double getSalary() const;
  void setSalary( double theSalary );

  void print() const;
};

Teacher::Teacher():Person()
{
	rank = rUnknown;
	salary = 0;
	department = dUnknown;
	numCourses = 0;
	numGraders = 0;
	for(int i=0;i<MaxCoursesForTeacher;i++)
		coursesOffered[i] = NULL;
	for(int i=0;i<MaxGraders;i++)
		graders[i] = NULL;
}

Teacher::Teacher(
	const string theName, long theSSN, const Date theBirthDate,
	const string theAddress, Rank theRank, Department theDepartment) :Person(theName,theSSN,theBirthDate,theAddress) {

		rank = theRank;
		department = theDepartment;
		salary = 0;
		numCourses = 0;
		numGraders = 0;
		for(int i=0;i<MaxCoursesForTeacher;i++)
			coursesOffered[i] = NULL;
		for(int i=0;i<MaxGraders;i++)
			graders[i] = NULL;
}

Teacher::Teacher( const Teacher& other) : Person(other)
{
	rank = other.rank;
	department = other.department;
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
		Person::operator=(other);
		rank = other.rank;
		department = other.department;
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

void Teacher::setDepartment( Department dept )
{
	department = dept;
}

Department Teacher::getDepartment() const
{
	return department;
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

void Teacher::print() const
{
	Person::print();
	cout<<"Rank = "<<rankNames[rank] << endl;
	cout<<"Salary = "<<salary<< endl;
	cout<<"Department = "<<departmentNames[department] << endl;
	cout<<"NumCourses = "<< numCourses<< endl;
	cout<< "NumGraders = "<< numGraders<<endl;
	cout<<"CoursesOffered = "<<endl;

	for(int i=0;i<numCourses;i++)
		cout<<*coursesOffered[i]<<endl;

	cout<<"Graders = "<<endl;
	for(int i=0;i<numGraders;i++)
		cout<<*graders[i]<<endl;
}

const unsigned GradCourseLevel = 400;

const unsigned MaxCoursesForGradStudent = 4;

class GraduateStudent : public Student {

  Teacher advisor;
  unsigned short numCourses;

public:
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
  ~GraduateStudent(){};

  bool enrollForCourse( const Course& aCourse );

  void changeAdvisor( const Teacher& newAdvisor );

  Teacher getAdvisor() const;

  void print() const;
};

GraduateStudent::GraduateStudent(): Student(),Person()
{
	numCourses = 0;
}

GraduateStudent::  GraduateStudent( const string theName,unsigned long theSSN,const Date theBirthDate,const string theAddress,
                   StudentStatus theStatus,Department theDepartment,const Teacher& theAdvisor)
				   : Student(theName,theSSN,theBirthDate,theAddress,theStatus,theDepartment)
				   , Person(theName,theSSN,theBirthDate,theAddress)
{
	advisor = theAdvisor;
	numCourses = 0;
}

GraduateStudent::GraduateStudent( const GraduateStudent& other ) :Student(other),Person(other)
{
	advisor = other.advisor;
	numCourses = other.numCourses;
}

GraduateStudent& GraduateStudent::operator=( const GraduateStudent& other )
{
	if(this != &other)
	{
		Student::operator=(other);
		Person::operator=(other);

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

void GraduateStudent::print() const
{
	Student::print();
	cout<<"Advisor : " << endl;
	cout<<"Name " << advisor.getName() << endl;
	cout<<"Identification "<< advisor.getIdentification()<<endl;
	cout<<"rankName "<< rankNames[advisor.getRank()]<<endl;
	cout<<"Deparment " << departmentNames[advisor.getDepartment()]<<endl;
}

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
  ~GradTeachAsst(){};

  void setStudentDepartment( Department dept );
  Department getStudentDepartment() const;

  void setTeachingDepartment( Department dept );
  Department getTeachingDepartment() const;

  bool setRank( Rank newRank );
  void print() const;

};
GradTeachAsst::GradTeachAsst():GraduateStudent(),Teacher(),Person() {}

GradTeachAsst::GradTeachAsst(const string theName,unsigned long theSSN,const Date theBirthDate,const string theAddress,
							 StudentStatus theStatus,Department studentDepartment,const Teacher& theAdvisor,
							 Department teachingDepartment,Rank theRank)
							 :GraduateStudent(theName,theSSN,theBirthDate,theAddress,theStatus,studentDepartment,theAdvisor)
							 ,Teacher(theName,theSSN,theBirthDate,theAddress,theRank,teachingDepartment)
							 ,Person(theName,theSSN,theBirthDate,theAddress)
							 {}

GradTeachAsst::GradTeachAsst( const GradTeachAsst& other ) : GraduateStudent(other),Teacher(other),Person(other) {}

GradTeachAsst& GradTeachAsst::operator=( const GradTeachAsst& other )
{
	if(this != &other)
	{
		GraduateStudent::operator=(other);
		Teacher::operator=(other);
		Person::operator=(other);
	}
	return *this;
}

void GradTeachAsst::setStudentDepartment( Department dept )
{
	Student::setDepartment(dept);
}

Department GradTeachAsst::getStudentDepartment() const
{
	return Student::getDepartment();
}

void GradTeachAsst::setTeachingDepartment( Department dept )
{
	Teacher::setDepartment(dept);
}

Department GradTeachAsst::getTeachingDepartment() const
{
	return Teacher::getDepartment();
}

bool GradTeachAsst::setRank( Rank newRank )
{
	if(newRank != GradTeachingAsst)
	{
		cout<<"Can't assign this rank"<<endl;
		return false;
	}
	if(getRank() != GradTeachingAsst)
	{
		setRank(GradTeachingAsst);
		return true;
	}
	return true;
}

void GradTeachAsst::print() const
{
	Person::print();
	cout<<"StudentStatus = "<<statusLabels[getStatus()]<<endl;
	cout<<"StudentDepartment = "<<departmentNames[getStudentDepartment()]<<endl;
	cout<<"Courses registered = "<<endl;
	listCoursesRegisteredFor();
	cout<<"TeachingRank = "<<rankNames[Teacher::getRank()]<<endl;
	cout<<"TeachingDepartment = "<<departmentNames[getTeachingDepartment()]<<endl;
	cout<<"Salary = "<<getSalary()<<endl;
	cout<<"Courses taught = "<<endl;
	listCoursesTaught();
	cout<<"Graders = "<<endl;
	listGraders();
	cout<<endl;
}



int main()
{
	Course c1("Parallel and Distributed Computing",1000000);
	Course c2("Application of Computational Intelligence in Engineering",1002000);


	cout<<"-------------------Student-------------------"<<endl;
	Date birthdayFors1(15,6,1996);
	Student s1("Kenny",77598,birthdayFors1,"NTUST",FullTime,Engineering);
	s1.print();

	cout<<"-------------------Teacher-------------------"<<endl;
	Date birthdayFort1(28,9,1985);
	Teacher t1("Garry",1001,birthdayFort1,"NTUST",Professor,Engineering);
	t1.setSalary(75000);
	t1.print();
	t1.offerCourse(c1);
	t1.assignGrader("Kevin");
	cout<<"  < offerCourse BassignGrader , then show result >"<<endl;
	t1.listCoursesTaught();
	t1.listGraders();

	cout<<"-------------------GraduateStudent-------------------"<<endl;
	Date birthdayForg1(5,6,1997);
	GraduateStudent g1("Jack",99581,birthdayForg1,"NTUST",FullTime,Engineering,t1);
	g1.enrollForCourse(c1);
	g1.enrollForCourse(c2);
	g1.print();

	cout<<"-------------------GradTeachAsst-------------------"<<endl;
	Date birthdayForgta1(20,11,1962);
	GradTeachAsst gta1("Eason",9527,birthdayForgta1,"NTUST",FullTime,Engineering,t1,Engineering);
	gta1.enrollForCourse(c1);
	gta1.offerCourse(c2);
	gta1.setSalary(22000);
	gta1.print();


    cout<<"-------------------Polymorphism-------------------"<<endl;
    Person* ptr2[4] = {&s1 , &t1, &g1, &gta1};
	for(int i=0;i<4;i++)
	{
		ptr2[i]->print();
		cout<<"-------------------------"<<endl;
	}

	return 0;
}
