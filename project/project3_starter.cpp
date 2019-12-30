//starter for project 3


/////////////      class Person      ///////////////
#include <iostream>
#include <string.h>
#include <typeinfo>
using namespace std;

class UniversityMember;
class Student;

enum Department{Accounting, Business, Engineering, Mathematics, Physics, Arts, Chemistry, dUnknown};
enum StudentStatus{FullTime, PartTime, Exchange, sUnknown};
enum Rank {Instructor, GradTeachingAsst, AsstProf, AssocProf, Professor, ResScientist, Dean, rUnknown};
const short MaxRoles = 6;   //an arbitrary limit
static const string statusLabels[] = {"full-time", "part-time", "exchange", "unknown"};
static const string departmentNames[] = {"Accounting", "Business", "Engineering", "Mathematics", "Physics", "Arts", "Chemistry", "Unknown"};

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


class Course {

private:
    string courseName;
    long   courseId;

public:
    Course() {}

    Course( const string name, long courseId){
        this->courseName = name;
        this->courseId = courseId;
    }

    Course( const Course& other) {
        this->courseName = other.courseName;
        this->courseId = other.courseId;
    };

    Course& operator=( const Course& other );
    ~Course() {};

    // comparison operators:
    bool operator==( const Course& );
    bool operator!=( const Course& );

    string getCourseName() const {
        return this->courseName;
    }
    void setCourseName( const string );
    long getCourseId() const;
    void setCourseId( long );

    friend ostream& operator << ( ostream& os, Course aCourse );
};

ostream &operator<<(ostream &os, Course aCourse) {
    os << aCourse.courseName << "  "  << aCourse.courseId << endl;
    return os;
}

class Person
{
private:
    string name;
    unsigned long ssn;
    string address;
    Date birthdate;
    UniversityMember* allRoles[MaxRoles];
    unsigned short roleCount;
    UniversityMember* activeRole;
public:

    Person() {

    }

    Person( const string theName, unsigned long theSSN, Date theBirthDate, const string theAddress ) {
        this->name = theName;
        this->ssn = theSSN;
        this->birthdate = theBirthDate;
        this->address = theAddress;
        cout << "Person Counstruct" << endl;

        this->roleCount = 0;
        this->activeRole = 0;
    }

    Person( const Person& other) {
        this->name = other.name;
        this->ssn = other.ssn;
        this->birthdate = other.birthdate;
        this->address = other.address;
        this->roleCount = other.roleCount;
        this->activeRole = other.activeRole;

        cout << "Person Copy Counstruct" << endl;
    }

    Person& operator=( const Person& other) {

    }

    ~Person() {};

    bool adoptNewRole(UniversityMember* newRole)
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

    UniversityMember* setActiveRole(UniversityMember* thisRole) {
        if(thisRole != 0)
        {
            UniversityMember* oldRole = activeRole;
            activeRole = thisRole;
            return oldRole;
        }

        return 0;
    }

    UniversityMember* getActiveRole() {
        return activeRole;
    }

    void print() {
        cout<<"Name: " << this->name << endl;
        cout<<"Address: "<< this->address << endl;
        cout<<"ID: " << this->ssn << endl;
        cout<<"Birthdate: "<< this->birthdate << endl;
    }
};

class UniversityMember
{
	UniversityMember* role;
	Person* ownerOfRole;
	Department department;

public:

	UniversityMember() {};

	UniversityMember(UniversityMember* whichRole, Person* thisPerson) {
        this->role = whichRole;
        this->ownerOfRole = thisPerson;

        cout << "UniversityMember Construct" <<endl;
	}

	UniversityMember(const UniversityMember& other) {
        this->role = other.role;
        this->ownerOfRole = other.ownerOfRole;

        cout << "UniversityMember Construct" <<endl;
	}

	UniversityMember& operator=(const UniversityMember& other) {
        this->role = other.role;
        this->ownerOfRole = other.ownerOfRole;

        cout << "UniversityMember Construct" <<endl;
	};

	virtual ~UniversityMember(){}	//virtual destructor

	bool operator==(const UniversityMember& other) {
        cout<<"inside the overload definition of == for UniversityMember"<<endl;
        return typeid(*this) == typeid(other);
	};

	Person* roleFor() const
	{
		return this->ownerOfRole;
	}

	Department getDepartment() const {
        return this->department;
	}

	virtual void print() const {}
};

const int MaxCoursesForStudent = 4;
class Student : public UniversityMember
{

private:
    StudentStatus status;
    Department department;
    Course* entolledFor[MaxCoursesForStudent];
    int numCourses;
public:

    Student() : UniversityMember() {}

  // constructor:
    Student(StudentStatus theStatus): UniversityMember() {

        this->status = theStatus;

        for(int i=0; i< MaxCoursesForStudent; i++)
            entolledFor[i] = 0;

        this->numCourses = 0;

        cout << "Student Construct" << endl;
    };

  // copy constructor, assignment operator, destructor:
    Student( const Student& other) {
        this->status = other.status;
        this->numCourses = other.numCourses;

        for(int i=0; i< MaxCoursesForStudent; i++) {
            if(other.entolledFor[i] != 0) this->entolledFor[i] = new Course(*(other.entolledFor[i]));
        }
    }

    Student& operator=( const Student& other) {
        if(this == &other) return *this;
        status = other.status;
        numCourses = other.numCourses;

        for(int i=0; i< MaxCoursesForStudent; i++)
        {
            if(this->entolledFor[i] != 0 && other.entolledFor[i] == 0)
                delete entolledFor[i];
            else if(this->entolledFor[i] == 0 && other.entolledFor[i] != 0)
                this->entolledFor[i] = new Course(*(other.entolledFor[i]));
            else if(this->entolledFor[i] != 0 && other.entolledFor[i] != 0)
                *(this->entolledFor[i]) = *(other.entolledFor[i]);
        }

        return *this;
    };

    ~Student() {
    	for(int i=0; i< MaxCoursesForStudent; i++) {
            if(this->entolledFor[i] != 0)
                delete entolledFor[i];
        }
    };

    void setDepartment(Department newDept) {
        this->department = newDept;
	}

    void setStatus( StudentStatus aStatus ) {
        this->status = aStatus;
        cout << "set status sucess" << endl;
    };

    StudentStatus getStatus() const {
        return this->status;
    };


    bool enrollForCourse(const Course& aCourse) {
        if(this->numCourses >= MaxCoursesForStudent)
            return false; //already enrolled too many courses

        for(int i=0; i< MaxCoursesForStudent; i++)
        {
            if(entolledFor[i] == 0)
            {
                this->entolledFor[i] = new Course(aCourse);
                this->numCourses++;
                return true;
            }
        }
        return false;
    };

    bool dropFromCourse(const Course& theCourse)
    {
        for(int i=0; i< MaxCoursesForStudent; i++)
        {
            if(this->entolledFor[i] != 0)
            {
                if(*this->entolledFor[i] == theCourse)
                {
                    delete this->entolledFor[i];	//it was dynamically allocated
                    this->entolledFor[i] = 0;
                    numCourses--;
                    return true;
                }
            }
        }
        return false;	//student has not registered for this course
    }

    void listCoursesRegisteredFor() const {
        for(int i=0; i< MaxCoursesForStudent; i++) {
            if(this->entolledFor[i] != 0) {
                cout << *this->entolledFor[i];
            }
        }
        cout<<endl;
    }

    Department getDepartment() const {
        return this->department;
    }

    void print() const {
        cout<<"*** Informations as a student ***"<<endl;
        cout<<"Status: "<<statusLabels[(int)status]<<endl;
        cout<<"Department: "<< departmentNames[getDepartment()] <<endl;
        cout<<"Number of courses registed: "<< this->numCourses <<endl;
        listCoursesRegisteredFor();
    }
};


//////////// derived class Teacher /////////////
const int MaxCoursesForTeacher = 2;
const int MaxGraders = 2;

class Teacher : public Person
{

private:
    Rank rank;
    double salary;
    Department department;
    Course* coursesOffered[MaxCoursesForTeacher];
    string* graders[MaxGraders];

public:
	Teacher(){}

    Teacher(const string theName, unsigned long theSSN, Date theBirthDate, const string theAddress) {
    }


};


//////////// main /////////////
int main()
{
	Person per1("Wei", 123456, Date(12, 10, 1992), "Teipei");
    Course course("Computer Science", 104400135);

    //per1.adoptNewRole(new Student(FullTime));
    per1.setActiveRole(new Student(FullTime));
    Student* sp = dynamic_cast<Student*>(per1.getActiveRole());
    sp->setDepartment(Engineering);
    sp->enrollForCourse(course);

	per1.print();
    sp->print();

	return 0;
}
