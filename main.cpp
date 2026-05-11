#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

class books{
    protected:
      vector<string> id;
      vector<string> author;
      vector<string> book_name;
      bool availability;
    public:
      void addbook(){
        int number_of_books;
        cout<<"Enter the number of books: ";
        cin>>number_of_books;
        for(int i = 0; i<= number_of_books; i++){
          cout<<"Enter book id "<<endl;
          cin>>id[i];
          cout<<"Enter book "<<i+1;
          cin>>book_name[i];
          cout<<endl;
          cout<<"Author name: ";
          cin>>author[i];
          cout<<endl;
        };
      };
      };
      void allotbook();
      void setavailability();
      void checkstatus();

class library: public books{
    public:
     void displayBooks(){
      for(int i = 0; i <= sizeof(book_name);i++){
        cout<<book_name[i]<<endl;
        cout<<id[i]<<endl;
        cout<<author[i]<<endl;
        cout<<endl;
     };};


     void addbooks();
     void allotbook();
     void returnbook();

};

int main(){
  library l;
  char decsn;
 l.addbook();
 cout<<"Do you wanna display books (Y/N): ";
 cin>>decsn;
 if(decsn == 'Y' || decsn == 'y'){
  l.displayBooks();
 }else{
  cout<<"Thanks for visiting sir!!";
 }
}