#define _WIN32_WINNT 0x0600 //for running the file rang.hpp for colored output
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "rang.hpp"
using namespace rang;
using namespace std;

class Room
{
public: 
    string roomNumber;
    int bedCount;
    int bedsOccupied;
    string roomType; //e.g. General ICU Private
    bool hasOxygenSupport;
    bool hasAC;
    vector <string> patientName;

    //Default Constructor
    Room()
    {
        roomNumber = bedCount = bedsOccupied = 0;
        roomType = "";
        hasOxygenSupport = hasAC = false;
    }

    //Creating Room
    void createRoom()
    {
        cout << fg::cyan << "\n-------------- Enter Room Details ----------------\n";
        
        cout << fg::blue << "Enter Room Number                     : ";
        getline(cin >> ws, roomNumber);
        
        cout << fg::blue << "Enter Total Beds                      : ";
        cin >> bedCount;

        cout << fg::blue << "Enter Room Type (General/ICU/Private) : ";
        getline(cin >> ws, roomType);
        
        char input;
        cout << fg::blue << "Oxygen Support (y/n)                  : ";
        cin >> input;
        hasOxygenSupport = (input == 'y' || input == 'Y'); 
        
        cout << fg::blue << "AC Available (y/n)                    : ";
        cin >> input;
        hasAC = (input == 'y' || input == 'Y');

        cout << fg::green << "✅ Room " << roomNumber << " Created Successfully!\n";
    }

    //Checl if beds are available or not
    bool isAvalable()
    {
        return bedsOccupied < bedCount;
    }

    //Assign a patient to a bed (by name)
    void assignBed(const string& patient) {
        if (bedsOccupied < bedCount) {
            patientName.push_back(patient);
            bedsOccupied++;
            cout << fg::green << "✅ Patient '" << patient << "' assigned to Room " << roomNumber << " successfully.\n";
        } else {
            cout << fg::red << "❌ No vacant beds available in Room " << roomNumber << ".\n";
        }
    }

    //Discharge a patient
    void dischargePatient(string patient)
    {
        for(int i = 0; i < patientName.size(); i++)
        {
            if(patientName[i] == patient)
            {
                patientName.erase(patientName.begin() + i);
                bedsOccupied--;
                cout << fg::green << "✅ Patient '" << patient << "' discharged from Room " << roomNumber << endl;
                return;
            }
        }
        cout << fg::red << "❌ Patient '" << patient << "' not found in Room " << roomNumber << endl;
    }

    //count available beds
    int availableBeds() const
    {
        return bedCount - bedsOccupied;
    }

    //Show Status
    void displayStatus()
    {
        cout << fg::magenta << "\n-------- Room Details --------\n";
        cout << fg::cyan << "Room Number         : " << roomNumber << endl;
        cout << fg::cyan << "Total Beds          : " << bedCount << endl;
        cout << fg::cyan << "Occupied beds       : " << bedsOccupied << endl;
        cout << fg::cyan << "Available Beds      : " << availableBeds() << endl;
        cout << fg::cyan << "Room Type           : " << roomType << endl;
        cout << fg::cyan << "Oxygen Suppport     : " << (hasOxygenSupport ? "Yes" : "No") << endl;
        cout << "AC Room             : " << (hasAC ? "Yes" : "No") << endl;
        cout << fg::cyan << "Patient Names: ";
        if(patientName.empty())
        {
            cout << "None";
        }
        else
        {
            for(auto name: patientName)
            {
                cout << name << " ";
            }
        }
    }

    string getRoomNumber() const
    {
        return roomNumber;
    }

    bool hasPatient(const string& name) const
    {
        for(const auto& p : patientName)
        {
            if(p == name)
                return true;
        }
        return false;
    }
};

void searchRoomByNumber(const vector<Room>& rooms, const string& roomNumber) {
    Room const* found = nullptr;
    // find the room
    for (auto const& r : rooms) {
        if (r.getRoomNumber() == roomNumber) {
            found = &r;
            break;
        }
    }

    if (!found) {
        cout << fg::red << "❌ Room " << roomNumber << " not found!\n";
        return;
    }

    // display room info
    cout << fg::magenta << "\n📘 Room Details:\n";
    cout << fg::cyan << "Room Number    : " << found->roomNumber   << "\n";
    cout << fg::cyan << "Room Type      : " << found->roomType     << "\n";
    cout << fg::cyan << "Total Beds     : " << found->bedCount     << "\n";
    cout << fg::cyan << "Occupied Beds  : " << found->bedsOccupied << "\n";
    cout << fg::cyan << "Vacant Beds    : " << found->availableBeds() << "\n";
    cout << fg::cyan << "Oxygen Support : " << (found->hasOxygenSupport ? "Yes" : "No") << "\n";
    cout << fg::cyan << "AC Available   : " << (found->hasAC            ? "Yes" : "No") << "\n";

    // list patients
    cout << fg::cyan << "Patients:\n";
    if (found->patientName.empty()) {
        cout << "  ⚠️ None\n";
    } else {
        for (int i = 0; i < found->patientName.size(); ++i) {
            cout << "  🛏 Bed " << (i+1)
                 << ": " << found->patientName[i] << "\n";
        }
    }
}

void pause()
{
    cout << fg::yellow << "Press Any key to Continue...";
    cin.ignore();
    cin.get();
    system("cls"); //for windows only (clears screen)
}

Room* findRoomByNumber (vector<Room>& rooms, string number)
{
    for(auto& r : rooms)
    {
        if(r.getRoomNumber() == number)
            return &r;
    }
    return nullptr;
}

void searchPatientByName(const vector<Room>& rooms, const string& name) {
    bool found = false;

    for (const auto& room : rooms) {
        for (int i = 0; i < room.patientName.size(); ++i) {
            if (room.patientName[i] == name) {
                if (!found) {
                    cout << fg::green << "\n🔍 All matches found:\n";
                }
                found = true;
                cout << fg::cyan 
                     << "✅ Room Number : " << room.roomNumber 
                     << " | Bed " << (i + 1) << " of " << room.bedCount
                     << " | Type: " << room.roomType 
                     << " | Oxygen: " << (room.hasOxygenSupport ? "Yes" : "No")
                     << " | AC: " << (room.hasAC ? "Yes" : "No") << "\n";
            }
        }
    }

    if (!found) {
        cout << fg::red << "❌ Patient '" << name << "' not found in any room.\n";
    }
}

void saveRoomsToFile(const vector<Room>& rooms, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << fg::red << "❌ Error Saving file.\n";
        return;
    }

    // Clean CSV header (no extra spaces!)
    file << "RoomNumber,BedCount,BedsOccupied,RoomType,Oxygen,AC,PatientNames\n";

    for (const auto& r : rooms) {
        // join patient names with '|', or "-" if none
        string patients = "-";
        if (!r.patientName.empty()) {
            patients.clear();
            for (size_t i = 0; i < r.patientName.size(); ++i) {
                patients += r.patientName[i];
                if (i + 1 < r.patientName.size()) 
                    patients += "|";
            }
        }

        file
          << r.roomNumber << ","
          << r.bedCount   << ","
          << r.bedsOccupied << ","
          << r.roomType   << ","
          << (r.hasOxygenSupport ? "1" : "0") << ","
          << (r.hasAC            ? "1" : "0") << ","
          << patients << "\n";
    }

    file.close();
    cout << fg::green << "💾 CSV saved to " << filename << " ✅\n";
}

void searchAndDischargePatient(vector<Room>& rooms, const string& nameToSearch) {
    vector<pair<int, int>> foundPatients; // (roomIndex, patientIndex)

    cout << fg::cyan << "\n🔍 Patients Found:\n";

    for (int i = 0; i < rooms.size(); ++i) {
        for (int j = 0; j < rooms[i].patientName.size(); ++j) {
            if (rooms[i].patientName[j] == nameToSearch) {
                foundPatients.push_back({i, j});
                cout << fg::yellow
                     << "👉 [" << foundPatients.size() << "] "
                     << "Room Number: " << rooms[i].roomNumber
                     << ", Bed: " << j + 1
                     << ", Name: " << rooms[i].patientName[j] << "\n";
            }
        }
    }

    if (foundPatients.empty()) {
        cout << fg::red << "❌ No patients found with the name '" << nameToSearch << "'.\n";
        return;
    }

    cout << fg::green << "\nEnter the number (1 - " << foundPatients.size() << ") to discharge that patient: ";
    int choice;
    cin >> choice;

    if (choice < 1 || choice > foundPatients.size()) {
        cout << fg::red << "❌ Invalid selection. Discharge cancelled.\n";
        return;
    }

    // Discharge selected patient
    int roomIdx = foundPatients[choice - 1].first;
    int patientIdx = foundPatients[choice - 1].second;

    string dischargedName = rooms[roomIdx].patientName[patientIdx];
    rooms[roomIdx].patientName.erase(rooms[roomIdx].patientName.begin() + patientIdx);
    rooms[roomIdx].bedsOccupied--;

    cout << fg::green << "✅ Patient '" << dischargedName
         << "' discharged from Room " << rooms[roomIdx].roomNumber << ".\n";

    saveRoomsToFile(rooms, "05_rooms.csv");
}
void loadRoomsFromFile(vector<Room>& rooms, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << fg::red << "⚠️ Error opening file for loading.\n";
        return;
    }

    rooms.clear();
    string line;

    // Skip exactly one header line
    if (!getline(file, line)) return;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);

        string roomNumStr, bedCountStr, bedsOccStr,
               roomTypeStr, oxygenStr, acStr, patientsStr;

        getline(ss, roomNumStr, ',');
        getline(ss, bedCountStr, ',');
        getline(ss, bedsOccStr, ',');
        getline(ss, roomTypeStr, ',');
        getline(ss, oxygenStr, ',');
        getline(ss, acStr, ',');
        getline(ss, patientsStr);

        Room r;
        r.roomNumber      = roomNumStr;
        r.bedCount        = stoi(bedCountStr);
        r.bedsOccupied    = stoi(bedsOccStr);
        r.roomType        = roomTypeStr;
        r.hasOxygenSupport= (oxygenStr == "1");
        r.hasAC           = (acStr     == "1");

        // split on '|'
        if (!patientsStr.empty() && patientsStr != "-") {
            string tmp;
            stringstream ps(patientsStr);
            while (getline(ps, tmp, '|'))
                if (!tmp.empty())
                    r.patientName.push_back(tmp);
        }

        rooms.push_back(r);
    }

    cout << fg::green << "✅ Rooms loaded successfully from file.\n";
}


void dischargePatientByName(vector<Room>& rooms, const string& name) {
    for (auto& r : rooms) {
        for (int i = 0; i < r.patientName.size(); i++) {
            if (r.patientName[i] == name) {
                r.patientName.erase(r.patientName.begin() + i);
                r.bedsOccupied--;
                cout << fg::green << "✅ Patient '" << name << "' discharged from Room " << r.roomNumber << ".\n";
                return;
            }
        }
    }
    cout << fg::red << "❌ Patient '" << name << "' not found in any room.\n";
}

void showVacantRooms(const vector<Room>& rooms) {
    cout << style::bold << fg::cyan << "\n🛏️ Rooms with Vacant Beds:\n" << style::reset;
    bool found = false;

    for (const auto& room : rooms) {
        if (room.bedsOccupied < room.bedCount) {
            found = true;
            cout << fg::blue << "🏠 Room No: " << room.roomNumber
                 << " | Total Beds: " << room.bedCount
                 << " | Occupied: " << room.bedsOccupied
                 << " | Room Type: " << room.roomType
                 << " | Vacant: " << (room.bedCount - room.bedsOccupied)
                 << " | Patients: ";

            if (room.patientName.empty()) {
                cout << "None";
            } else {
                for (const auto& p : room.patientName)
                    cout << p << " ";
            }
            cout << endl;
        }
    }

    if (!found) {
        cout << fg::yellow << "😕 No rooms with vacant beds found.\n";
    }
}

int getValidatedChoice() {
    int c;
    while (true) {
        cout << fg::yellow << "Enter Your Choice : ";
        if (cin >> c) {
            cin.ignore(10000, '\n');  // flush buffer
            return c;
        } else {
            cin.clear();              // clear error
            cin.ignore(10000, '\n');  // discard invalid input
            cout << fg::red << "❌ Invalid input. Please enter a number.\n";
        }
    }
}

int main()
{
    system("chcp 65001");//for getting emojis in terminal output
    system("cls");
    vector <Room> rooms;
    string filename = "05_rooms.csv";

    loadRoomsFromFile(rooms, filename);

    int choice;

    while(true)
    {
        cout << fg::magenta << "\n======== Hospital Room Management Menu ==========\n";
        cout << fg::cyan << "1. Add New Room\n";
        cout << fg::cyan << "2. View All Rooms\n";
        cout << fg::cyan << "3. Assign Patient to Room\n";
        cout << fg::cyan << "4. Search Patient by Name\n";
        cout << fg::cyan << "5. Show Rooms With Vacant Beds\n";
        cout << fg::cyan << "6. Room Details with RoomNumber\n";
        cout << fg::cyan << "7. Exit\n";

        choice = getValidatedChoice();

        if(choice == 1)
        {
            Room r;
            r.createRoom();
            rooms.push_back(r);
            saveRoomsToFile(rooms, filename);
            pause();
        }
        else if(choice == 2)
        {
            if(rooms.empty())
            {
                cout << fg::red << "❌ No Rooms added yet!\n";
                pause();
            }
            else 
            {
                for(auto& r : rooms)
                    r.displayStatus();
                    pause();
            }
        }
        else if (choice == 3)
        {
            string num;
            string name;
            showVacantRooms(rooms);
            cout << fg::yellow << "Enter Room Number: ";
            getline(cin >> ws, num);

            Room* r = findRoomByNumber(rooms, num);
            if(r == nullptr)
            {
                cout << fg::red << "❌ Room not found!\n";
                pause();
            }
            else 
            {
                cout << fg::yellow << "Enter patient Name : ";
                getline(cin >> ws, name);
                r -> assignBed(name);
                saveRoomsToFile(rooms, filename); // Save after assigning
                pause();
            }
        }
        else if(choice == 4)
        {
            string name;
            cout << fg::yellow << "Enter Patient Name to Search: ";
            getline(cin >> ws, name);
            searchAndDischargePatient(rooms, name);
            pause();
        }
        else if (choice == 5)
        {
            showVacantRooms(rooms);
            pause();
        }
        else if (choice == 6) 
        {
            string num;
            cout << fg::yellow << "Enter Room Number to View Details: ";
            getline(cin >> ws, num);
            searchRoomByNumber(rooms, num);
            pause();
        }
        else if(choice == 7)
        {
            cout << fg::green << "Exiting System. Goodbye!\n";
            break;
        }
        else
        {
            cout << fg::red << "❌ Invalid Choice. Goodbye!\n";
            pause();
        }
    }

    return 0;
}