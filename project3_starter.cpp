//starter for project 3


/////////////      class Person      ///////////////



class UniversityMember;

const short MaxRoles = 6;   //an arbitrary limit


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
	//initialize
}

Person::Person( const string theName, unsigned long theSSN, Date theBirthDate, const string theAddress )
{

	//initialize the roles to 0

	for(int i=0; i<MaxRoles; i++)
		allRoles[i] = 0;

	roleCount = 0;

	activeRole = 0;
}

Person::~Person()
{
	delete [] allRoles;
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

	virtual ~UniversityMember(){}	//virtual destructor

	bool operator==(const UniversityMember& other);

	Person* roleFor() const
	{
		return ownerOfRole;
	}

	Person* changeOwnerTo(Person* newPerson);

	Department getDepartment() const;

	void setDepartment(Department newDept);

	virtual string toString() const{}

	virtual void print() const {}
};


UniversityMember::UniversityMember()
{

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
  Student( const Student& );
  Student& operator=( const Student& );
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
	cout<<"*** Informations as a student ***"<<endl;
	cout<<"Status: "<<statusLabels[(int)status]<<endl;
	cout<<"Department: "<<departmentNames[getDepartment()]<<endl;
	cout<<"Number of courses registed: "<<numCourses<<endl;
	listCoursesRegisteredFor();
}



//////////// derived class Teacher /////////////


const int MaxCoursesForTeacher = 2;
const int MaxGraders = 2;


class Teacher : public UniversityMember
{  
	//.....
public:
	Teacher(){}
	//.....
};

//.....



//////////// main /////////////

void main()
{
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
}