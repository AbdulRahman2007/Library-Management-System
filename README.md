# Library Management System
A simple C++ library management program designed for a semester project.

## Overview
This project allows an admin to:
- log in with a username and password
- add books to the library
- display the list of books

> Note: The current implementation stores book data only in memory during runtime.

## Features
- Admin authentication
- Add one or more books
- Display all books in the library

## Files
- `main.cpp` — main source file containing the library logic
- `README.md` — project documentation

## Build and Run
### Using PowerShell
```powershell
cd "C:\Users\PMLS\OneDrive\Desktop\New folder\Library_management_System\Library-Management-System"
g++ -g main.cpp -o main.exe
.\main.exe
```

### Using Bash / Git Bash
```bash
cd "/c/Users/PMLS/OneDrive/Desktop/New folder/Library_management_System/Library-Management-System"
g++ -g main.cpp -o main
./main
```

## Login Credentials
- Username: `admin`
- Password: `1234`

## Notes
- Enter the number of books to add, then provide each book ID, title, and author.
- After adding books, choose `Y` to display the saved books.
- This project is a good starting point for adding persistent storage, book allotment, and return tracking.

