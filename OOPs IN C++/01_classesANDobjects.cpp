#define _WIN32_WINNT 0x0600
#include <iostream>
#include "rang.hpp"
using namespace rang;
using namespace std;

// Making Class
class Teacher
{
private:
    double salary; // private attribute
    // access only in class

public: // public attributes and methods
    // can access outside class too
    string name;
    string department;
    string subject;

    // setter function
    void changeDept(string dept)
    {
        department = dept;
    }
    void setSalary(double s)
    {
        salary = s;
    }
    // getter function
    double getSalary()
    {
        return salary;
    }
};

int main()
{
    system("chcp 65001");

    // making objects
    Teacher t1;
    t1.name = "Sakshi Sharma";
    t1.department = "Btech";
    t1.subject = "C++";

    // t1.salary; we can't access private attributes directly
    t1.setSalary(25000);                                                             // set salary by this public method
    cout << fg::green << "Salary of " << t1.name << " = " << t1.getSalary() << endl; // if we want to get salary we can access by this method

    return 0;
}