#define _WIN32_WINNT 0x0600 //for running the file rang.hpp for colored output
#include <iostream>
#include "rang.hpp"
#include <vector>
#include <fstream>
#include <sstream>
using namespace rang;
using namespace std;

class Patient
{
private:
    string name;
    int age;
    string gender;
    string disease;
    int patientID;
    int roomNo;

public:

    //Default Constructor
    Patient()
    {
        name = " ";
        age = 0;
        gender = " ";
        disease = " ";
        patientID = 0;
        roomNo = 0;
    }

    Patient(string name, int age, string gender, string disease, int patientID, int rommNo)
    {
        this -> name = name;
        this -> age = age;
        this -> gender = gender;
        this -> disease = disease;
        this -> patientID = patientID;
        this -> roomNo = roomNo;
    }

    //Search utility and return patient ID
    int getID()
    {
        return patientID;
    }

    //Update any Details
    void updateDetails(string disease, int roomNo, int age)
    {
       this -> disease = disease;
       this -> roomNo = roomNo;
       this -> age = age; 
       cout << fg::green << "Patient Info Updated Successfully! ✅ \n";
    }

    //For Displaying details
    void displayDetails()
    {
        cout << fg::cyan << "\n-------------------------------\n";
        cout << fg::green << "Name         : "<< name << endl;
        cout << fg::green << "Age          : "<< age << endl;
        cout << fg::green << "Gender       : "<< gender << endl;
        cout << fg::green << "Disease      : "<< disease << endl;
        cout << fg::green << "Patient Id   : "<< patientID << endl;
        cout << fg::green << "Room No.     : "<< roomNo << endl;
        cout << fg::cyan << "\n-------------------------------\n";
    }

    void saveToFile(ofstream &file) const
    {
        file << name << "," << age << "," << gender << "," << disease << "," << patientID << "," << roomNo << "\n";
    }

};

void pause()
{
    cout << fg::yellow << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void loadPatients(vector<Patient> &records)
{
    ifstream file("patients.txt");
    if(!file) return;

    string name, gender, disease;
    int age, id, room;
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, name, ',');
        ss >> age;
        ss.ignore();
        getline(ss, gender, ',');
        getline(ss, disease, ',');
        ss >> id;
        ss.ignore();
        ss >> room;

        records.push_back(Patient(name, age, gender, disease, id, room));
    }

    file.close();
}

void rewriteAllToFile(const vector<Patient> &records)
{
    ofstream file("patients.txt");
    for(const Patient &p: records)
    {
        p.saveToFile(file);
    }
    file.close();
}

int main()
{
    system("chcp 65001");//for getting emojis in terminal output

    vector <Patient> records;

    loadPatients(records);
    cout<<"\n📂 Patient data loaded from file.\n";

    int choice;

    do 
    {
        cout << fg::magenta << "\n=========== 🏥 Hospital Patient Record System ===========\n";
        cout << fg::cyan << "1. Add New Patient\n";
        cout << fg::cyan << "2. Display All Patient\n";
        cout << fg::cyan << "3. Search Patient by ID\n";
        cout << fg::cyan << "4. Update Patient Info\n";
        cout << fg::cyan << "5. Exit\n";

        cout<< fg::yellow << "\nChoose an Option: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                string name, gender, disease;
                int age, id, room;

                cout << fg::blue << "Enter Patient Name: ";
                cin.ignore();
                getline(cin, name);

                cout << fg::blue << "Enter Patient Age: ";
                cin >> age;

                cout << fg::blue << "Enter Gender: ";
                cin >> gender;

                cout << fg::blue << "Enter Disease: ";
                cin >> disease;

                cout << fg::blue << "Enter patient ID: ";
                cin >> id;

                cout << fg::blue << "Enter Room Number: ";
                cin >> room;

                Patient newPatient(name, age, gender, disease, id, room);
                records.push_back(newPatient);

                //saving to file
                ofstream outFile("patients.txt", ios::app);
                newPatient.saveToFile(outFile);
                outFile.close();

                cout << fg::green << "✅ Patient added successfully!\n";
                pause();
                break;
            }
            case 2:
            {
                if(records.empty())
                {
                    cout << fg::red << "⚠️ No patient records found.\n";
                }
                else
                {
                    cout << fg::magenta << "\n📃 List of Patients:\n";
                    for(Patient p: records)
                    {
                        p.displayDetails();
                    }
                }
                pause();
                break;
            }
            case 3:
            {
                int searchID;
                bool found = false;
                cout << fg::yellow << "Enter Patient ID to search: ";
                cin >> searchID;

                for(Patient p: records)
                {
                    if(p.getID() == searchID)
                    {
                        cout << fg::green << "🔍 Patient found:\n";
                        p.displayDetails();
                        found = true;
                        break;
                    }
                }
                if(!found)
                {
                    cout << fg::red << "❌ No patient with ID "<< searchID << " found.\n";

                }
                pause();
                break;
            }

            case 4:
            {
                int updateID;
                cout << fg::yellow << "Enter Patient ID to Update: ";
                cin >> updateID;
                bool updated = false;

                for (Patient &p: records)
                {
                    if(p.getID() == updateID)
                    {
                        string newDisease;
                        int newRoom, newAge;

                        cout << fg::blue << "Enter new Disease: ";
                        cin >> newDisease;

                        cout << fg::blue << "Enter new Room No.: ";
                        cin >> newRoom;

                        cout << fg::blue << "Enter new Age: ";
                        cin >> newAge;

                        p.updateDetails(newDisease, newRoom, newAge);
                        updated = true;
                        break;
                    }
                }
                rewriteAllToFile(records);

                if(!updated)
                    cout << fg::red << "❌ Patient not found for update.\n";

                pause();
                break;
            }

            case 5:
                cout << fg::cyan << "👋 Exiting the program. Stay healthy!\n";
                break;

            default:
                cout << fg::red << "⚠️ Invalid choice. Try again.\n";
                pause();
        }
    }while (choice != 5);

    return 0;
}