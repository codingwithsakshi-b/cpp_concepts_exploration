#define _WIN32_WINNT 0x0600
#include <iostream>
#include "rang.hpp"
using namespace rang;
using namespace std;

class Student
{

public://public means can access direct outside the class or inside the class too.
    string name;
    int rollno;
    float CGPA;
    int age;
    string branch;
    int marks[5]; // Array to store marks of 5 subjects

    //for making normal inialization we need to mae a default construtor
    Student()
    {
        //default Construtor
    }

    // Parameterized Constructor
    Student (string s, int r, float g, int a, string b)
    { // function like but no return type
        name = s;
        rollno = r;
        CGPA = g;
        age = a;
        branch = b;
    }

    //We can make Multiple Parameterized Constructor
    Student(string s, int r, float g)
    {
        name = s;
        rollno = r;
        CGPA = g;
    }

};

void printStudentDetails(Student s){
    cout << fg::cyan << "👉 Name : "<< s.name <<endl;
    cout << fg::cyan << "👉  rollno : "<< s.rollno <<endl;
    cout << fg::cyan << "👉 CGPA : "<< s.CGPA <<endl;
    cout << fg::cyan << "👉 age : "<< s.age <<endl;
    cout << fg::cyan << "👉 branch : "<< s.branch <<endl;
}

class Car // classes is like blueprint of object
{
public:
    string name; // attribute of class car
    int price;
    int seats;
    int bhp; // brake horse power
    string color;

    //for normal inialization  in some case
    Car()
    {
        //default Constructor
    }

    //Constructor for car class
    Car(string n, int p, int s, int b, string c)
    { //Parameterized Constructor
        name = n;
        price = p;
        seats = s;
        bhp = b;
        color = c;
    }
};

void printCarDetails(Car c)
{
    cout<< fg::cyan << "Car Name: " << c.name << endl;
    cout<< fg::cyan << "Price: $" << c.price << endl;
    cout<< fg::cyan << "Seats: " << c.seats << endl;
    cout<< fg::cyan << "BHP: " << c.bhp << endl;
    cout<< fg::cyan << "Color: " << c.color << endl;
}

int main()
{
    system("chcp 65001");

    // Use of constructor
    //we can directly initialize values

    //OBJECT 1
    Student s1("Sakshi Kumari", 36, 8.5, 20, "BTech-CSE"); //calling our Constructor

    cout<<fg::magenta<< "\n📑 Student Details of s1\n";
    printStudentDetails(s1);

    //OBJECT 2
    Student s2("Keshav Sharma", 37, 8.2, 21, "BPharma");

    cout<<fg::magenta<< "\n📑 Student Details of s2\n";
    printStudentDetails(s2);

    //OBJECT 3
    Student s3("Rahul Sharma", 38, 9.1);

    cout<<fg::magenta<< "\n📑 Student Details of s2\n";
    printStudentDetails(s3); // no error because we make a constructor only for these 3 values

    //For Car Class
    Car c1("X1 SUV", 41350, 5, 134, "white");//object 1

    cout << fg::magenta << "\n🚗 Details of CAR1\n";
    printCarDetails(c1);

    Car c2("Audi Q7 Premium Plus", 65000, 7, 335, "red");//object 2

    cout << fg::magenta << "\n🚗 Details of CAR2\n";
    printCarDetails(c2);

    //object 3
    Car c3;
    cout << fg::magenta << "\n🚗 Details of CAR3 - Prints Garbage Value because it is not inialised with any value\n";
    printCarDetails(c3);//prints Garbage values

    //CONCEPT OF COPY CONSTRUCTOR

    Car c4 = c1; // Deep copy of c1
    c4.name = " Tesla Model 3 "; //it doesn't change in original car1 only changes for car4
    cout << fg::magenta << "\n🚗 Details of CAR4\n";
    printCarDetails(c4);

    Car c5(c2); //shallow copy == COPY CONSTRUCTOR;
    c5.name = "BMW X5 xDrive40i"; 
    cout << fg::magenta << "\n🚗 Details of CAR5\n";//also a deep copy
    printCarDetails(c5);

    return 0;
}