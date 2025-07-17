#define _WIN32_WINNT 0x0600 //for running the file rang.hpp for colored output
#include <iostream>
#include "rang.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;
using namespace rang;

string getCurrentTimestamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%d-%m-%Y %I:%M %p", ltm);
    return string(timestamp);
}

class Doctor {
private:
    int id;
    string name;
    string specialization;
    string contact;
    string shift;
    string addedOn;
    bool availability;

public:
    Doctor() {}

    void inputDetails(int doctorID) {
        id = doctorID;
        cin.ignore();
        cout << fg::yellow << "Enter Name: ";
        getline(cin, name);
        cout << fg::yellow << "Enter Specialization: ";
        getline(cin, specialization);
        cout << fg::yellow<< "Enter Contact: ";
        getline(cin, contact);
        shift = "Not Assigned";
        availability = true;
        addedOn = getCurrentTimestamp();
    }

    void displayDetails() const {
        cout << fg::magenta << "\n---------- Doctor Details --------------\n";
        cout<< fg::cyan << "\n🩺 Doctor ID      : " << id
             << "\n👤 Name           : " << name
             << "\n🔬 Specialization : " << specialization
             << "\n📞 Contact        : " << contact
             << "\n⏰ Shift          : " << shift
             << "\n🟢 Availability   : " << (availability ? "Available" : "Not Available") 
             << "\n📅 Added On       : " << addedOn << endl;
    }

    void assignShift(const string& newShift) {
        shift = newShift;
        cout << fg::green << "✅ Shift assigned successfully.\n";
    }

    void updateContact(const string& newContact) {
        contact = newContact;
        cout << fg::green << "📞 Contact updated.\n";
    }

    void toggleAvailability() {
        availability = !availability;
        cout << fg::green << "🟢 Availability toggled.\n";
    }

    string getName() const { return name; }
    int getID() const { return id; }
    string getShift() const { return shift; }
    bool isAvailable() const { return availability; }

    void saveToFile(ofstream& out) const {
        out << id << "|" << name << "|" << specialization << "|" << contact << "|" << shift << "|" << availability << "|" << addedOn << "\n";
    }

    void loadFromLine(const string& line) {
        size_t pos = 0, last = 0;
        vector<string> tokens;
        while ((pos = line.find('|', last)) != string::npos) {
            tokens.push_back(line.substr(last, pos - last));
            last = pos + 1;
        }
        tokens.push_back(line.substr(last));

        if (tokens.size() == 7) {
            id = stoi(tokens[0]);
            name = tokens[1];
            specialization = tokens[2];
            contact = tokens[3];
            shift = tokens[4];
            availability = stoi(tokens[5]);
            addedOn = tokens[6];
        }
    }
};

// === Utility Functions ===

void pause()
{
    cout << fg::yellow << "Press Any key to Continue...";
    cin.ignore();
    cin.get();
    system("cls"); //for windows only (clears screen)
}

bool shiftConflict(const vector<Doctor>& doctors, const string& shift, const string& specialization) {
    for (const auto& doc : doctors) {
        if (doc.getShift() == shift && doc.isAvailable()) {
            return false; // at least one doctor already assigned, allow
        }
    }
    return true; // no one yet, allow
}

void saveDoctorsToFile(const vector<Doctor>& doctors, const string& filename) {
    ofstream out(filename);
    for (const auto& doc : doctors) {
        doc.saveToFile(out);
    }
    out.close();
    cout << fg::green << "💾 Data saved to file successfully.\n";
}

void loadDoctorsFromFile(vector<Doctor>& doctors, int& nextID, const string& filename) {
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        Doctor d;
        d.loadFromLine(line);
        doctors.push_back(d);
        nextID = max(nextID, d.getID() + 1);
    }
    in.close();
}

int main() {

    system("chcp 65001");
    system("cls");
    vector<Doctor> doctors;
    int nextID = 1000;
    string filename = "04_doctors.txt";
    loadDoctorsFromFile(doctors, nextID, filename);

    int choice;
    do {
        cout << fg::magenta << "\n===== Doctor Scheduling System =====\n";
        cout << fg::cyan << "1. ➕ Add Doctor\n";
        cout << "2. 📋 Show All Doctors\n";
        cout << "3. 🔄 Assign Shift\n";
        cout << "4. 🔍 Search Doctor by Name\n";
        cout << "5. 🟢 Toggle Availability\n";
        cout << "6. 📞 Update Contact\n";
        cout << "7. 💾 Save to File\n";
        cout << "8. ❌ Exit\n";
        cout << fg::yellow << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Doctor d;
                d.inputDetails(nextID++);
                doctors.push_back(d);
                saveDoctorsToFile(doctors, filename);
                pause();
                break;
            }

            case 2: {
                if (doctors.empty()) cout << fg::red << "No doctors added yet.\n";
                else for (const auto& doc : doctors) doc.displayDetails();
                pause();
                break;
            }

            case 3: {
                int id;
                string shift;
                cout << fg::blue << "Enter Doctor ID: ";
                cin >> id;
                cout << "Enter Shift (Morning/Evening): ";
                cin >> shift;

                bool found = false;
                for (auto& doc : doctors) {
                    if (doc.getID() == id) {
                        doc.assignShift(shift);
                        found = true;
                        break;
                    }
                }
                if (!found) cout << fg::red << "Doctor not found.\n";
                else saveDoctorsToFile(doctors, filename);

                pause();
                break;
            }

            case 4: {
                cin.ignore();
                string name;
                cout << fg::yellow << "Enter Doctor Name to search: ";
                getline(cin, name);

                bool found = false;
                for (auto& doc : doctors) {
                    if (doc.getName() == name) {
                        doc.displayDetails();
                        found = true;
                    }
                }
                if (!found) cout << fg::red << "Doctor not found.\n";
                pause();
                break;
            }

            case 5: {
                int id;
                cout << fg::yellow << "Enter Doctor ID to toggle availability: ";
                cin >> id;

                bool found = false;
                for (auto& doc : doctors) {
                    if (doc.getID() == id) {
                        doc.toggleAvailability();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << fg::red << "Doctor not found.\n";
                else saveDoctorsToFile(doctors, filename);

                pause();
                break;
            }

            case 6: {
                int id;
                string newContact;
                cout << fg::blue << "Enter Doctor ID: ";
                cin >> id;
                cin.ignore();
                cout << fg::yellow << "Enter new contact: ";
                getline(cin, newContact);

                bool found = false;
                for (auto& doc : doctors) {
                    if (doc.getID() == id) {
                        doc.updateContact(newContact);
                        found = true;
                        break;
                    }
                }
                if (!found) cout << fg::yellow << "Doctor not found.\n";
                else saveDoctorsToFile(doctors, filename);
                pause();
                break;
            }

            case 7:
                saveDoctorsToFile(doctors, filename);
                pause();
                break;

            case 8:
                cout << fg::green << "👋 Exiting program. Goodbye!\n";
                break;

            default:
                cout << fg::red << "❌ Invalid choice.\n";
                pause();
        }

    } while (choice != 8);

    return 0;
}