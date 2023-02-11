//#include <iostream>
//#include <set>
//#include <string>
#include "util.h"
#include "book.h"
#include "product.h"
#include "movie.h"

using namespace std;

int main(){

  set <string> temp1 = {"Edgar", "Sbou", "Cheener.7162921", "Tyson", "William"};
  set <string> temp2 = {"Edgar", "GAGJSJ", "Tyson", "GSBIIABB", "Sbou", "Cheener.7162921"};

  set <string> temp = setUnion(temp1, temp2);

  set<string>::iterator it;

  for (it = temp.begin(); it != temp.end(); ++it){
    cout << *it << endl;
  }

  // Book temp("BookName", 55.87, 1, "William", "1-GSABI172");

  // string stemp = temp.displayString();

  // cout << stemp << endl;



return 0;
}
