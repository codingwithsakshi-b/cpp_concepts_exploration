#define _WIN32_WINNT 0x0600 //for running the file rang.hpp for colored output
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "rang.hpp"
#include <direct.h>
using namespace rang;
using namespace std;

class Bill
{
public:
    string patientID, patientName, billingDate;
    float consultationFee, roomCharges, medicineCost, totalAmount;

    // Default Constructor
    Bill()
        : patientID(""), patientName(""), billingDate(""),
          consultationFee(0.0f), roomCharges(0.0f), medicineCost(0.0f), totalAmount(0.0f) {}

    //for creating auto-generated bill id
    void generatePatientID(int count) {
        stringstream ss;
        ss << "BILL2025_" << setw(3) << setfill('0') << (count + 1);
        patientID = ss.str();
        cout << fg::yellow << "🆔 Auto-generated Patient ID: " << patientID << endl;
    }

    // Function to create a bill
    void createBill(int billCountSoFar)
    {
        cout << fg::cyan << "\n-------------- Enter Billing Details ----------------\n";
        generatePatientID(billCountSoFar);
        
        cout << fg::blue << "Enter Patient Name        : ";
        getline(cin >> ws, patientName);

        cout << fg::blue << "Enter Billing Date (DD/MM/YYYY): ";
        getline(cin >> ws, billingDate);

        cout << fg::blue << "Enter Consultation Fee    : ₹";
        cin >> consultationFee;

        cout << fg::blue << "Enter Medicine Cost       : ₹";
        cin >> medicineCost;
        
        int roomChoice, bedCount;
        cout << fg::blue << "\nSelect Room Type (Per Bed Charge):\n";
        cout << "1. General  (₹800)\n";
        cout << "2. Private  (₹1500)\n";
        cout << "3. ICU      (₹2500)\n";
        cout << "4. Deluxe   (₹3000)\n";
        cout << fg::yellow << "Enter choice (1-4): ";
        cin >> roomChoice;

        cout << fg::yellow << "Enter number of beds taken: ";
        cin >> bedCount;

        switch (roomChoice) {
            case 1:
                roomCharges = 800 * bedCount;
                cout << fg::green << "✅ Room: General x" << bedCount << " = ₹" << roomCharges << endl;
                break;
            case 2:
                roomCharges = 1500 * bedCount;
                cout << fg::green << "✅ Room: Private x" << bedCount << " = ₹" << roomCharges << endl;
                break;
            case 3:
                roomCharges = 2500 * bedCount;
                cout << fg::green << "✅ Room: ICU x" << bedCount << " = ₹" << roomCharges << endl;
                break;
            case 4:
                roomCharges = 3000 * bedCount;
                cout << fg::green << "✅ Room: Deluxe x" << bedCount << " = ₹" << roomCharges << endl;
                break;
            default:
                cout << fg::red << "❌ Invalid room type. Defaulting to General.\n";
                roomCharges = 800 * bedCount;
        }

        totalAmount = consultationFee + roomCharges + medicineCost;

        cout << fg::green << "✅ Bill Created Successfully!\n";
    }

    // Function to display the bill
    void showInvoice() const
    {
        cout << fg::magenta << "\n============== INVOICE ==============\n";
        cout << fg::cyan << "Patient ID     : " << patientID << endl;
        cout << fg::cyan << "Patient Name   : " << patientName << endl;
        cout << fg::cyan << "Billing Date   : " << billingDate << endl;
        cout << fg::cyan << "--------------------------------------\n";
        cout << fg::cyan << "Consultation Fee : ₹" << fixed << setprecision(2) << consultationFee << endl;
        cout << fg::cyan << "Medicine Cost    : ₹" << medicineCost << endl;
        cout << fg::cyan << "Room Charges     : ₹" << roomCharges << endl;
        cout << fg::cyan << "--------------------------------------\n";
        cout << fg::green << "TOTAL AMOUNT     : ₹" << totalAmount << "\n";
        cout << fg::magenta << "======================================\n";
    }

    // Function to save the bill to a file
    string toCSV() const {
        stringstream ss;
        ss << patientID << "," << patientName << "," << billingDate << ","
           << consultationFee << "," << medicineCost << "," << roomCharges << "," << totalAmount;
        return ss.str();
    }
};

void saveBillsToFile(const vector<Bill>& bills, const string& filename)
{
    ofstream file(filename);
    if(!file) {
        cerr << fg::red << "⚠️ Error opening file for saving bills.\n";
        return;
    }

    file << "PatientID,PatientName,BillingDate,ConsultationFee,MedicineCost,RoomCharges,TotalAmount\n"; // Header

    for (const auto& bill : bills) {
        file << bill.toCSV() << "\n";
    }

    file.close();
    cout << fg::green << "✅ Bills saved to " << filename << " successfully!\n";
}

void saveInvoiceAsTXT(const Bill& bill) {
    _mkdir("invoices"); // Create folder if not exists (Windows)

    string filename = "invoices/" + bill.patientID + ".txt";
    ofstream file(filename);
    if (!file) {
        cout << fg::red << "❌ Failed to save invoice for " << bill.patientID << endl;
        return;
    }

    file << "=================================================\n";
    file << "              🏥 HOSPITAL INVOICE\n";
    file << "=================================================\n";
    file << "🧾 Patient ID     : " << bill.patientID << "\n";
    file << "👤 Patient Name   : " << bill.patientName << "\n";
    file << "📅 Billing Date   : " << bill.billingDate << "\n";
    file << "-------------------------------------------------\n";
    file << "🩺 Consultation Fee : ₹" << fixed << setprecision(2) << bill.consultationFee << "\n";
    file << "💊 Medicine Cost    : ₹" << bill.medicineCost << "\n";
    file << "🛏️  Room Charges     : ₹" << bill.roomCharges << "\n";
    file << "-------------------------------------------------\n";
    file << "💰 TOTAL AMOUNT     : ₹" << bill.totalAmount << "\n";
    file << "=================================================\n";
    file << "         Thank you for trusting our care! 💖\n";
    file << "=================================================\n";

    file.close();
    cout << fg::green << "📝 Invoice saved as " << filename << endl;
}

// Function to load bills from a file
void loadBillsFromFile(vector<Bill>& bills, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << fg::yellow << "⚠️ No previous bills found.\n";
        return;
    }

    string line;
    getline(file, line); // skip header
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Bill b;
        string val;

        getline(ss, b.patientID, ',');
        getline(ss, b.patientName, ',');
        getline(ss, b.billingDate, ',');

        getline(ss, val, ','); b.consultationFee = stof(val);
        getline(ss, val, ','); b.medicineCost = stof(val);
        getline(ss, val, ','); b.roomCharges = stof(val);
        getline(ss, val, ','); b.totalAmount = stof(val);

        bills.push_back(b);
    }
    cout << fg::green << "✅ Bills loaded from file successfully.\n";
}

int getValidatedChoice() {
    int choice;
    while (true) {
        cout << fg::yellow << "Enter Your Choice: ";
        if (cin >> choice) {
            cin.ignore();
            return choice;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << fg::red << "❌ Invalid input. Please enter a number.\n";
        }
    }
}

void pause() {
    cout << fg::yellow << "\nPress any key to continue...";
    cin.ignore();
    cin.get();
    system("cls");
}

void searchBillByID(const vector<Bill>& bills, const string& id) {
    bool found = false;
    for (auto& b : bills) {
        if (b.patientID == id) {
            b.showInvoice();
            found = true;
        }
    }
    if (!found) {
        cout << fg::red << "❌ No bill found for Patient ID: " << id << endl;
    }
}

void deleteBillByID(vector<Bill>& bills, const string& id) {
    auto it = bills.begin();
    while (it != bills.end()) {
        if (it->patientID == id) {
            it = bills.erase(it);
            cout << fg::green << "✅ Bill for Patient ID " << id << " deleted.\n";
            return;
        } else {
            ++it;
        }
    }
    cout << fg::red << "❌ No bill found for Patient ID: " << id << endl;
}

void showRevenueSummary(const vector<Bill>& bills) {
    float totalConsultation = 0, totalMedicine = 0, totalRoom = 0, grandTotal = 0;

    for (const auto& b : bills) {
        totalConsultation += b.consultationFee;
        totalMedicine += b.medicineCost;
        totalRoom += b.roomCharges;
        grandTotal += b.totalAmount;
    }

    cout << fg::magenta << "\n========== 💸 Revenue Summary ==========\n";
    cout << fg::cyan << "🧾 Total Bills Issued    : " << bills.size() << endl;
    cout << fg::cyan << "🩺 Consultation Fees     : ₹" << fixed << setprecision(2) << totalConsultation << endl;
    cout << fg::cyan << "💊 Medicine Revenue      : ₹" << totalMedicine << endl;
    cout << fg::cyan << "🛏️  Room Charges         : ₹" << totalRoom << endl;
    cout << fg::green   << "💰 Grand Total Revenue   : ₹" << grandTotal << endl;
    cout << fg::magenta << "========================================\n";
}

int main() {
    system("chcp 65001");
    system("cls");

    vector<Bill> bills;
    string filename = "06_bills.csv";

    loadBillsFromFile(bills, filename);

    int choice;
    while (true) {
        cout << fg::magenta << "\n========= Billing & Invoice Menu =========\n";
        cout << fg::cyan << "1. Add New Bill\n";
        cout << fg::cyan << "2. View All Bills\n";
        cout << fg::cyan << "3. Search Bill by Patient ID\n";
        cout << fg::cyan << "4. Delete Bill by Patient ID\n";
        cout << fg::cyan << "5. Show Revenue Summary\n";
        cout << fg::cyan << "6. Exit\n";

        choice = getValidatedChoice();

        if (choice == 1) {
            Bill b;
            b.createBill(bills.size());
            bills.push_back(b);
            saveBillsToFile(bills, filename);
            saveInvoiceAsTXT(b); // <--- ✅ NEW LINE
            pause();
        }
        else if (choice == 2) {
            if (bills.empty()) {
                cout << fg::red << "❌ No bills available.\n";
            } else {
                for (auto& b : bills)
                    b.showInvoice();
            }
            pause();
        }
        else if (choice == 3) {
            string id;
            cout << fg::yellow << "Enter Patient ID to Search: ";
            getline(cin >> ws, id);
            searchBillByID(bills, id);
            pause();
        }
        else if (choice == 4) {
            string id;
            cout << fg::yellow << "Enter Patient ID to Delete Bill: ";
            getline(cin >> ws, id);
            deleteBillByID(bills, id);
            saveBillsToFile(bills, filename);
            pause();
        }
        else if (choice == 5) {
            showRevenueSummary(bills);
            pause();
        }
        else if (choice == 6) {
            cout << fg::green << "👋 Exiting Billing System. Goodbye!\n";
            break;
        }
        else {
            cout << fg::red << "❌ Invalid choice!\n";
            pause();
        }
    }

    return 0;
}