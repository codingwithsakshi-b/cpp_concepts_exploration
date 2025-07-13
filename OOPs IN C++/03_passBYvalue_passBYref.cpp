#define _WIN32_WINNT 0x0600
#include <iostream>
#include "rang.hpp"
using namespace rang;
using namespace std;

class Car // classes is like blueprint of object
{
public:
    string name; // attribute of class car
    int price;
    int seats;
    int bhp; // brake horse power
    string color;
};

void printCarDetails(Car c)
{
    cout<< fg::cyan << "Car Name: " << c.name << endl;
    cout<< fg::cyan << "Price: $" << c.price << endl;
    cout<< fg::cyan << "Seats: " << c.seats << endl;
    cout<< fg::cyan << "BHP: " << c.bhp << endl;
    cout<< fg::cyan << "Color: " << c.color << endl;
}

void ChangeCarColor(Car c) //pass by value
{
    c.color = "blue";
}

void ChangeCarColorRef(Car &c) //pass by reference
{ // due to adding & we are passing address of c
    // so it will change the original object
    // POINTERS THEORY
    c.color = "green";
}

int main()
{
    system("chcp 65001");

    //object 1
    Car c1;
    c1.name = "Tesla Model S";
    c1.price = 79999;
    c1.seats = 5;
    c1.bhp = 670;
    c1.color = "Red";

    //getting car details after changing color
    printCarDetails(c1);
    ChangeCarColor(c1); // This will not change the color of c1
    cout << fg::yellow << "\nAfter ChangeCarColor (pass by value):" << endl;
    printCarDetails(c1);    

    ChangeCarColorRef(c1); // This will change the color of c1
    cout << fg::green << "\nAfter ChangeCarColorRef (pass by reference):" << endl;
    printCarDetails(c1); //color = green

    return 0;
} 