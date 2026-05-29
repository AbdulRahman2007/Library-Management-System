#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// ============================================================
//  BOOK CLASS — holds data for one single book
// ============================================================
class Book {
public:
    string id;
    string name;
    string author;
    bool isAvailable;   // true = on shelf,  false = allotted

    // Default constructor
    Book() {
        isAvailable = true;
    }

    // Parameterized constructor
    Book(string i, string n, string a) {
        id          = i;
        name        = n;
        author      = a;
        isAvailable = true;
    }

    void display() {
        cout << "  Book ID   : " << id     << endl;
        cout << "  Name      : " << name   << endl;
        cout << "  Author    : " << author << endl;
        cout << "  Status    : " << (isAvailable ? "Available" : "Allotted") << endl;
        cout << "  ----------------------------" << endl;
    }
};

// ============================================================
//  STUDENT CLASS — holds one allotment record
// ============================================================
class Student {
public:
    string studentName;
    string bookId;
    string returnDate;

    Student() {}

    Student(string sName, string bId, string rDate) {
        studentName = sName;
        bookId      = bId;
        returnDate  = rDate;
    }

    void display() {
        cout << "  Student   : " << studentName << endl;
        cout << "  Book ID   : " << bookId      << endl;
        cout << "  Return by : " << returnDate  << endl;
        cout << "  ----------------------------" << endl;
    }
};

// ============================================================
//  LOGIN CLASS — handles admin authentication
// ============================================================
class Login {
private:
    string correctUsername;
    int    correctPassword;

public:
    Login() {
        correctUsername = "admin";
        correctPassword = 1234;
    }

    // Returns true if login succeeds, false otherwise
    bool authenticate() {
        string enteredUser;
        int    enteredPass;

        cout << "\n===== LIBRARY LOGIN =====" << endl;
        cout << "Username : ";
        cin  >> enteredUser;
        cout << "Password : ";
        cin  >> enteredPass;

        if (enteredUser == correctUsername && enteredPass == correctPassword) {
            cout << "\nLogin successful! Welcome, Admin." << endl;
            return true;
        } else {
            cout << "\nInvalid username or password." << endl;
            return false;
        }
    }
};

// ============================================================
//  LIBRARY CLASS — manages all books and students
// ============================================================
class Library {
private:
    vector<Book>    books;      // stores all books
    vector<Student> allotments; // stores all allotment records

    // --- File names used for saving data ---
    string booksFile     = "books.txt";
    string allotmentFile = "allotments.txt";

public:

    // Constructor loads data from files when program starts
    Library() {
        loadBooksFromFile();
        loadAllotmentsFromFile();
    }

    // --------------------------------------------------------
    //  ADD BOOKS
    // --------------------------------------------------------
    void addBooks() {
        int n;
        cout << "\nHow many books do you want to add? ";
        cin  >> n;
        cin.ignore(); // flush leftover newline

        for (int i = 0; i < n; i++) {
            string bid, bname, bauthor;

            cout << "\n-- Book " << i + 1 << " --" << endl;

            cout << "  Enter Book ID   : ";
            getline(cin, bid);

            cout << "  Enter Book Name : ";
            getline(cin, bname);

            cout << "  Enter Author    : ";
            getline(cin, bauthor);

            // Create a Book object and add to the vector
            Book b(bid, bname, bauthor);
            books.push_back(b);

            cout << "  Book added successfully!" << endl;
        }

        saveBooksToFile(); // save after adding
    }

    // --------------------------------------------------------
    //  DISPLAY ALL BOOKS
    // --------------------------------------------------------
    void displayBooks() {
        if (books.empty()) {
            cout << "\nNo books in the library yet." << endl;
            return;
        }

        cout << "\n===== ALL BOOKS =====" << endl;
        for (int i = 0; i < books.size(); i++) {
            books[i].display();
        }
    }

    // --------------------------------------------------------
    //  CHECK AVAILABILITY of a specific book
    // --------------------------------------------------------
    void checkAvailability() {
        string searchId;
        cout << "\nEnter Book ID to check: ";
        cin.ignore();
        getline(cin, searchId);

        for (int i = 0; i < books.size(); i++) {
            if (books[i].id == searchId) {
                cout << "\nBook found:" << endl;
                books[i].display();
                return;
            }
        }
        cout << "\nNo book found with ID: " << searchId << endl;
    }

    // --------------------------------------------------------
    //  ALLOT A BOOK to a student
    // --------------------------------------------------------
    void allotBook() {
        string searchId, sName, rDate;

        cin.ignore();
        cout << "\nEnter Book ID to allot : ";
        getline(cin, searchId);

        // Search for the book
        for (int i = 0; i < books.size(); i++) {
            if (books[i].id == searchId) {

                if (!books[i].isAvailable) {
                    cout << "Sorry, this book is already allotted." << endl;
                    return;
                }

                cout << "Enter Student Name    : ";
                getline(cin, sName);
                cout << "Enter Return Date     : ";
                getline(cin, rDate);

                // Mark book as unavailable
                books[i].isAvailable = false;

                // Create allotment record
                Student s(sName, searchId, rDate);
                allotments.push_back(s);

                cout << "Book allotted successfully to " << sName << "!" << endl;

                saveBooksToFile();
                saveAllotmentsToFile();
                return;
            }
        }

        cout << "No book found with ID: " << searchId << endl;
    }

    // --------------------------------------------------------
    //  RETURN A BOOK
    // --------------------------------------------------------
    void returnBook() {
        string searchId;

        cin.ignore();
        cout << "\nEnter Book ID to return: ";
        getline(cin, searchId);

        // Step 1: Find and mark book as available
        bool bookFound = false;
        for (int i = 0; i < books.size(); i++) {
            if (books[i].id == searchId) {
                books[i].isAvailable = true;
                bookFound = true;
                cout << "Book '" << books[i].name << "' returned successfully." << endl;
                break;
            }
        }

        if (!bookFound) {
            cout << "No book found with ID: " << searchId << endl;
            return;
        }

        // Step 2: Remove the allotment record for this book
        for (int i = 0; i < allotments.size(); i++) {
            if (allotments[i].bookId == searchId) {
                allotments.erase(allotments.begin() + i);
                break;
            }
        }

        saveBooksToFile();
        saveAllotmentsToFile();
    }

    // --------------------------------------------------------
    //  DISPLAY ALL ALLOTMENTS
    // --------------------------------------------------------
    void displayAllotments() {
        if (allotments.empty()) {
            cout << "\nNo books are currently allotted." << endl;
            return;
        }

        cout << "\n===== ALLOTMENT RECORDS =====" << endl;
        for (int i = 0; i < allotments.size(); i++) {
            allotments[i].display();
        }
    }

    // ============================================================
    //  FILE HANDLING — Save and Load
    // ============================================================

    void saveBooksToFile() {
        ofstream file(booksFile);
        for (int i = 0; i < books.size(); i++) {
            // Each book saved as 4 lines: id, name, author, availability
            file << books[i].id          << "\n";
            file << books[i].name        << "\n";
            file << books[i].author      << "\n";
            file << books[i].isAvailable << "\n";
        }
        file.close();
    }

    void loadBooksFromFile() {
        ifstream file(booksFile);
        if (!file.is_open()) return; // file doesn't exist yet, that's fine

        string bid, bname, bauthor, avail;
        while (getline(file, bid)) {
            getline(file, bname);
            getline(file, bauthor);
            getline(file, avail);

            Book b(bid, bname, bauthor);
            b.isAvailable = (avail == "1"); // "1" means true
            books.push_back(b);
        }
        file.close();
    }

    void saveAllotmentsToFile() {
        ofstream file(allotmentFile);
        for (int i = 0; i < allotments.size(); i++) {
            file << allotments[i].studentName << "\n";
            file << allotments[i].bookId      << "\n";
            file << allotments[i].returnDate  << "\n";
        }
        file.close();
    }

    void loadAllotmentsFromFile() {
        ifstream file(allotmentFile);
        if (!file.is_open()) return;

        string sName, bId, rDate;
        while (getline(file, sName)) {
            getline(file, bId);
            getline(file, rDate);

            Student s(sName, bId, rDate);
            allotments.push_back(s);
        }
        file.close();
    }
};

// ============================================================
//  MAIN — menu loop
// ============================================================
int main() {

    // Step 1: Login
    Login loginSystem;
    bool loggedIn = false;

    // Give 3 attempts
    for (int attempt = 0; attempt < 3; attempt++) {
        if (loginSystem.authenticate()) {
            loggedIn = true;
            break;
        }
        if (attempt < 2)
            cout << "Try again. (" << 2 - attempt << " attempts left)" << endl;
    }

    if (!loggedIn) {
        cout << "\nToo many failed attempts. Exiting." << endl;
        return 0;
    }

    // Step 2: Menu
    Library lib;
    int choice;

    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Add Books"            << endl;
        cout << "2. Display All Books"    << endl;
        cout << "3. Check Availability"   << endl;
        cout << "4. Allot a Book"         << endl;
        cout << "5. Return a Book"        << endl;
        cout << "6. Display Allotments"   << endl;
        cout << "7. Exit"                 << endl;
        cout << "Enter your choice: ";
        cin  >> choice;

        switch (choice) {
            case 1: lib.addBooks();          break;
            case 2: lib.displayBooks();      break;
            case 3: lib.checkAvailability(); break;
            case 4: lib.allotBook();         break;
            case 5: lib.returnBook();        break;
            case 6: lib.displayAllotments(); break;
            case 7: cout << "\nThank you! Goodbye." << endl; break;
            default: cout << "\nInvalid choice. Try again." << endl;
        }

    } while (choice != 7);

    return 0;
}