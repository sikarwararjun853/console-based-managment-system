#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void addBook() {
    int id;
    string name, author;

    ofstream file("books.txt", ios::app);

    cout << "Enter Book ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Book Name: ";
    getline(cin, name);

    cout << "Enter Author Name: ";
    getline(cin, author);

    file << id << "|" << name << "|" << author << "|Available" << endl;

    file.close();

    cout << "Book Added Successfully\n";
}

void displayBooks() {

    ifstream file("books.txt");
    string line;

    cout << "\n================ Library Books ================\n\n";

    cout << left << setw(10) << "ID"
         << setw(25) << "Book Name"
         << setw(20) << "Author"
         << setw(15) << "Status" << endl;

    cout << "-------------------------------------------------------------\n";

    while (getline(file, line)) {

        int pos1 = line.find('|');
        int pos2 = line.find('|', pos1 + 1);
        int pos3 = line.find('|', pos2 + 1);

        int id = stoi(line.substr(0, pos1));
        string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string author = line.substr(pos2 + 1, pos3 - pos2 - 1);
        string status = line.substr(pos3 + 1);

        cout << left << setw(10) << id
             << setw(25) << name
             << setw(20) << author
             << setw(15) << status << endl;
    }

    file.close();
}

void deleteBook() {

    int deleteID;
    cout << "Enter Book ID to delete: ";
    cin >> deleteID;

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {

        int pos = line.find('|');
        int id = stoi(line.substr(0, pos));

        if (id != deleteID) {
            temp << line << endl;
        }
        else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        cout << "Book Deleted Successfully\n";
    else
        cout << "Book Not Found\n";
}

void issueBook() {

    int issueID;
    cout << "Enter Book ID to issue: ";
    cin >> issueID;

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {

        int pos1 = line.find('|');
        int pos2 = line.find('|', pos1 + 1);
        int pos3 = line.find('|', pos2 + 1);

        int id = stoi(line.substr(0, pos1));
        string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string author = line.substr(pos2 + 1, pos3 - pos2 - 1);
        string status = line.substr(pos3 + 1);

        if (id == issueID && status == "Available") {
            status = "Issued";
            found = true;
            cout << "Book Issued Successfully\n";
        }

        temp << id << "|" << name << "|" << author << "|" << status << endl;
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found)
        cout << "Book Not Available or Not Found\n";
}

void returnBook() {

    int returnID;
    cout << "Enter Book ID to return: ";
    cin >> returnID;

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {

        int pos1 = line.find('|');
        int pos2 = line.find('|', pos1 + 1);
        int pos3 = line.find('|', pos2 + 1);

        int id = stoi(line.substr(0, pos1));
        string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string author = line.substr(pos2 + 1, pos3 - pos2 - 1);
        string status = line.substr(pos3 + 1);

        if (id == returnID && status == "Issued") {
            status = "Available";
            found = true;
            cout << "Book Returned Successfully\n";
        }

        temp << id << "|" << name << "|" << author << "|" << status << endl;
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found)
        cout << "Book Not Found\n";
}

int main() {

    int choice;

    do {

        cout << "\n=========== Library Management System ===========\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Delete Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            addBook();
            break;

        case 2:
            displayBooks();
            break;

        case 3:
            deleteBook();
            break;

        case 4:
            issueBook();
            break;

        case 5:
            returnBook();
            break;

        case 6:
            cout << "Program Ended\n";
            break;

        default:
            cout << "Invalid Choice\n";
        }

    } while (choice != 6);

    return 0;
}