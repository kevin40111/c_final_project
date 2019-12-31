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
static const string rankNames[] = {"Instructor", "GradTeachingAsst", "AsstProf", "Professor", "ResScientist", "Dean", "rUnknown"};
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
    }

    ~Course() {}

    bool operator==( const Course& other)
    {
        if(this == &other)
            return true;
        else
            return false;
    }

    // comparison operators:
    Course& operator=( const Course& other) {
        if ( this != &other ) {
            courseName = other.courseName;
            courseId = other.courseId;
        }
        return *this;
    }

    bool operator!=( const Course& other) {
        if(this != &other)
            return true;
        else
            return false;
    }

    string getCourseName() const {
        return this->courseName;
    }

    void setCourseName( const string txt) {
        this->courseName = txt;
    }

    long getCourseId() const {
        return courseId;
    }

    void setCourseId( long id) {
        this->courseId = id;
    }

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
        this->roleCount = 0;
        this->activeRole = 0;
        for(int i=0; i < MaxRoles; i++) {
            allRoles[i] = 0;
        }
    }

    Person( const Person& other) {
        this->name = other.name;
        this->ssn = other.ssn;
        this->birthdate = other.birthdate;
        this->address = other.address;
        this->roleCount = other.roleCount;
        this->activeRole = other.activeRole;
        for(int i=0; i < MaxRoles; i++) {
            this->allRoles[i] = other.allRoles[i];
        }
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
    }

    UniversityMember(const UniversityMember& other) {
        this->role = other.role;
        this->ownerOfRole = other.ownerOfRole;
    }

    UniversityMember& operator=(const UniversityMember& other) {
        this->role = other.role;
        this->ownerOfRole = other.ownerOfRole;
    };

    virtual ~UniversityMember(){}   //virtual destructor

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
                    delete this->entolledFor[i];    //it was dynamically allocated
                    this->entolledFor[i] = 0;
                    numCourses--;
                    return true;
                }
            }
        }
        return false;   //student has not registered for this course
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
class Teacher : public UniversityMember
{

private:
    Rank rank;
    double salary;
    Department department;
    Course* coursesOffered[MaxCoursesForTeacher];
    string* graders[MaxGraders];
    int numCourses;
    int numGraders;

public:
    Teacher(){}

    Teacher(Rank tRank): UniversityMember() {

        this->rank = tRank;

        for(int i=0; i< MaxCoursesForTeacher; i++)
            this->coursesOffered[i] = 0;

        for(int i=0; i< MaxGraders; i++)
            this->graders[i] = 0;

        this->numCourses = 0;
        this->numGraders = 0;
    };

    Teacher( const Teacher& other) {
        this->rank = other.rank;
        this->numCourses = other.numCourses;
        this->numGraders = other.numGraders;

        for(int i=0; i < MaxCoursesForTeacher; i++) {
            this->coursesOffered[i] = new Course(*(other.coursesOffered[i]));
        }

        for(int i=0; i < MaxGraders; i++) {
            this->graders[i] = other.graders[i];
        }
    }

    Department getDepartment() const {
        return this->department;
    }

    void setRank(Rank tRank) {
        this->rank = tRank;
    }

    void setDepartment(Department newDept) {
        this->department = newDept;
    }

    void setSalary(double salary) {
        this->salary = salary;
    }

    void listCoursesRegisteredFor() const {
        for(int i=0; i< MaxCoursesForTeacher; i++) {
            if(this->coursesOffered[i] != 0) {
                cout << *this->coursesOffered[i];
            }
        }
        cout<<endl;
    }

    bool enrollForCourse(const Course& aCourse) {
        if(this->numCourses >= MaxCoursesForStudent)
            return false; //already enrolled too many courses

        for(int i=0; i< MaxCoursesForTeacher; i++)
        {
            if(coursesOffered[i] == 0)
            {
                this->coursesOffered[i] = new Course(aCourse);
                this->numCourses++;
                return true;
            }
        }
        return false;
    };

    bool dropFromCourse(const Course& theCourse)
    {
        for(int i=0; i< MaxCoursesForTeacher; i++)
        {
            if(this->coursesOffered[i] != 0)
            {
                if(*this->coursesOffered[i] == theCourse)
                {
                    delete this->coursesOffered[i]; //it was dynamically allocated
                    this->coursesOffered[i] = 0;
                    numCourses--;
                    return true;
                }
            }
        }
        return false;   //student has not registered for this course
    }

    bool setGraders(string grader) {
        if(this->numGraders >= MaxGraders)
            return false; //already enrolled too many courses

        for(int i=0; i<MaxGraders; i++)
        {
            if(graders[i] == 0)
            {
                this->graders[i] = new string(grader);
                this->numGraders++;
                return true;
            }
        }
        return false;
    }

    void print() const {
        cout<<"*** Informations as a teacher ***"<<endl;
        cout<<"Rank: "<<rankNames[(int)rank - 1]<<endl;
        cout<<"Department: "<< departmentNames[getDepartment()] <<endl;
        cout<<"Salary: "<< this->salary << endl;
        cout << "Graders: ";
        cout<<"Number of courses registed: "<< this->numCourses <<endl;
        for(int i=0; i < this->numGraders; i++) {
            cout << *this->graders[i] << " ";
        }
        cout << endl;
        listCoursesRegisteredFor();
        cout<<endl;

    }
};


const unsigned GradCourseLevel = 400;
const unsigned MaxCoursesForGradStudent = 4;
class GraduateStudent : public Student {

  Teacher advisor;
  unsigned short numCourses;

public:
    GraduateStudent();
    GraduateStudent( StudentStatus theStatus);
    GraduateStudent( const GraduateStudent& other );
    GraduateStudent&  operator=( const GraduateStudent& other );
    ~GraduateStudent(){};
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
    cout<<"Advisor is :" << endl;
    advisor.print();
}

int main()
{
    Person per1("Wei", 123456, Date(12, 10, 1992), "Teipei");
    Person per2("Kevin", 321654, Date(12, 10, 1922), "USA");

    Course course("Computer Science", 104400135);

    per2.setActiveRole(new Teacher(ResScientist));
    per1.setActiveRole(new Student(FullTime));

    Student* sp = dynamic_cast<Student*>(per1.getActiveRole());
    Teacher* st = dynamic_cast<Teacher*>(per2.getActiveRole());

    sp->setDepartment(Engineering);
    sp->enrollForCourse(course);

    st->setDepartment(Engineering);
    st->enrollForCourse(course);
    st->setSalary(78000);
    st->setGraders("10705507");

    sp->print();
    per1.print();

    cout << "-----------------------------------" << endl;

    st->print();
    per2.print();

    cout << "-----------------------------------" << endl;

    Person per3("Dick Check", 234567, Date(7, 6, 1989), "Main Street, USA");
    per3.adoptNewRole(new GraduateStudent(FullTime));
    per3.setActiveRole(new GraduateStudent(FullTime));
    GraduateStudent* gp = dynamic_cast<GraduateStudent*>(per3.getActiveRole());
    gp->changeAdvisor(*st);
    gp->setDepartment(Engineering);

    cout << "Graduate Student:" << endl;
    per3.print();
    gp->print();
    per2.print();

    return 0;
}
