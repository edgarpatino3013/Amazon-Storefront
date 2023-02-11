#include <map>
#include "datastore.h"
#include "util.h"


class myDataStore : public DataStore {
public:
    myDataStore();

    ~myDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    //REQUIRED
    void addToCart(std::string username, Product* p);

    void viewCart(std::string username);

    void buyCart(std::string username);



    private:

    std::vector<Product*> products_; //all products
    std::map<std::string, User*> names_users; //map of (names, users)
    std::map<std::string, std::set<Product*>> keywords_products; //map of (keywords, products)
    std::map<std::string, std::vector<Product*>> username_cart; //map of (usernames, carts)

};
