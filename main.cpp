#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>

using namespace std;

class login{
  protected:
   string username = "admin";
   int password = 1234;
  public:
  string usernme;
  int pasword;
  login(){
    cout<<"Enter the username: ";
    cin>>usernme;    
    cout<<"Enter password: ";
    cin>>pasword;
  };
};

class books{
    protected:
      vector<string> id;
      vector<string> author;
      vector<string> book_name;
      bool availability;
    public:
    void addbook();
     void displaybook();
     void allotbooks();
    };



class library: public books{
    public:

     void addbook(){
        int number_of_books;
        cout<<"Enter the number of books: ";
        cin>>number_of_books;
        id.resize(number_of_books);
        for(int i = 0; i<= number_of_books; i++){
           cout<<"Enter book id: ";
           cin>>id[i];
           cout<<id[i];
           cout<<"Enter book "<<i+1;
           cin>>book_name[i];
           cin.ignore();
           getline(cin, book_name[i]);
           cout<<endl;
           cout<<"Author name: ";
           cin>>author[i];
           cin.ignore();
           getline(cin, author[i]);
           cout<<endl;
         };
     };

     void displayBooks(){
      for(int i = 0; i <= book_name.size();i++){
        cout<<book_name[i]<<endl;
        cout<<id[i]<<endl;
        cout<<author[i]<<endl;
        cout<<endl;
     };
    };

     void returnbook();
     void addbook(){};
     void allotbook(){
        //book id
        
        //student name 
        //return date
      };
      void setavailability(){};
      void checkstatus(){};
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
 };
}