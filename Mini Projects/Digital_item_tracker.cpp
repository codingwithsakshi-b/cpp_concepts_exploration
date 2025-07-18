#define _WIN32_WINNT 0x0600
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include "rang.hpp"

using namespace std;
using namespace rang;

struct Item {
    string name;
    string status; // "PENDING" or "PURCHASED"
};

void pauseConsole() {
    cout << fg::gray << "\nPress Enter to continue..." << style::reset;
    cin.ignore();
    cin.get();
}

const string FILE_NAME = "item_list.csv";

// Function to load items from file
vector<Item> loadItems() {
    vector<Item> items;
    ifstream file(FILE_NAME);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, status;
        getline(ss, name, ',');
        getline(ss, status);
        if (!name.empty()) {
            items.push_back({name, status});
        }
    }
    file.close();
    return items;
}

// Function to save items to file
void saveItems(const vector<Item>& items) {
    ofstream file(FILE_NAME);
    for (const auto& item : items) {
        file << item.name << "," << item.status << endl;
    }
    file.close();
}

// Add item
void addItem() {
    string itemName;
    cout << style::bold << fg::cyan << "📝 Enter item name to add: " << style::reset;
    cin.ignore();
    getline(cin, itemName);

    ofstream file(FILE_NAME, ios::app);
    file << itemName << ",PENDING" << endl;
    file.close();

    cout << fg::green << "✅ Item added successfully!\n" << style::reset;
    pauseConsole();
    system("cls"); // Clear console for Windows
}

// View all items
void viewItems(const vector<Item>& items) {
    cout << "\n" << style::bold << fg::yellow << "📋 Your Item List:\n" << style::reset;
    cout << left << setw(5) << "No." << setw(30) << "Item Name" << "Status\n";
    cout << "-----------------------------------------------\n";
    int i = 1;
    for (const auto& item : items) {
        cout << left << setw(5) << i++ << setw(30) << item.name;
        if (item.status == "PENDING")
            cout << fg::yellow << "🟡 " << item.status << style::reset << endl;
        else
            cout << fg::green << "🟢 " << item.status << style::reset << endl;
    }
    cout << endl;
    pauseConsole();
    system("cls"); // Clear console for Windows
}

// View filtered items
void viewFilteredItems(const vector<Item>& items, const string& filterStatus) {
    cout << "\n" << style::bold << fg::magenta;
    cout << (filterStatus == "PENDING" ? "📂 Pending Items:\n" : "📦 Purchased Items:\n");
    cout << style::reset;
    cout << left << setw(5) << "No." << setw(30) << "Item Name" << "Status\n";
    cout << "-----------------------------------------------\n";
    int i = 1;
    for (const auto& item : items) {
        if (item.status == filterStatus) {
            cout << left << setw(5) << i++ << setw(30) << item.name;
            if (filterStatus == "PENDING")
                cout << fg::yellow << "🟡 " << item.status << style::reset << endl;
            else
                cout << fg::green << "🟢 " << item.status << style::reset << endl;
        }
    }
    cout << endl;
    pauseConsole();
    system("cls"); // Clear console for Windows
}

// Mark item as purchased
void markAsPurchased(vector<Item>& items) {
    viewFilteredItems(items, "PENDING");
    int choice;
    cout << style::bold << fg::cyan << "🛒 Enter item number to mark as purchased: " << style::reset;
    cin >> choice;

    int count = 0;
    for (auto& item : items) {
        if (item.status == "PENDING") {
            count++;
            if (count == choice) {
                item.status = "PURCHASED";
                saveItems(items);
                cout << fg::green << "✅ Item marked as purchased!\n" << style::reset;
                return;
            }
        }
    }

    cout << fg::red << "⚠️ Invalid choice!\n" << style::reset;
    pauseConsole();
    system("cls"); // Clear console for Windows
}

// Delete item
void deleteItem(vector<Item>& items) {
    viewItems(items);
    int choice;
    cout << style::bold << fg::red << "🗑️ Enter item number to delete: " << style::reset;
    cin >> choice;

    if (choice < 1 || choice > items.size()) {
        cout << fg::red << "❌ Invalid choice!\n" << style::reset;
        return;
    }

    items.erase(items.begin() + choice - 1);
    saveItems(items);
    cout << fg::yellow << "🧹 Item deleted successfully!\n" << style::reset;
    pauseConsole();
    system("cls"); // Clear console for Windows
}

// Main menu
void showMenu() {
    cout << "\n" << style::bold << fg::blue << "📌 Digital Item Tracker Menu:\n" << style::reset;
    cout << fg::gray << "----------------------------------\n" << style::reset;
    cout << "1. " << fg::green << "Add Item\n" << style::reset;
    cout << "2. " << fg::yellow << "View All Items\n" << style::reset;
    cout << "3. " << fg::green << "Mark Item as Purchased\n" << style::reset;
    cout << "4. " << fg::yellow << "View Pending Items\n" << style::reset;
    cout << "5. " << fg::green << "View Purchased Items\n" << style::reset;
    cout << "6. " << fg::red << "Delete Item\n" << style::reset;
    cout << "7. " << fg::gray << "Exit\n" << style::reset;
    cout << fg::cyan << "Enter your choice: " << style::reset;
}

int main() {
    system("cls"); // Clear console for Windows
    system("chcp 65001"); // Set console to UTF-8 encoding
    int choice;

    do {
        vector<Item> items = loadItems();
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addItem(); break;
            case 2: viewItems(items); break;
            case 3: markAsPurchased(items); break;
            case 4: viewFilteredItems(items, "PENDING"); break;
            case 5: viewFilteredItems(items, "PURCHASED"); break;
            case 6: deleteItem(items); break;
            case 7: cout << fg::blue << "👋 Exiting... Have a great day, Sakshi!\n" << style::reset; break;
            default: cout << fg::red << "❌ Invalid choice. Try again!\n" << style::reset; break;
        }

    } while (choice != 7);

    return 0;
}