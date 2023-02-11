#include<sstream> 
#include "clothing.h"

using namespace std;

Clothing::Clothing(const string category, const string name, double price, int qty, string size, string brand):
  Product(category, name, price, qty){
    size_ = size;
    brand_ = brand;
}

Clothing::~Clothing(){

}

set<string> Clothing::keywords() const{

  string kword = name_ + " " + brand_;
  kword = convToLower(kword);
  set<string> keywords = parseStringToWords(kword);
  
  return keywords;
}


string Clothing::displayString() const{
  string p = to_string(getPrice()); 
  string q = to_string(getQty());

  string ClothingDisplay = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n"
                  + p + " " + q + " left.";

  return ClothingDisplay;  
}

void Clothing::dump(ostream& os) const{

os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;

}