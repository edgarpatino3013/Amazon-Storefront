#include<sstream> 
#include "movie.h"

using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, string genre, string rating):
  Product(category, name, price, qty){
    genre_ = genre;
    rating_ = rating;
}

Movie::~Movie(){

}

set<string> Movie::keywords() const{

  string kword = name_ + " " + genre_;
  kword = convToLower(kword);
  set<string> keywords = parseStringToWords(kword);

  return keywords;
}


string Movie::displayString() const{

  string p = to_string(getPrice());
  string q = to_string(getQty());

  string MovieDisplay = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n"
                  + p + " " + q + " left.";

  return MovieDisplay; 
}

void Movie::dump(ostream& os) const{

os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;

}