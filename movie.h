//#include<string>
#include "product.h"
#include "util.h"

class Movie: public Product{
public:
    Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
    ~Movie();

    std::set<std::string> keywords() const;

    //bool isMatch(std::vector<std::string>& searchTerms) const; //not needed for this hw

    std::string displayString() const;

    void dump(std::ostream& os) const;

private:
    std::string genre_;
    std::string rating_;
};