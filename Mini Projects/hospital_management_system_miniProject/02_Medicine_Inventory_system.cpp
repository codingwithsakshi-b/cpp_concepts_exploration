#define _WIN32_WINNT 0x0600 //for running the file rang.hpp for colored output
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include "rang.hpp"
using namespace rang;
using namespace std;

class Medicine
{
public:
    string name;           //Medicine name
    string id;             //Unique code or ID
    string expiryDate;     //Format: DD-MM-YYYY
    int quantity;          //Number of units in stocks
    float pricePerUnit;    //cost per unit
    string manufacturer;   //Company Name

    //DEFAULT CONSTRUCTOR
    Medicine()
    {
        name = "";
        id = "";
        expiryDate = "";
        quantity = 0;
        pricePerUnit = 0.0;
        manufacturer = "";
    }

    //Parameterized Constructor
    Medicine(string name, string id, string expiryDate, int quantity, float pricePerUnit,
    string manufacturer)
    {
        this -> name = name;
        this -> id = id;
        this -> expiryDate = expiryDate;
        this -> quantity = quantity;
        this -> pricePerUnit = pricePerUnit;
        this -> manufacturer = manufacturer;
    }

    //For adding Medicine Info
    void Input()
    {
        cout << fg::magenta << "\n-----Enter Medicine Details-----\n";

        cout << fg::yellow << "Enter Medicine Name: ";
        getline(cin >> ws, name);

        cout << fg::yellow << "Enter Medicine ID: ";
        getline(cin >> ws, id);

        cout << fg::yellow << "Enter Medicine Expiry Date(DD-MM-YYY): ";
        getline(cin >> ws, expiryDate);


        cout << fg::yellow << "Quantity: ";
        cin >> quantity;

        cout << fg::yellow << "Price Per Unit: ";
        cin >> pricePerUnit;

        cout << fg::yellow << "Manufacturer Name: ";
        getline(cin >> ws, manufacturer);
    }

    //For Displaying Details 
    void display() const
    {
        cout << fg::magenta << "\n---------------------------------------------------\n";
        cout << fg::cyan << "Medicine Name      : " << name << endl;
        cout << fg::cyan << "ID                 : " << id << endl;
        cout << fg::cyan << "Expiry Date        : " << expiryDate << endl;
        cout << fg::cyan << "Quantity           : " << quantity << endl;
        cout << fg::cyan << "Price Per Unit     : " << pricePerUnit << " ₹" << endl;
        cout << fg::cyan << "Manufacturer Name  : " << manufacturer << endl;
    }

    //for updating Quantity
    void updateQuantity(int newQty)
    {
        quantity = newQty;
        cout << fg::green << "✅ Quantity Updated to " << quantity << endl;
    }

    //For Updating Price
    void updatePrice(float newPrice)
    {
        pricePerUnit = newPrice;
        cout << fg::green << "✅ Price Updated to ₹" << pricePerUnit << endl;
    }

    // Placeholder: Check expiry (we’ll improve later)
    bool isExpired() const {
        int day, month, year;

        //parse expiry date from string
        sscanf(expiryDate.c_str(), "%d-%d-%d", &day, &month, &year);

        //Get current system date
        time_t now = time(0);
        tm *ltm = localtime(&now);

        int currentDay = ltm->tm_mday;
        int currentMonth = 1 + ltm->tm_mon;
        int currentYear = 1900 + ltm->tm_year;

        //compare dates
        if(year < currentYear) return true;
        else if(year == currentYear && month < currentMonth) return true;
        else if(year == currentYear && month == currentMonth && day < currentDay) return true;
        else return false;
    }
};

void saveToFile(const vector<Medicine> & inventory)
{
    ofstream fout("Medicines.txt");
    if(!fout)
    {
        cout << fg::red << "❌ Error Opening file for Writing!\n";
        return;
    }

    for(const auto &med : inventory)
    {
        fout << med.name << "," << med.id << "," << med.expiryDate << "," << med.quantity << "," << med.pricePerUnit << "," << med.manufacturer << "\n";
    }

    fout.close();
    cout << fg::green << "✅ Data Saved to 'medicines.txt' \n";
}

void loadFromFile(vector<Medicine>& inventory)
{
    ifstream fin("medicines.txt");
    if(!fin)
    {
        cout << fg::red << "❌ File not found! Starting with empty inventory.\n";
        return;
    }

    inventory.clear();
    string line;

    while (getline(fin, line))
    {
        stringstream ss(line);
        string name, id, expiry, manufacturer;
        int quantity;
        float price;

        getline(ss, name, ',');
        getline(ss, id, ',');
        getline(ss, expiry, ',');
        ss >> quantity;
        ss.ignore();
        ss >> price;
        ss.ignore();
        getline(ss, manufacturer);

        inventory.push_back(Medicine(name, id, expiry, quantity, price, manufacturer));
    }
    fin.close();
    cout << fg::green << "\n✅ Data Loaded from 'medicines.txt'\n";
}

void pause()
{
    cout << fg::yellow << "Press Any key to Continue...";
    cin.ignore();
    cin.get();
    system("cls"); //for windows only (clears screen)
}

void deleteMedicine(vector<Medicine>& inventory)
{
    string id;
    cout << fg::yellow << "Enter Medicine ID to delete: ";
    cin >> id;

    auto it = find_if(inventory.begin(), inventory.end(), [&id](const Medicine& m) {
        return m.id == id;
    });

    if (it != inventory.end())
    {
        char confirm;
        cout << fg::red << "Are you sure you want to delete " << it->name << "? (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y')
        {
            // Save to trash
            ofstream trash("trashed_medicines.txt", ios::app);
            if (trash.is_open())
            {
                trash << it->name << "," << it->id << "," << it->expiryDate << ","
                      << it->quantity << "," << it->pricePerUnit << "," << it->manufacturer << "\n";
                trash.close();
            }

            // Erase from inventory
            inventory.erase(it);

            // ✅ Save updated inventory to file
            saveToFile(inventory);

            cout << fg::green << "✅ Medicine deleted and moved to trash.\n";
        }
        else
        {
            cout << fg::cyan << "Deletion cancelled.\n";
        }
    }
    else
    {
        cout << fg::red << "❌ Medicine with ID " << id << " not found!\n";
    }
}


int main()
{
    system("chcp 65001");//for getting emojis in terminal output

    vector <Medicine> inventory;
    loadFromFile(inventory);
    int choice;

    while(true)
    {
        cout << fg::magenta << "\n========💊 Medicine Inventory Menu========\n";
        cout << fg::cyan << "1. Add Medicine\n";
        cout << fg::cyan << "2. Display All Medicine\n";
        cout << fg::cyan << "3. Update Quantity\n";
        cout << fg::cyan << "4. Update Price\n";
        cout << fg::cyan << "5. Show Expired Medicines\n";
        cout << fg::cyan << "6. Delete Medicines\n";
        cout << fg::cyan << "7. Exit\n";

        cout << fg::yellow << "\nEnter Your Choice(1-7): ";
        cin >> choice;

        if (choice == 1)
        {
            Medicine med;
            med.Input();
            inventory.push_back(med);
            saveToFile(inventory);
        }
        else if (choice == 2)
        {
            for(const auto& med: inventory)
            {
                if(!med.isExpired())
                {
                    med.display();
                }
                else
                {
                    cout<<fg::red <<endl;
                    med.display();
                    cout << fg::red << med.name << "(❌ Expired)\n";
                }
            }
        }
        else if (choice == 3)
        {
            string id;
            int newQty;

            cout << fg::cyan << "Enter Medicine ID to Update Quantity: ";
            cin >> id;

            cout << fg::yellow << "Enter New Quantity: ";
            cin >> newQty;

            bool found = false;
            for (auto &med : inventory)
            {
                if(med.id == id)
                {
                    med.updateQuantity(newQty);
                    saveToFile(inventory);
                    found = true;
                    break;
                }
            }
            if(!found) cout << fg::red << "❌ Medicine Not Found!\n";
        }
        else if (choice == 4)
        {
            string id;
            float price;

            cout << fg::cyan << "Enter Medicine ID to Update Price: ";
            cin >> id;

            cout << fg::yellow << "Enter New Price: ";
            cin >> price;

            bool found = false;
            for (auto &med : inventory)
            {
                if(med.id == id)
                {
                    med.updatePrice(price);
                    saveToFile(inventory);
                    found = true;
                    break;
                }
            }
            if(!found) cout << fg::red << "❌ Medicine Not Found!\n";
        }
        else if(choice == 5)
        {
            bool found = false;
            for(const auto& med : inventory)
            {
                if(med.isExpired())
                {
                    med.display();
                    found = true;
                }
            }
            if(!found) cout << fg::green << "🎉 No Expired medicines found!\n";
        }
        else if(choice == 6)
        {
            deleteMedicine(inventory);
        }
        else if(choice == 7)
        {
            saveToFile(inventory); //save all data to file
            cout << fg::blue << "Exiting... Thank You 🙏.\n";
            break;
        }

        else 
        {
            cout << fg::red << "\n⚠️ Invalid Choice. Try Again\n";
        }

        pause();

    }

    return 0;
}