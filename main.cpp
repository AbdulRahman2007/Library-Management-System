#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// ============================================================
//  BOOK CLASS — stores one book record
// ============================================================
class Book {
public:
    string id;
    string name;
    string author;
    bool isAvailable;

    Book() : isAvailable(true) {}

    Book(const string &bookId, const string &bookName, const string &bookAuthor)
        : id(bookId), name(bookName), author(bookAuthor), isAvailable(true) {}

    void display() const {
        cout << "  Book ID   : " << id << endl;
        cout << "  Name      : " << name << endl;
        cout << "  Author    : " << author << endl;
        cout << "  Status    : " << (isAvailable ? "Available" : "Allotted") << endl;
        cout << "  ----------------------------" << endl;
    }
};

// ============================================================
//  STUDENT CLASS — stores one book allotment record
// ============================================================
class Student {
public:
    string studentName;
    string bookId;
    string returnDate;

    Student() {}

    Student(const string &name, const string &book, const string &date)
        : studentName(name), bookId(book), returnDate(date) {}

    void display() const {
        cout << "  Student   : " << studentName << endl;
        cout << "  Book ID   : " << bookId << endl;
        cout << "  Return by : " << returnDate << endl;
        cout << "  ----------------------------" << endl;
    }
};

// ============================================================
//  LOGIN CLASS — handles admin authentication
// ============================================================
class Login {
private:
    const string correctUsername = "admin";
    const int    correctPassword = 1234;

public:
    bool authenticate() {
        string enteredUser;
        int enteredPass;

        cout << "\n===== LIBRARY LOGIN =====" << endl;
        cout << "Username : ";
        cin  >> enteredUser;
        cout << "Password : ";
        cin  >> enteredPass;

        if (enteredUser == correctUsername && enteredPass == correctPassword) {
            cout << "\nLogin successful! Welcome, Admin." << endl;
            return true;
        }

        cout << "\nInvalid username or password." << endl;
        return false;
    }
};

// ============================================================
//  LIBRARY CLASS — manages books, allotments, and file storage
// ============================================================
class Library {
private:
    vector<Book>    books;
    vector<Student> allotments;
    const string    booksFile     = "books.txt";
    const string    allotmentFile = "allotments.txt";

    void clearInput() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int findBookIndex(const string &bookId) const {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].id == bookId) return static_cast<int>(i);
        }
        return -1;
    }

    int findAllotmentIndexByBookId(const string &bookId) const {
        for (size_t i = 0; i < allotments.size(); i++) {
            if (allotments[i].bookId == bookId) return static_cast<int>(i);
        }
        return -1;
    }

public:
    Library() {
        loadBooksFromFile();
        loadAllotmentsFromFile();
    }

    void addBooks() {
        int n;
        cout << "\nHow many books do you want to add? ";
        cin  >> n;
        clearInput();

        for (int i = 0; i < n; i++) {
            string bid, bname, bauthor;
            cout << "\n-- Book " << i + 1 << " --" << endl;
            cout << "  Enter Book ID   : ";
            getline(cin, bid);
            cout << "  Enter Book Name : ";
            getline(cin, bname);
            cout << "  Enter Author    : ";
            getline(cin, bauthor);

            Book book(bid, bname, bauthor);
            books.push_back(book);
            cout << "  Book added successfully!" << endl;
        }

        saveBooksToFile();
    } // addBooks: reads book details from user input and saves them to file

    void removeBook() {
        string bookId;
        cout << "\nEnter Book ID to remove: ";
        clearInput();
        getline(cin, bookId);

        int index = findBookIndex(bookId);
        if (index < 0) {
            cout << "Book with ID " << bookId << " not found." << endl;
            return;
        }

        if (!books[index].isAvailable) {
            int allotIndex = findAllotmentIndexByBookId(bookId);
            if (allotIndex >= 0) {
                allotments.erase(allotments.begin() + allotIndex);
            }
        }

        books.erase(books.begin() + index);
        saveBooksToFile();
        saveAllotmentsToFile();
        cout << "Book removed successfully." << endl;
    } // removeBook: deletes a book and any matching allotment record, then updates files

    void displayBooks() const {
        if (books.empty()) {
            cout << "\nNo books in the library yet." << endl;
            return;
        }

        cout << "\n===== ALL BOOKS =====" << endl;
        for (const auto &book : books) {
            book.display();
        }
    } // displayBooks: shows every stored book and its availability

    void checkAvailability() {
        string searchId;
        cout << "\nEnter Book ID to check: ";
        clearInput();
        getline(cin, searchId);

        int index = findBookIndex(searchId);
        if (index < 0) {
            cout << "\nNo book found with ID: " << searchId << endl;
            return;
        }

        cout << "\nBook availability:" << endl;
        books[index].display();
    } // checkAvailability: looks up a book by ID and displays its current status

    void allotBook() {
        string searchId;
        cout << "\nEnter Book ID to allot: ";
        clearInput();
        getline(cin, searchId);

        int index = findBookIndex(searchId);
        if (index < 0) {
            cout << "\nNo book found with ID: " << searchId << endl;
            return;
        }

        if (!books[index].isAvailable) {
            cout << "This book is already allotted." << endl;
            return;
        }

        string studentName;
        string returnDate;
        cout << "Enter Student Name : ";
        getline(cin, studentName);
        cout << "Enter Return Date  : ";
        getline(cin, returnDate);

        books[index].isAvailable = false;
        allotments.emplace_back(studentName, searchId, returnDate);

        saveBooksToFile();
        saveAllotmentsToFile();
        cout << "Book allotted successfully to " << studentName << "!" << endl;
    } // allotBook: assign a book to a student and create an allotment record

    void returnBook() {
        string searchId;
        cout << "\nEnter Book ID to return: ";
        clearInput();
        getline(cin, searchId);

        int index = findBookIndex(searchId);
        if (index < 0) {
            cout << "\nNo book found with ID: " << searchId << endl;
            return;
        }

        if (books[index].isAvailable) {
            cout << "Book is already available in the library." << endl;
            return;
        }

        books[index].isAvailable = true;
        int allotIndex = findAllotmentIndexByBookId(searchId);
        if (allotIndex >= 0) {
            allotments.erase(allotments.begin() + allotIndex);
        }

        saveBooksToFile();
        saveAllotmentsToFile();
        cout << "Book returned successfully." << endl;
    } // returnBook: marks a book available again and removes its allotment record

    void displayAllotments() const {
        if (allotments.empty()) {
            cout << "\nNo books are currently allotted." << endl;
            return;
        }

        cout << "\n===== ALLOTMENT RECORDS =====" << endl;
        for (const auto &record : allotments) {
            record.display();
        }
    } // displayAllotments: prints all current student-book allotment records

    void checkAllotment() {
        string searchId;
        cout << "\nEnter Book ID to check allotment: ";
        clearInput();
        getline(cin, searchId);

        int allotIndex = findAllotmentIndexByBookId(searchId);
        if (allotIndex < 0) {
            cout << "\nNo allotment found for Book ID: " << searchId << endl;
            return;
        }

        cout << "\nAllotment details:" << endl;
        allotments[allotIndex].display();
    } // checkAllotment: finds an allotment by book ID and displays its student record

    void saveBooksToFile() const {
        ofstream file(booksFile);
        for (const auto &book : books) {
            file << book.id << '\n';
            file << book.name << '\n';
            file << book.author << '\n';
            file << (book.isAvailable ? "1" : "0") << '\n';
        }
    } // saveBooksToFile: writes all book records to a local text file

    void loadBooksFromFile() {
        ifstream file(booksFile);
        if (!file.is_open()) return;

        string bid, bname, bauthor, avail;
        while (getline(file, bid)) {
            if (!getline(file, bname)) break;
            if (!getline(file, bauthor)) break;
            if (!getline(file, avail)) break;

            Book book(bid, bname, bauthor);
            book.isAvailable = (avail == "1");
            books.push_back(book);
        }
    } // loadBooksFromFile: restores saved book records from disk into memory

    void saveAllotmentsToFile() const {
        ofstream file(allotmentFile);
        for (const auto &record : allotments) {
            file << record.studentName << '\n';
            file << record.bookId << '\n';
            file << record.returnDate << '\n';
        }
    } // saveAllotmentsToFile: writes allotment records to a separate text file

    void loadAllotmentsFromFile() {
        ifstream file(allotmentFile);
        if (!file.is_open()) return;

        string name, bookId, date;
        while (getline(file, name)) {
            if (!getline(file, bookId)) break;
            if (!getline(file, date)) break;
            allotments.emplace_back(name, bookId, date);
        }
    } // loadAllotmentsFromFile: restores allotment records from disk into memory
};

int main() {
    Login loginSystem;
    bool loggedIn = false;

    for (int attempt = 0; attempt < 3; attempt++) {
        if (loginSystem.authenticate()) {
            loggedIn = true;
            break;
        }
        if (attempt < 2) {
            cout << "Try again. (" << 2 - attempt << " attempts left)" << endl;
        }
    }

    if (!loggedIn) {
        cout << "\nToo many failed attempts. Exiting." << endl;
        return 0;
    }

    Library lib;
    int choice;

    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Add Books" << endl;
        cout << "2. Remove Book" << endl;
        cout << "3. Display All Books" << endl;
        cout << "4. Check Availability" << endl;
        cout << "5. Allot a Book" << endl;
        cout << "6. Return a Book" << endl;
        cout << "7. Display Allotments" << endl;
        cout << "8. Check Allotment" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: lib.addBooks();          break;
            case 2: lib.removeBook();        break;
            case 3: lib.displayBooks();      break;
            case 4: lib.checkAvailability(); break;
            case 5: lib.allotBook();         break;
            case 6: lib.returnBook();        break;
            case 7: lib.displayAllotments(); break;
            case 8: lib.checkAllotment();    break;
            case 9: cout << "\nThank you! Goodbye." << endl; break;
            default: cout << "\nInvalid choice. Try again." << endl;
        }
    } while (choice != 9);

    return 0;
}
