#define _WIN32_WINNT 0x0600
#include <iostream>
#include "rang.hpp"
using namespace rang;
using namespace std;

class Laptop
{
public:
    string brand;
    string model;
    int ramSize;        // in GB
    int storageSize;    // in GB
    string processor;
    float price;

    //default constructor
    Laptop()
    {
        //default constructor
    }

    // CONSTRUCTOR

    //THIS KEYWORD USE HERE
    //if we want to keep attribute same as attribute in constructor means b == brand;
    Laptop(string brand, string model, int ramSize, int storageSize, string processor, float price) 
    {
        this -> brand = brand;
        this -> model = model;
        this -> ramSize = ramSize;
        this -> storageSize = storageSize;
        this -> processor = processor;
        this -> price = price;
    }
};

void displayInfo(Laptop l) 
{
        cout << fg::cyan << "# 🏷️ Brand: " << l.brand << endl;
        cout << fg::cyan << "# 🧾 Model: " << l.model << endl;
        cout << fg::cyan << "# 💾 RAM: " << l.ramSize << " GB" << endl;
        cout << fg::cyan << "# 🗄️ Storage: " << l.storageSize << " GB" << endl;
        cout << fg::cyan << "# 🖥️ Processor: " << l.processor << endl;
        cout << fg::cyan << "# 💸 Price: $" << l.price << endl;
}

int main()
{
    system("chcp 65001");

    //object 
    cout<<fg::magenta << "\nMine Laptop INFO : \n";

    //without THIS keyword it print like some garbage values
    // Mine Laptop INFO : 
    // # 🏷️ Brand: 
    // # 🧾 Model: 
    // # 💾 RAM: 0 GB
    // # 🗄️ Storage: 4199136 GB
    // # 🖥️ Processor: 
    // # 💸 Price: $0

    Laptop l1("ASUS LAPTOP", "VIVOBOOK 16", 16, 512, "Core Ultra 5", 840.0);

    displayInfo(l1);

    //After Using THIS keyword
    // Mine Laptop INFO : 
    // # 🏷️ Brand: ASUS LAPTOP
    // # 🧾 Model: VIVOBOOK 16
    // # 💾 RAM: 16 GB
    // # 🗄️ Storage: 512 GB
    // # 🖥️ Processor: Core Ultra 5
    // # 💸 Price: $840

    return 0;
}