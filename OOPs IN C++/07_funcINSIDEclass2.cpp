#define _WIN32_WINNT 0x0600
#include <iostream>
#include "rang.hpp"
using namespace rang;
using namespace std;

class StudentofJECRC
{
//PRIVATE ATTRIBUTES
//Can only access by inside the class and class functions
private:
    string name;
    int rollno;
    int age;
    string branch;
    int marks[5];
    float CGPA;

//PUBLIC ATTRIBUTES
//Can access outside the class too
public:

    //Default Constructor
    StudentofJECRC()
    {
        //if anyone didn't fill any details
        name = " ";
        rollno = 0;
        age = 0;
        branch = " ";
        for(int i = 0; i < 5; i++) marks[i] = 0;
        CGPA = 0;
    }

    // Functions to set Details of student
    void setDetails()
    {
        cout<< fg::cyan << "\n-----📝 Getting Student Details-----\n";

        cout<< fg::yellow << "👉 Enter Student Name: ";
        getline(cin, name);

        cout<< fg::yellow << "🔢 Enter Roll number: ";
        cin >> rollno;

        cout<< fg::yellow << "🪭 Enter Age: ";
        cin >> age;

        cin.ignore();

        cout<< fg::yellow << "Enter Branch: ";
        getline(cin, branch);

        cout<< fg::yellow << "\n5️⃣ Enter Marks of 5 Main subjects:\n";
        for(int i = 0; i < 5; i++)
        {
            cout<< fg::green << "Subject " << i + 1 << ": ";
            cin >> marks[i];
        }

        calculateCGPA();
    }

    // Function for calculate CGPA
    void calculateCGPA()
    {
        int total = 0;
        for(int i = 0; i < 5; i++)
        {
            total += marks[i];
        }
        float percentage = total / 5.0;
        CGPA = percentage / 9.5; //Approximate Conversion
    }

    // Function to Display all Details
    void displayStudentDetails()
    {
        cout << fg::magenta << "\n-----🖥️ Student Details-----\n";

        cout << fg::green << "Name         : " << name << endl;
        cout << fg::green << "Roll no      : " << rollno << endl;
        cout << fg::green << "Age          : " << age << endl;
        cout << fg::green << "Branch       : " << branch << endl;

        cout << fg::green << "Marks        : ";
        for(int i = 0; i < 5; i++)
        {
            cout << fg::yellow << marks[i] << " ";
        }

        cout << fg::green << "\nCGPA         : " << CGPA << endl;
        cout << fg::green << "Passed       : " << (isPassed() ? "Yes ✅" : "No ❌") <<endl;
    }

    //Function of Getting Rollnumber
    int getRollNo()
    {
        return rollno;
    }

    //Function to check student is passed or not
    bool isPassed()
    {
        for(int i = 0; i < 5; i++)
        {
            if (marks[i] < 33)
                return false;
        }
        return true;
    }
    
};

int main()
{
    system("chcp 65001");

    //Object 1
    StudentofJECRC s1;
    s1.displayStudentDetails();//show the default values as we didn't set any values for s1

    //Object 2
    StudentofJECRC s2;
    s2.setDetails(); //first we set details 
    s2.displayStudentDetails();// then it display the details

    return 0;
}