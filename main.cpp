#include <iostream>
#include <string.h>
using namespace std;

class books{
    private:
      int id;
      int author;
      string book_name;
      bool availability;
    public:
      void addbook();
      void allotbook();
      void setavailability();
      void checkstatus();
};

class library{
    public:
     void displayBooks();
     void addbooks();
     void allotbook();
     void returnbook();
     
};