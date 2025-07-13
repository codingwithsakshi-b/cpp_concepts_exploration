#define _WIN32_WINNT 0x0600 //for using rang.hpp file for getting colorful terminal
#include <iostream>
#include "rang.hpp"
using namespace rang;
using namespace std;

//by class we making new data type of own
class Student
{

public://public means can access direct outside the class or inside the class too.
    string name;
    int rollno;
    float CGPA;
    int age;
    string branch;
    int marks[5]; // Array to store marks of 5 subjects


};

class Car // classes is like blueprint of object
{
public:
    string name; // attribute of class car
    int price;
    int seats;
    int bhp; // brake horse power
    string color;
};

int main()
{ 
    system("chcp 65001");//for getting emojis

    //object 1
    Student s1;
    s1.name = "Sakshi Kumari";
    s1.rollno = 101;
    s1.CGPA = 9.1;
    // s1.age = 20;
    s1.branch = "CSE";
    s1.marks[0] = 85;
    s1.marks[1] = 90;
    s1.marks[2] = 78;
    s1.marks[3] = 88;
    s1.marks[4] = 92;
    //getting values from user
    cin>>s1.age; // Input for age

    //object 2
    Student s2;
    s2.name = " Keshav Sharma";
    s2.rollno = 102;
    s2.CGPA = 8.5;
    s2.age = 21;
    s2.branch = "ECE";
    s2.marks[0] = 80;
    s2.marks[1] = 85;
    s2.marks[2] = 90;
    s2.marks[3] = 88;
    s2.marks[4] = 92;

    //object 3
    Car c1;
    c1.name = "Tesla Model S";
    c1.price = 79999;
    c1.seats = 5;
    c1.bhp = 670;
    c1.color = "Red";

    //object 4
    Car c2;
    c2.name = "Ford Mustang";
    c2.price = 55999;
    c2.seats = 4;
    c2.bhp = 450;
    c2.color = "Blue";

    //getting object data
    cout << fg::green << "Name student1: " << s1.name << endl;
    
    cout << fg::green << "Name student2: " << s2.name << endl;
    
    cout<<fg::green<<"Age of student1: " << s1.age << endl;
    
    cout << fg::blue << "Car 1 Name: " << c1.name << endl;
    
    cout << fg::blue << "Car 1 Price: $" << c1.price << endl;
    
    cout<< fg::cyan << "Car 2 Name: " << c2.name << endl;
    
    cout << fg::cyan << "Car 2 Price: $" << c2.price << endl;

    return 0;
}