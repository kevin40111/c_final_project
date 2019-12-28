#include <iostream>
#include <string>
using namespace std;

class Student {       // The class
    public:
        Student(string stdid) {
            this->stdid = stdid;
            cout << "student construct call" << endl;
        }

        Student(){
            cout << "student construct call" << endl;
        };

        Student(const Student &object) {
            this->stdid = object.stdid;
            cout << "copy student construct call" << endl;
        }

        Student& operator=(const Student &obj) {
            return *this;
        }

        void print(){
            cout << this->stdid;
        }

        ~Student(){
            cout << "Destruct student call" << endl;
        }

    protected:
        string stdid;
};

class GraduateStudent : public Student {
    public:
        void print(){
            cout << this->stdid << " " << this->group << endl;
        }

        GraduateStudent() {
            cout << "GraduateStudent construct call" << endl;
        }

        GraduateStudent(string stdid, string group){
            this->group = group;
            this->stdid = stdid;
            cout << "GraduateStudent construct call" << endl;
        }

        GraduateStudent(const GraduateStudent &obj){
            this->group = obj.group;
            this->stdid = obj.stdid;
            cout << "copy GraduateStudent construct call" << endl;
        }

        GraduateStudent& operator=(GraduateStudent &obj) {
            this->group = obj.group;
            this->stdid = obj.stdid;
            cout << "copy assignment GraduateStudent construct call" << endl;
            return *this;
        }

        ~GraduateStudent() {
            cout << "Destruct GraduateStudent call" << endl;
        }

    protected:
        string group;
};

class MasterStudent : public GraduateStudent {
    public:
        void print(){
            cout << this->stdid << " " << this->group <<  " "  << this->academic << endl;
        }

        MasterStudent(){
            cout << "MasterStudent construct call" << endl;
        }

        MasterStudent(string stdid, string group) : GraduateStudent(stdid, group) {
            this->group = group;
            this->stdid = stdid;
            cout << "MasterStudent construct call" << endl;
        }

        MasterStudent(const MasterStudent &obj) : GraduateStudent(obj) {
            this->group = obj.group;
            this->stdid = obj.stdid;
            cout << "Copy MasterStudent construct call" << endl;
        }

        MasterStudent& operator=(MasterStudent &obj) {
            this->group = obj.group;
            this->stdid = obj.stdid;
            cout << "copy assignment MasterStudent construct call" << endl;
            return *this;
        }

        ~MasterStudent() {
            cout << "Destruct MasterStudent call" << endl;
        }

    private:
        int academic = 4;
};

class PhDStudent : public GraduateStudent {
    public:
        void print(){
            cout << this->stdid << " " << this->group <<  " "  << this->academic << endl;
        }

        PhDStudent(){
            cout << "PhDStudent construct call" << endl;
        }

        PhDStudent(string stdid, string group) : GraduateStudent(stdid, group) {
            this->group = group;
            this->stdid = stdid;
            cout << "PhDStudent construct call" << endl;
        }

        PhDStudent(const PhDStudent &obj) : GraduateStudent(obj) {
            this->group = obj.group;
            this->stdid = obj.stdid;
            cout << "Copy PhDStudent construct call" << endl;
        }

        PhDStudent& operator=(PhDStudent &obj) {
            this->group = obj.group;
            this->stdid = obj.stdid;
            cout << "copy assignment PhDStudent construct call" << endl;
            return *this;
        }

        ~PhDStudent() {
            cout << "Destruct PhDStudent call" << endl;
        }

    private:
        int academic = 4;
};

class UndergraduateStudent : public Student {
    public:
        void print(){
            cout << this->stdid << " " << this->department << endl;
        }

        void tutionCaculate();

        UndergraduateStudent(){
            cout << "GraduateStudent construct call" << endl;
        }

        UndergraduateStudent(string stdid, string department):Student(stdid) {
            this->department = department;
            this->stdid = stdid;
            cout << "GraduateStudent construct call" << endl;
        }

        UndergraduateStudent(const UndergraduateStudent &obj):Student(obj) {
            this->department = obj.department;
            this->stdid = obj.stdid;
            cout << "Copy UndergraduateStudent construct call" << endl;
        }

        UndergraduateStudent& operator=(UndergraduateStudent &obj) {
            this->department = obj.department;
            this->stdid = obj.stdid;
            cout << "copy assignment UndergraduateStudent construct call" << endl;
            return *this;
        }

        ~UndergraduateStudent() {
            cout << "Destruct UndergraduateStudent call" << endl;
        }
    protected:
        string department;
        int tuition = 0;
};

class FullTimeStudent : public UndergraduateStudent {
    public:
        void print(){
            cout << this->stdid << " " << this->department << " " << this->tuition << endl;
        }

        void tutionCaculate(int cost) {
            this->tuition = cost;
        }

        FullTimeStudent(){
            cout << "FullTimeStudent construct call" << endl;
        }

        FullTimeStudent (string stdid, string department):UndergraduateStudent(stdid, department) {
            this->department = department;
            this->stdid = stdid;
            cout << "FullTimeStudent construct call" << endl;
        }

        FullTimeStudent(const FullTimeStudent &obj):UndergraduateStudent(obj) {
            this->department = obj.department;
            this->stdid = obj.stdid;
            this->tuition = obj.tuition;
            cout << "Copy FullTimeStudent construct call" << endl;
        }

        FullTimeStudent& operator=(FullTimeStudent &obj) {
            this->department = obj.department;
            this->stdid = obj.stdid;
            this->tuition = obj.tuition;
            cout << "copy assignment FullTimeStudent construct call" << endl;
            return *this;
        }

        ~FullTimeStudent() {
            cout << "Destruct FullTimeStudent call" << endl;
        }
};

class PartTimeStudent : public UndergraduateStudent {
    public:
        void print(){
            cout << this->stdid << " " << this->department << " " << this->tuition << endl;
        }

        void tutionCaculate(int numberOfCredits ) {
            this->tuition = numberOfCredits * 8200;
        }

        PartTimeStudent(){
            cout << "PartTimeStudent construct call" << endl;
        }

        PartTimeStudent (string stdid, string department):UndergraduateStudent(stdid, department) {
            this->department = department;
            this->stdid = stdid;
            cout << "PartTimeStudent construct call" << endl;
        }

        PartTimeStudent(const PartTimeStudent &obj):UndergraduateStudent(obj) {
            this->department = obj.department;
            this->stdid = obj.stdid;
            this->tuition = obj.tuition;
            cout << "Copy PartTimeStudent construct call" << endl;
        }

        PartTimeStudent& operator=(PartTimeStudent &obj) {
            this->department = obj.department;
            this->stdid = obj.stdid;
            this->tuition = obj.tuition;
            cout << "copy assignment FullTimeStudent construct call" << endl;
            return *this;
        }

        ~PartTimeStudent() {
            cout << "Destruct PartTimeStudent call" << endl;
        }
};

int main() {
    cout << "---------------------------GraduateStudent Construct" << endl;
    GraduateStudent stu("M10705507", "資訊組");
    stu.print();

    cout << "---------------------------Copy GraduateStudent Construct" << endl;
    GraduateStudent stu2 = stu;
    stu2.print();

    cout << "---------------------------PhDStudent Construct" << endl;
    PhDStudent stu3("D10550051", "材料組");
    stu3.print();

    cout << "---------------------------FullTimeStudent Construct" << endl;
    FullTimeStudent stu4("M10550031", "營管組");
    stu4.tutionCaculate(24360);
    stu4.print();

    cout << "---------------------------PartTimeStudent Construct" << endl;
    PartTimeStudent stu5("M10705057", "結構組");
    stu5.tutionCaculate(6);
    stu5.print();

    cout << "---------------------------Copy PartTimeStudent Construct" << endl;
    PartTimeStudent stu6 = stu5;
    stu6.print();

    cout << "---------------------------Copy Assignment GraduateStudent Construct" << endl;
    GraduateStudent stu7;
    stu7 = stu;
    stu7.print();

    cout << "---------------------------Copy Assignment FullTimeStudent Construct" << endl;
    FullTimeStudent stu8;
    stu8 = stu4;
    stu8.tutionCaculate(20000);
    stu4.print();
    stu8.print();

    cout << "---------------------------call Destruct" << endl;

    return 0;
}
