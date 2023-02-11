#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> newWords;
    std::string currentWord;
    std::stringstream ss;
    char currentLetter; //not sure if you need std::

    for (size_t i = 0; i < rawWords.length(); i++){ //go through all of rawWords by character
      currentLetter = rawWords[i];
      if (isalnum(currentLetter) || currentLetter == '.'){ //isalnum checks to see if it's a letter or num
        ss << currentLetter;  //if not punctuation, add to stringstream
      }
      else if(!ss.str().empty()){   //if we run into a punctuation and ss is not empty, we have our new word in ss
        ss >> currentWord;  //whatever word we have in ss will become a new word
        if (currentWord.length() >= 2){ //checks for length of word
          newWords.insert(currentWord);
        }
        ss.clear(); //clears ss, even if no word was inserted
      }
    }

  //final check if last char was a letter
    if (!ss.str().empty()){
      ss >> currentWord;
      if (currentWord.length() >= 2){
        newWords.insert(currentWord);
      }
    }

    return newWords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
