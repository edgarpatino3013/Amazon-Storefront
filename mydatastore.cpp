#include "mydatastore.h"
#include <iostream>

using namespace std;

myDataStore::myDataStore(){

}

myDataStore::~myDataStore(){
  for (map<string, User*>::iterator it = names_users.begin(); it != names_users.end(); ++it){
    delete it->second;
  }

  for (size_t i = 0; i < products_.size(); i++){
    delete products_[i];
  }

}

//* Adds a product to the data store
void myDataStore::addProduct(Product* p){

  products_.push_back(p);

  set<string> tempKeyWords = p->keywords();

  //update kewords_products
  set<string>::iterator it;
  for (it = tempKeyWords.begin(); it !=tempKeyWords.end(); ++it ){
    if (keywords_products.find(*it) != keywords_products.end()){
        (keywords_products.find(*it)->second).insert(p);
        //keywords_products[*it].insert(p);
    }
    else{
      set<Product*> newProduct;
      newProduct.insert(p);
      keywords_products.insert(make_pair(*it, newProduct));
    }
  }

}

//* Adds a user to the data store
void myDataStore::addUser(User* u){

  names_users.insert(make_pair(u->getName(),u));

}

/**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
vector<Product*> myDataStore::search(vector<string>& terms, int type){

  vector<Product*> sResults;

  //CASE 1: EMPTY TERMS 
  if (terms.empty()){
    return sResults;
  }
  //CASE 2: 1 TERM
  if (terms.size() == 1){
    if (keywords_products.find(terms[0]) != keywords_products.end()){
      set<Product*>::iterator it;
      for (it = keywords_products[terms[0]].begin(); it != keywords_products[terms[0]].end(); ++it){
        sResults.push_back(*it);
      }
    }
    return sResults;
  }

  //CASE 3: 2 OR MORE WORDS 
  set<Product*> sSet;
  //AND
  if (type == 0){
    if (keywords_products.find(terms[0]) != keywords_products.end()){
      sSet = keywords_products[terms[0]];
    }
    else{
      return sResults;
    }
    for (size_t i = 1; i < terms.size(); i++){
      if(keywords_products.find(terms[i]) != keywords_products.end()){
        sSet = setIntersection(keywords_products[terms[i]], sSet);
      }
      else{
        return sResults;
      }
    }
  }
  //OR
  else if(type == 1){
    for (size_t i = 0; i < terms.size(); i++){
      if (keywords_products.find(terms[i]) != keywords_products.end()){
        sSet = setUnion(keywords_products[terms[i]], sSet);
      }
    }
  }
  set<Product*>::iterator it;
  for (it = sSet.begin(); it != sSet.end(); ++it){
    sResults.push_back(*it);
  }

  return sResults;

}

void myDataStore::dump(ostream& ofile){

  set<Product*> allProducts;
  for (size_t i = 0; i < products_.size(); i++){
    allProducts.insert(products_[i]); 
  }

//product part
  ofile << "<products>" << endl;
  for (set<Product*>::iterator it = allProducts.begin(); it != allProducts.end(); ++it){
    (*it)->dump(ofile); //dump product info
  }
  ofile << "</products>" << endl;

//users part

  ofile << "<users>" << endl;
  for (map<string, User*>::iterator it = names_users.begin(); it != names_users.end(); ++it){
    it->second->dump(ofile);
  }
  ofile << "</users>"; //no endl;

}

void myDataStore::addToCart(std::string username, Product* p){

  if (names_users.find(username) == names_users.end()){
    cout << "Invalid request" << endl;
  }
  else{
    if(username_cart.find(username) == username_cart.end()){
      vector<Product*> newCart;
      username_cart.insert(make_pair(username, newCart));
    }
    //user has cart
    username_cart.find(username)->second.push_back(p);
  }

}

void myDataStore::viewCart(std::string username){

  //check for users and carts
  if (names_users.find(username) == names_users.end()){
      cout << "Invalid username" << endl;
  }
  else if (username_cart.find(username) == username_cart.end()){
    cout << "Empty Cart" << endl;
  }

    else{
      vector<Product*> cart = username_cart[username];
      size_t cartSize = cart.size();
      for(size_t i = 0; i < cartSize; i++){
        cout << "Product " << i+1 << endl;
        cout << cart[i]->displayString() << endl;
      }
    }
    
  
  
}

void myDataStore::buyCart(std::string username){

  if (names_users.find(username) == names_users.end()){
    cout << "Invalid username" << endl;
  }
  else if(username_cart.find(username) == username_cart.end()){
    cout << "Empty Cart" << endl;
  } 
  
  else{
    
    vector<Product*> retrunedCart;
    for(size_t i = 0; i < username_cart[username].size(); i++){
      if (names_users[username]->getBalance() - username_cart[username][i]->getPrice() >= 0 && username_cart[username][i]->getQty() > 0){
        names_users[username]->deductAmount(username_cart[username][i]->getPrice());
        username_cart[username][i]->subtractQty(1);
      }
      else{
        retrunedCart.push_back(username_cart[username][i]); //stuff that was not bought
      }
    }

    username_cart[username] = retrunedCart;
  }
  
}