#define _WIN32_WINNT 0x0600 //for running the file rang.hpp for colored output
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
    void Ishungry()
    {
        //only for asking is hungry or not
        if(ishungry == 1)
        {
            cout << fg::red << "Yes " << name <<" is Hungry! 🐥"<< endl;
        }
        else
        {
            cout << fg::red << "No " << name <<" is not Hungry! 🐥"<< endl;
        }
    }

};

int main()
{
    system("chcp 65001");//for getting emojis in terminal output

    //DYNAMIC ALLOCATION
    int *ptr = new int(5); //Runtime me memory allocate hui
    int *ptr1 = new int[5]; //can also make array,vector too.

    //USE OF DA IN OOPs

    Pet *p1 = new Pet("Oggy", "cat", "Persian", 2, 4.3, false);

    //if we have to print details of it
    p1->getInfo();

    //have to play with pet then we feed them
    p1->play();
    p1->Ishungry();//is hungry yes 

    p1->eat();

    p1->Ishungry(); //no

    return 0;
}