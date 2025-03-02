/* Adam Cebula
* February 22, 2025
* Item tracking program for Corner Grocer
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

// Stores items and frequencies
class GroceryTracker {
private:
    map<string, int> itemFrequency;

public:
    //Loads data from file and creates backup file
    GroceryTracker(const string& inputFile, const string& backupFile) {
        LoadData(inputFile);
        SaveData(backupFile);
    }

    // Reads input file and populates map
    void LoadData(const string& filename) {
        ifstream inFile(filename);
        string item;
        if (inFile.is_open()) {
            while (inFile >> item) {
                itemFrequency[item]++;
            }
            inFile.close();
        }
        else {
            cerr << "Error: unable to open input file." << endl;
        }
    }

    // Saves frequency data to a backup file
    void SaveData(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& pair : itemFrequency) {
                outFile << pair.first << " " << pair.second << endl;
            }
            outFile.close();
        }
        else {
            cerr << "Error: unable to open backup file." << endl;
        }
    }

    // Gets frequency of item
    int GetItemFrequency(const string& item) {
        if (itemFrequency.find(item) != itemFrequency.end()) {
            return itemFrequency[item];
        }
        return 0; // If item not found
    }

    // Display items and frequencies
    void DisplayAllItems() {
        cout << "\nItem Frequency List:\n";
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Prints histogram
    void DisplayHistogram() {
        cout << "\nItem Frequency Histogram:\n";
        for (const auto& pair : itemFrequency) {
            cout << setw(15) << left << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};


// Display menu
void DisplayMenu() {
    cout << "\nCorner Grocer Inventory System\n";
    cout << "1. Search for an item frequency\n";
    cout << "2. Display all item frequencies\n";
    cout << "3. Display histogram\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    const string inputFile = "CS210_Project_Three_Input_File.txt";
    const string backupFile = "frequency.dat";
    GroceryTracker tracker(inputFile, backupFile);

    int choice;
    string item;

    while (true) {
        DisplayMenu();
        cin >> choice;

        if (choice == 1) {
            cout << "Enter item name: ";
            cin >> item;
            cout << "Frequency of " << item << ": " << tracker.GetItemFrequency(item) << endl;
        }
        else if (choice == 2) {
            tracker.DisplayAllItems();
        }
        else if (choice == 3) {
            tracker.DisplayHistogram();
        }
        else if (choice == 4) {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    }

    return 0;
}

