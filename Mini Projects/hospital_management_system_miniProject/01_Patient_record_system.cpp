#define _WIN32_WINNT 0x0600
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "rang.hpp"
using namespace std;
using namespace rang;

class Patient {
public:
    string patientID;
    string name;
    int age;
    string gender;
    string disease;
    long long contactNumber;

    Patient() : patientID(""), name(""), age(0), gender(""), disease(""), contactNumber(0) {}

    Patient(string id, string name, int age, string gender, string disease, long long contactNumber)
        : patientID(id), name(name), age(age), gender(gender), disease(disease), contactNumber(contactNumber) {}

    void displayDetails() const {
        cout << fg::cyan << "\n-------------------------------\n";
        cout << fg::green << "Patient ID     : " << patientID << "\n";
        cout << fg::green << "Name           : " << name << "\n";
        cout << fg::green << "Age            : " << age << "\n";
        cout << fg::green << "Gender         : " << gender << "\n";
        cout << fg::green << "Disease        : " << disease << "\n";
        cout << fg::green << "Contact Number : " << contactNumber << "\n";
        cout << fg::cyan << "-------------------------------\n";
    }

    void saveToFile(ofstream& file) const {
        file << patientID << "," << name << "," << age << "," << gender << "," << disease << "," << contactNumber << "\n";
    }
};

string generateUniquePatientID(const vector<Patient>& patients) {
    int maxID = 0;
    for (const auto& p : patients) {
        if (p.patientID.find("PAT2025_") == 0) {
            int num = stoi(p.patientID.substr(9));
            if (num > maxID) maxID = num;
        }
    }
    stringstream ss;
    ss << "PAT2025_" << setw(3) << setfill('0') << (maxID + 1);
    return ss.str();
}

void loadPatients(vector<Patient>& patients) {
    ifstream file("01_patients.txt");
    if (!file) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, gender, disease;
        int age;
        long long contact;

        getline(ss, id, ',');
        getline(ss, name, ',');
        ss >> age;
        ss.ignore();
        getline(ss, gender, ',');
        getline(ss, disease, ',');
        ss >> contact;

        patients.push_back(Patient(id, name, age, gender, disease, contact));
    }
    file.close();
}

void saveAllPatients(const vector<Patient>& patients) {
    ofstream file("01_patients.txt");
    for (const auto& p : patients) {
        p.saveToFile(file);
    }
    file.close();
}

void pause() {
    cout << fg::yellow << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    system("cls");
}

int main() {
    system("chcp 65001 > nul");
    system("cls");

    vector<Patient> patients;
    loadPatients(patients);
    cout << fg::green << "📂 Patients loaded from file.\n";

    int choice;

    do {
        cout << fg::magenta << "\n=========== 🏥 Hospital Patient Record System ===========\n";
        cout << fg::cyan << "1. Add New Patient\n";
        cout << fg::cyan << "2. View All Patients\n";
        cout << fg::cyan << "3. Search Patient by ID\n";
        cout << fg::cyan << "4. Update Patient Info\n";
        cout << fg::cyan << "5. Exit\n";
        cout << fg::yellow << "Enter Your Choice: ";
        cin >> choice;

        cin.ignore();  // flush buffer

        switch (choice) {
            case 1: {
                string name, gender, disease;
                int age;
                long long contact;

                cout << fg::blue << "Enter Patient Name       : ";
                getline(cin, name);

                cout << fg::blue << "Enter Age                : ";
                cin >> age;

                cout << fg::blue << "Enter Gender             : ";
                cin >> gender;

                cout << fg::blue << "Enter Disease            : ";
                cin.ignore();
                getline(cin, disease);

                cout << fg::blue << "Enter Contact Number     : ";
                cin >> contact;

                string id = generateUniquePatientID(patients);
                Patient newP(id, name, age, gender, disease, contact);
                patients.push_back(newP);

                ofstream outFile("01_patients.txt", ios::app);
                newP.saveToFile(outFile);
                outFile.close();

                cout << fg::green << "✅ Patient added successfully! ID: " << id << "\n";
                pause();
                break;
            }

            case 2: {
                if (patients.empty()) {
                    cout << fg::red << "⚠️ No patient records found.\n";
                } else {
                    for (const auto& p : patients) {
                        p.displayDetails();
                    }
                }
                pause();
                break;
            }

            case 3: {
                string searchID;
                bool found = false;
                cout << fg::yellow << "Enter Patient ID to search: ";
                getline(cin, searchID);

                for (const auto& p : patients) {
                    if (p.patientID == searchID) {
                        cout << fg::green << "🔍 Patient Found:\n";
                        p.displayDetails();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << fg::red << "❌ No patient with ID " << searchID << " found.\n";
                }
                pause();
                break;
            }

            case 4: {
                string updateID;
                bool updated = false;
                cout << fg::yellow << "Enter Patient ID to update: ";
                getline(cin, updateID);

                for (auto& p : patients) {
                    if (p.patientID == updateID) {
                        cout << fg::blue << "Enter new Disease        : ";
                        getline(cin, p.disease);

                        cout << fg::blue << "Enter new Contact Number : ";
                        cin >> p.contactNumber;

                        cout << fg::blue << "Enter new Age            : ";
                        cin >> p.age;

                        updated = true;
                        cout << fg::green << "✅ Patient info updated successfully!\n";
                        break;
                    }
                }

                if (!updated) {
                    cout << fg::red << "❌ No patient with that ID found.\n";
                }

                saveAllPatients(patients);
                pause();
                break;
            }

            case 5:
                cout << fg::green << "👋 Exiting. Stay healthy!\n";
                break;

            default:
                cout << fg::red << "⚠️ Invalid choice. Try again.\n";
                pause();
        }

    } while (choice != 5);

    return 0;
}