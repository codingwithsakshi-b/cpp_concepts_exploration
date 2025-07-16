#define _WIN32_WINNT 0x0600 //for running the file rang.hpp for colored output
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>
#include "rang.hpp"
using namespace rang;
using namespace std;

void pause()
{
    cout << fg::yellow << "Press Any key to Continue...";
    cin.ignore();
    cin.get();
    system("cls"); //for windows only (clears screen)
}

class Appointment
{
private:
    static int idCounter;

    string generatePatientID()
    {
        stringstream ss;
        ss << "APT" << setfill('0') << setw(3) << ++idCounter;
        return ss.str();
    }

public:
    string patientID;
    string patientName;
    string doctorName;
    string date;
    string time;
    string purpose;

    //Default Constructor
    Appointment()
    {
        patientID = generatePatientID();
        patientName = doctorName = date = time = purpose = "none";
    }

    Appointment(string patientName, string doctorName , string date, string time, string purpose)
    {
        this -> patientID = generatePatientID();
        this -> patientName = patientName;
        this -> doctorName = doctorName;
        this -> date = date;
        this -> time = time;
        this -> purpose = purpose;
    }

    //for getting information
    void input()
    {
        cout << fg::magenta << "\n---- Enter Appointment Details ----\n";

        cout << fg::cyan << "Generated Patient ID: " << generatePatientID() << endl;;
        patientID = generatePatientID();

        cout << fg::cyan << "Patient Name: ";
        getline(cin >> ws, patientName);

        cout << fg::cyan << "Doctor Name: ";
        getline(cin >> ws, doctorName);

        cout << fg::cyan << "Date (DD-MM-YYYY): ";
        getline(cin >> ws, date);

        cout << fg::cyan << "Time (HH:MM): ";
        getline(cin >> ws, time);

        cout << fg::cyan << "Purpose of Visit: ";
        getline(cin >> ws, purpose);
    }

    //for displaying info
    void display() const
    {
        cout << fg::magenta << "\n---------- 📅 Appointment Details ----------\n";
        cout << fg::cyan << "Patient ID       : " << patientID << endl;
        cout << fg::cyan << "Patient Name     : " << patientName << endl;
        cout << fg::cyan << "Doctor Name      : " << doctorName << endl;
        cout << fg::cyan << "Date             : " << date << " (" << getDayOfWeek() << ")" << endl;
        cout << fg::cyan << "Time             : " << time << endl;
        cout << fg::cyan << "Purpose          : " << purpose << endl;
    }

    //for rescheduling appointment
    void reSchedule(const string& newDate, const string& newTime)
    {
        date = newDate;
        time = newTime;
    }

    string getDayOfWeek() const
    {
        int day, month, year;
        sscanf(date.c_str(), "%d-%d-%d", &day, &month, &year);

        tm timeStruct = {};
        timeStruct.tm_mday = day;
        timeStruct.tm_mon = month - 1;
        timeStruct.tm_year = year - 1900;

        mktime(&timeStruct);

        const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thrusday", "Friday", "Saturday"};
        return days[timeStruct.tm_wday];
    }

    string toCSV() const
    {
        return patientID + "," + patientName + "," + doctorName + "," + date + "," + time + "," + purpose;
    }
};

//static variable initialize
int Appointment::idCounter = 0;

//--------------------- Global Appointment Vector ---------------------
vector <Appointment> appointmentList;

void showMenu()
{
    cout << fg::magenta << "\n======== 🏥 APPOINTMENT MENU ========\n";
    cout << fg::cyan << "1. Add New Appointment\n";
    cout << "2. Display All Appointment\n";
    cout << "3. Reschedule Appointment\n";
    cout << "4. Save All Appointment to File\n";
    cout << "5. Search Appointment by Date or Doctor Name\n";
    cout << "6. Exit\n";
    cout << fg::yellow << "\nEnter Your Choice(1-5): ";
}

void saveToFile() {
    ofstream file("appointments.csv");
    for (const auto& appt : appointmentList) {
        file << appt.toCSV() << "\n";
    }
    file.close();
    cout << fg::green << "✅ Appointments saved to 'appointments.csv'\n";
}

bool isPastDate(const string& date) {
    int d, m, y;
    sscanf(date.c_str(), "%d-%d-%d", &d, &m, &y);

    time_t now = time(0);
    tm* curr = localtime(&now);

    if (y < curr->tm_year + 1900) return true;
    if (y == curr->tm_year + 1900 && m < curr->tm_mon + 1) return true;
    if (y == curr->tm_year + 1900 && m == curr->tm_mon + 1 && d < curr->tm_mday) return true;

    return false;
}

void autoTrash() {
    ofstream trashFile("trashed_appointments.csv", ios::app); // store old appointments
    vector<Appointment> updatedList;

    for (const auto& appt : appointmentList) {
        if (isPastDate(appt.date)) {
            trashFile << appt.toCSV() << "\n"; // move to trash
        } else {
            updatedList.push_back(appt); // keep future appointments
        }
    }

    trashFile.close();
    appointmentList = updatedList; // keep only future appointments

    // Overwrite main appointments.csv file
    saveToFile();

    cout << fg::yellow << "🧹 Old appointments trashed successfully!\n";
}


void addAppointment()
{
    Appointment a;
    a.input();
    appointmentList.push_back(a);
    
    ofstream file("appointments.csv", ios::app);
    if(file.is_open())
    {
        file << a.toCSV() << "\n";
        file.close();

        cout << fg::green << "✅ Appointment added Successfully!\n";
        pause();
    }
    else
    {
        cout << fg::red << "❌ Failed to open file for saving.\n";
        pause();
    }
}

void displayAppointments()
{
    if(appointmentList.empty())
    {
        cout << fg::red << "⚠️ No appointments available.\n";
        pause();
        return;
    }
    for (const auto& appt : appointmentList)
    {
        appt.display();
    }
    pause();
}

void rescheduleAppointment()
{
    if(appointmentList.empty())
    {
        cout << fg::red << "⚠️ No appointments available.\n";
        return;
    }

    string id;
    cout << fg::blue << "Enter Appointment ID to reschedule: ";
    getline(cin >> ws, id);

    bool found = false;
    for(auto& appt : appointmentList)
    {
        if(appt.patientID == id)
        {
            string newDate, newTime;
            cout << fg::yellow << "New Date (DD-MM-YYYY): ";
            getline(cin >> ws, newDate);

            cout << fg::yellow << "New Time (HH:MM): ";
            getline(cin >> ws, newTime);

            appt.reSchedule(newDate, newTime);
            cout << fg::green << "✅ Appointment Rescheduled!\n";
            
            saveToFile();

            pause();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << fg::red << "❌ Appointment ID not found!\n";
        pause();
    }
}

void searchAppointments()
{
    if (appointmentList.empty())
    {
        cout << fg::red << "⚠️ No appointments to search.\n";
        return;
    }

    int choice;
    cout << fg::cyan << "\nSearch by:\n1. Date\n2. Doctor Name\nEnter Choice: ";
    cin >>choice;
    cin.ignore();

    string input;
    bool found = false;

    if(choice == 1)
    {
        cout << "Enter Date (DD-MM-YYYY): ";
        getline(cin >> ws, input);

        for(const auto& appt : appointmentList)
        {
            if(appt.date == input)
            {
                appt.display();
                found = true;
            }
        }
    }
    else if(choice == 2)
    {
        cout << "Enter Doctor Name: ";
        getline(cin >> ws, input);
        for(const auto& appt : appointmentList)
        {
            if(appt.doctorName == input)
            {
                appt.display();
                found = true;
            }
        }
    }
    else 
    {
        cout << fg::red <<  "❌ Invalid search option!\n";
        pause();
        return;
    }

    if (!found)
        cout << fg::red << "❌ No matching appointments found.\n";
    pause();
}

void loadFromFile() {
    ifstream file("appointments.csv");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, doctor, date, time, purpose;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, doctor, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');
        getline(ss, purpose, ',');

        Appointment appt;
        appt.patientID = id;
        appt.patientName = name;
        appt.doctorName = doctor;
        appt.date = date;
        appt.time = time;
        appt.purpose = purpose;

        appointmentList.push_back(appt);
    }
    file.close();
    cout << fg::green << "📂 Appointments loaded from file.\n";
}

int main() {
    system("chcp 65001");
    system("cls");

    loadFromFile();
    autoTrash(); 

    int choice;
    
    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addAppointment(); break;
            case 2: displayAppointments(); break;
            case 3: rescheduleAppointment(); break;
            case 4: saveToFile(); break;
            case 5: searchAppointments(); break;
            case 6: cout << fg::cyan << "👋 Exiting system. Bye Sakshi!\n"; break;
            
            default: cout << fg::red << "❌ Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}