#include "book.h"


using namespace std;

Book::Book(const string category, const string name, double price, int qty, string isbn, string author):
  Product(category, name, price, qty)
{
  isbn_ = isbn;
  author_ = author;

}

Book::~Book(){

}

//name, author, ISBN 
set<string> Book::keywords() const{

  string kword = name_ + " " + author_;
  kword = convToLower(kword);
  set<string> keywords = parseStringToWords(kword);
  keywords.insert(isbn_);

  return keywords;
}

string Book::displayString() const{
  string p = to_string(getPrice());
  string q = to_string(getQty());

  string BookDisplay = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n"
                  + p + " " + q + " left.";

  return BookDisplay;
}

//
void Book::dump(ostream& os) const{


os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;

}