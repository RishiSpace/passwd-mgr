//  This CLI Program is Designed by Rishikesh Giridhar for Personal use Only

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include <algorithm>

using namespace std;

string generateRandomChars(int length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string result;
    result.resize(length);
    for (int i = 0; i < length; ++i) {
        result[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    return result;
}

string encrypt(const string& input) {
    string encrypted;
    for (char c : input) {
        encrypted += c;
        encrypted += generateRandomChars(10);
    }
    return encrypted;
}

string decrypt(const string& input) {
    string decrypted;
    for (size_t i = 0; i < input.size(); i += 11) {
        decrypted += input[i];
    }
    return decrypted;
}

void savePassword() {
    fstream file("passwords.txt", ios::out | ios::app);
    if (!file) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    srand(time(nullptr));

    string username, password, website;
    cout << "Enter the website name: ";
    getline(cin, website);

    cout << "Enter the username: ";
    getline(cin, username);

    cout << "Enter the password: ";
    getline(cin, password);

    string encryptedUsername = encrypt(username);
    string encryptedPassword = encrypt(password);

    file << website << " | " << encryptedUsername << " | " << encryptedPassword << endl;
    file.close();

    cout << "Username and password encrypted and stored." << endl;
}

void searchPassword(const string& searchTerm) {
    ifstream inFile("passwords.txt");
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    bool found = false;
    string line;
    while (getline(inFile, line)) {
        size_t pos = line.find(" | ");
        if (pos != string::npos) {
            string web = line.substr(0, pos);
            string rest = line.substr(pos + 3);
            size_t pos2 = rest.find(" | ");
            if (pos2 != string::npos) {
                string encUsername = rest.substr(0, pos2);
                string encPassword = rest.substr(pos2 + 3);
                string username = decrypt(encUsername);
                string password = decrypt(encPassword);

                if (web.find(searchTerm) != string::npos || username.find(searchTerm) != string::npos) {
                    cout << "Website: " << web << endl;
                    cout << "Username: " << username << endl;
                    cout << "Password: " << password << endl;
                    cout << endl;
                    found = true;
                }
            }
        }
    }

    inFile.close();

    if (!found) {
        cout << "No matching passwords found." << endl;
    }
}

int main() {
    srand(time(nullptr));
    while (true) {   
        system("cls");     
        cout << "Choose an option:" << endl;
        cout << "1. Save a new password" << endl;
        cout << "2. Search for an existing password" << endl;
        cout << "3. Exit" << endl;
        int option;
        cin >> option;
        cin.ignore();
        if (option == 1) {
            system("cls");
            savePassword();
            cout << "Going back to menu in 5....";
            system("timeout /t 5 /nobreak");
        } else if (option == 2) {
            system("cls");
            string searchTerm;
            cout << "Enter a search term: ";
            getline(cin, searchTerm);
            searchPa