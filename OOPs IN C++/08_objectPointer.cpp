#define _WIN32_WINNT 0x0600
#include <iostream>
#include "rang.hpp"
using namespace rang;
using namespace std;

class Pet
{
public:
    string name;
    string species;
    string breed;
    int age;
    float weight;
    bool ishungry;

    Pet()
    {
        //default constructor
    }

    //PARAMETERIZED CONSTRUCTOR
    Pet(string name, string species, string breed, int age, float weight, bool ishungry)
    {
        this -> name = name;
        this -> species = species;
        this -> breed = breed;
        this -> age = age;
        this -> weight = weight;
        this -> ishungry = ishungry;
    }

    //Functions
    void eat(){
        if(ishungry)
        {
            cout << fg::green << "\n" << name << " is Eating now. 🍖"<< endl;
            ishungry = false;
        }
        else
        {
            cout <<fg::green << "\n" << name <<" is not hungry now. 🍪" <<endl;
        }
    }

    void play()
    {
        cout <<fg::green << "\n" << name << " is playing happily! ⚽"<< endl;
        ishungry = true;
    }

    void getInfo() 
    {
        cout << fg::magenta << "\n🐶 Pet Information 🐾" << endl;
        cout << fg::cyan << "Name: " << name << endl;
        cout << fg::cyan << "Species: " << species << endl;
        cout << fg::cyan << "Breed: " << breed << endl;
        cout << fg::cyan << "Age: " << age << " years" << endl;
        cout << fg::cyan << "Weight: " << weight << " kg" << endl;
        cout << fg::cyan << "Hungry: " << (ishungry ? "Yes" : "No") << endl;
    }

    void updateWeight(float newWeight)
    {
        weight = newWeight;
        cout <<fg::green << "\n" << name << "'s weight has been updated to " << weight << " kg." << endl;
    }


};

void changeNamePASSBYVALUE(Pet p, string newName)
{
    p.name = newName;
}//pass by value name doesn't change

void changeNamePASSBYREF(Pet* p, string newName)
{
    (*p).name = newName;
    //Another method we can do it
    p -> name = newName;
}

int main()
{
    system("chcp 65001");

    //-----Revising Pointer Concepts-----
    int x = 4;
    cout << fg::yellow << &x << endl;
    int* ptr = &x;
    cout<< ptr << endl; // same as previous one 

    cout<< *ptr <<endl; //dereference operator

    *ptr = 100;
    cout << x << endl; //now output = 100

    //----------OBJECT POINTER----------
    cout << fg::magenta << "\n---OBJECT POINTER---\n";
    //object 1
    Pet p1("Tommy", "Dog", "Labrador", 3, 25, true);

    //pointer
    Pet* ptr1 = &p1;
    //for getting values from object pointer
    cout << fg::green << (*ptr1).name <<endl;
    //we can change values too
    (*ptr1).name = "Bruno";
    p1.getInfo();
    p1.eat();

    changeNamePASSBYVALUE(p1, "Tom");
    p1.getInfo();//name doesn't change it remains Bruno

    changeNamePASSBYREF(ptr1, "Titan");
    p1.getInfo();//name changes to Titan

    //a -> b means a must be a pointer (*a).b

    return 0; 
}