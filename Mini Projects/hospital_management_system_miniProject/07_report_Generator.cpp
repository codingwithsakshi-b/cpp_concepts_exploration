#define _WIN32_WINNT 0x0600
#include <direct.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "rang.hpp"
using namespace std;
using namespace rang;

struct Appointment {
    string id, patientName, doctorName, date;
};

struct PatientInfo {
    string name, age, gender, problem, patientID, contact;
};

class Report {
public:
    string reportID, patientName, date, doctorName;
    string age, gender, contact, problem, patientFileID;
    string diagnosis, medicines, followupDate, notes;

    void generateReportID(int count) {
        stringstream ss;
        ss << "PTREP_" << setw(3) << setfill('0') << (count + 1);
        reportID = ss.str();
        cout << fg::yellow << "🆔 Auto-generated Report ID: " << reportID << endl;
    }

    void createReportFromAppointment(const Appointment& a, const PatientInfo& p, int totalReports) {
        generateReportID(totalReports);
        patientName = a.patientName;
        doctorName = a.doctorName;
        date = a.date;

        // From Patient Record
        age = p.age;
        gender = p.gender;
        contact = p.contact;
        problem = p.problem;
        patientFileID = p.patientID;

        cout << fg::cyan << "\n👉 Auto-filled from appointment & patient record:\n";
        cout << fg::blue << "Patient Name   : " << patientName << endl;
        cout << fg::blue << "Doctor Name    : " << doctorName << endl;
        cout << fg::blue << "Date           : " << date << endl;
        cout << fg::blue << "Age            : " << age << endl;
        cout << fg::blue << "Gender         : " << gender << endl;
        cout << fg::blue << "Contact No.    : " << contact << endl;
        cout << fg::blue << "Problem        : " << problem << endl;

        cout << fg::blue << "\nEnter Diagnosis            : ";
        getline(cin >> ws, diagnosis);
        cout << fg::blue << "Prescribed Medicines       : ";
        getline(cin >> ws, medicines);
        cout << fg::blue << "Follow-up Date (DD/MM/YYYY): ";
        getline(cin >> ws, followupDate);
        cout << fg::blue << "Additional Notes           : ";
        getline(cin >> ws, notes);

        cout << fg::green << "✅ Report Created Successfully!\n";
    }

    void displayReport() const {
        cout << fg::magenta << "\n============== Patient Medical Report ==============\n";
        cout << fg::cyan << "Report ID      : " << reportID << endl;
        cout << fg::cyan << "Patient Name   : " << patientName << "  (" << gender << ", Age: " << age << ")" << endl;
        cout << fg::cyan << "Patient ID     : " << patientFileID << "  📞 " << contact << endl;
        cout << fg::cyan << "Checkup Date   : " << date << "  | Doctor: " << doctorName << endl;
        cout << fg::cyan << "Problem        : " << problem << endl;
        cout << fg::cyan << "Diagnosis      : " << diagnosis << endl;
        cout << fg::cyan << "Medicines      : " << medicines << endl;
        cout << fg::cyan << "Follow-up Date : " << followupDate << endl;
        cout << fg::cyan << "Notes          : " << notes << endl;
        cout << fg::magenta << "====================================================\n";
    }

    string toCSV() const {
        auto escape = [](const string& field) -> string {
            return "\"" + field + "\"";
        };

        stringstream ss;
        ss << reportID << "," << escape(patientName) << "," << gender << "," << age << "," << contact << "," << patientFileID << ","
        << escape(doctorName) << "," << date << "," << escape(problem) << "," << escape(diagnosis) << "," << escape(medicines) << "," 
        << followupDate << "," << escape(notes);
        return ss.str();
    }
};

// ✳️ Load appointments
vector<Appointment> loadAppointments(const string& filename) {
    vector<Appointment> appointments;
    ifstream file(filename);
    if (!file) return appointments;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Appointment a;
        string skip;
        getline(ss, a.id, ',');
        getline(ss, a.patientName, ',');
        getline(ss, a.doctorName, ',');
        getline(ss, a.date, ',');
        getline(ss, skip); // skip time/reason
        appointments.push_back(a);
    }
    return appointments;
}

// ✳️ Load patient records
PatientInfo getPatientByName(const string& name) {
    PatientInfo p = {"", "", "", "", "", ""};
    ifstream file("01_patients.txt");
    if (!file) return p;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, n;

        getline(ss, id, ',');
        getline(ss, n, ',');

        if (n == name) {
            p.patientID = id;
            p.name = n;
            getline(ss, p.age, ',');
            getline(ss, p.gender, ',');
            getline(ss, p.problem, ',');
            getline(ss, p.contact);
            break;
        }
    }
    return p;
}

Appointment selectAppointment() {
    vector<Appointment> appts = loadAppointments("03_appointments.csv");
    if (appts.empty()) {
        cout << fg::red << "❌ No appointments found!\n";
        return {};
    }

    cout << fg::cyan << "\n📅 Appointments:\n";
    for (size_t i = 0; i < appts.size(); ++i) {
        cout << i + 1 << ". [" << appts[i].id << "] "
             << appts[i].patientName << " ➝ " << appts[i].doctorName << " on " << appts[i].date << endl;
    }

    int ch;
    cout << fg::yellow << "Choose appointment [1-" << appts.size() << "]: ";
    cin >> ch; cin.ignore();
    if (ch >= 1 && ch <= appts.size()) return appts[ch - 1];
    return {};
}

void saveReportsToFile(const vector<Report>& reports, const string& filename) {
    ofstream file(filename);
    if (!file) return;
    file << "ReportID,Name,Gender,Age,Contact,PatientID,Doctor,Date,Problem,Diagnosis,Medicines,FollowupDate,Notes\n";
    for (auto& r : reports) file << r.toCSV() << "\n";
}

void saveIndividualReportToCSV(const Report& report) {
    _mkdir("reports"); // Make folder if it doesn’t exist

    string filename = "reports/" + report.reportID + ".csv";
    ofstream file(filename);
    if (!file) {
        cout << fg::red << "❌ Failed to save report to " << filename << endl;
        return;
    }

    file << "ReportID,PatientName,Gender,Age,Contact,PatientID,Doctor,Date,Problem,Diagnosis,Medicines,FollowupDate,Notes\n";
    file << report.toCSV() << endl;
    file.close();

    cout << fg::green << "✅ Individual Report saved to " << filename << endl;
}

void saveIndividualReportToTXT(const Report& report) {
    _mkdir("reports"); // Ensure reports/ exists (already added for CSV)

    string filename = "reports/" + report.reportID + ".txt";
    ofstream file(filename);
    if (!file) {
        cout << fg::red << "❌ Failed to save report to " << filename << endl;
        return;
    }

    file << "=========================================================\n";
    file << "                   🏥 MEDICAL REPORT\n";
    file << "=========================================================\n\n";

    file << "🆔 Report ID     : " << report.reportID << "\n";
    file << "📅 Date          : " << report.date << "\n\n";

    file << "👤 Patient Details\n";
    file << "---------------------------------------------------------\n";
    file << "Name             : " << report.patientName << "\n";
    file << "Age              : " << report.age << "\n";
    file << "Gender           : " << report.gender << "\n";
    file << "Patient ID       : " << report.patientFileID << "\n";
    file << "Contact Number   : " << report.contact << "\n\n";

    file << "🩺 Doctor Assigned\n";
    file << "---------------------------------------------------------\n";
    file << "Name             : " << report.doctorName << "\n\n";

    file << "📝 Medical Information\n";
    file << "---------------------------------------------------------\n";
    file << "Reported Problem : " << report.problem << "\n";
    file << "Diagnosis        : " << report.diagnosis << "\n";
    file << "Prescribed Meds  : " << report.medicines << "\n";
    file << "Follow-up Date   : " << report.followupDate << "\n\n";

    file << "🗒️ Notes\n";
    file << "---------------------------------------------------------\n";
    file << report.notes << "\n";

    file << "\n=========================================================\n";
    file << "          Thank you for visiting! Stay healthy 💖\n";
    file << "=========================================================\n";

    file.close();
    cout << fg::green << "📝 Printable TXT report saved to " << filename << endl;
}

void loadReportsFromFile(vector<Report>& reports, const string& filename) {
    ifstream file(filename);
    if (!file) return;

    string line;
    getline(file, line); // skip header
    while (getline(file, line)) {
        stringstream ss(line);
        Report r;
        getline(ss, r.reportID, ',');
        getline(ss, r.patientName, ',');
        getline(ss, r.gender, ',');
        getline(ss, r.age, ',');
        getline(ss, r.contact, ',');
        getline(ss, r.patientFileID, ',');
        getline(ss, r.doctorName, ',');
        getline(ss, r.date, ',');
        getline(ss, r.problem, ',');
        getline(ss, r.diagnosis, ',');
        getline(ss, r.medicines, ',');
        getline(ss, r.followupDate, ',');
        getline(ss, r.notes);
        reports.push_back(r);
    }
}

int getValidatedChoice() {
    int c;
    cout << fg::yellow << "Enter your choice [1-5]: ";
    while (!(cin >> c)) {
        cin.clear(); cin.ignore(10000, '\n');
        cout << fg::red << "❌ Invalid input. Try again: ";
    }
    cin.ignore();
    return c;
}

void pause() {
    cout << fg::yellow << "\nPress any key to continue...";
    cin.get();
    system("cls");
}

void searchReportByID(const vector<Report>& reports, const string& id) {
    for (const auto& r : reports) {
        if (r.reportID == id) {
            r.displayReport();
            return;
        }
    }
    cout << fg::red << "❌ Report not found.\n";
}

void deleteReportByID(vector<Report>& reports, const string& id) {
    for (auto it = reports.begin(); it != reports.end(); ++it) {
        if (it->reportID == id) {
            reports.erase(it);
            cout << fg::green << "✅ Report deleted.\n";
            return;
        }
    }
    cout << fg::red << "❌ Report not found.\n";
}

int main() {
    system("chcp 65001");
    system("cls");

    vector<Report> reports;
    string filename = "07_reports.csv";

    loadReportsFromFile(reports, filename);

    while (true) {
        cout << fg::magenta << "\n========= Patient Report System =========\n";
        cout << fg::cyan << "1. Create New Report\n";
        cout << fg::cyan << "2. View All Reports\n";
        cout << fg::cyan << "3. Search Report by ID\n";
        cout << fg::cyan << "4. Delete Report\n";
        cout << fg::cyan << "5. Exit\n";

        int choice = getValidatedChoice();

        if (choice == 1) {
            Appointment appt = selectAppointment();
            if (appt.id.empty()) { pause(); continue; }

            PatientInfo pinfo = getPatientByName(appt.patientName);
            if (pinfo.name.empty()) {
                cout << fg::red << "❌ Patient not found in record file!\n";
                pause(); continue;
            }

            Report r;
            r.createReportFromAppointment(appt, pinfo, reports.size());
            reports.push_back(r);
            saveReportsToFile(reports, filename);
            saveIndividualReportToCSV(r);
            saveIndividualReportToTXT(r);
            pause();
        }
        else if (choice == 2) {
            for (auto& r : reports) r.displayReport();
            pause();
        }
        else if (choice == 3) {
            string id;
            cout << fg::yellow << "Enter Report ID to Search: ";
            getline(cin >> ws, id);
            searchReportByID(reports, id);
            pause();
        }
        else if (choice == 4) {
            string id;
            cout << fg::yellow << "Enter Report ID to Delete: ";
            getline(cin >> ws, id);
            deleteReportByID(reports, id);
            saveReportsToFile(reports, filename);
            pause();
        }
        else if (choice == 5) {
            cout << fg::green << "👋 Exiting Report System. Stay healthy!\n";
            break;
        }
        else {
            cout << fg::red << "❌ Invalid choice!\n";
            pause();
        }
    }
    return 0;
}