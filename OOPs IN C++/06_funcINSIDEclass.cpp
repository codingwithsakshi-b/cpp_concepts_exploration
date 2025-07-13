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

int main(){
    system("chcp 65001");

    //Creating an Object
    Pet myPet("Tommy", "Dog", "Labrador", 3, 25, true);

    //Testing Functions
    myPet.getInfo();

    //in output we saw that pet is hungry so
    myPet.eat();

    //now if we get info it is not hungry anymore
    myPet.getInfo();

    //now we go to method play then again we get info it becomes hungry 
    myPet.play();
    myPet.getInfo(); //now pet is hungry

    //now again we feed our dog
    myPet.eat();

    myPet.getInfo();

    //after eating if we feed again
    myPet.eat(); //it will show that our pet is not hungry anymore

    //We can update weight too
    //before update Weight = 25
    myPet.updateWeight(26.7);
    //now weight = 26.7

    myPet.getInfo();

    return 0;
}