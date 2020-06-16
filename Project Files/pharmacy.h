#ifndef PHARMACY_INCLUDED
#define PHARMACY_INCLUDED

#include "cart.h"
#include "item.h"
#include "user.h"

class Pharmacy{
    private:
        // create 3 vectors (these are the 'list' that we want to modify)
        vector<Item> Stock;
        vector <User> userList;
        vector<int> revenue;

        //create Cart object
        Cart Cart;

        void phStock();
        void phOption();
        void phAddToCart();
        void phRemoveFromCart();
        void phCheckout();
        void display(vector<Item> Stock);
        void displayUser(vector<User> userList);
        int getRevenue();
        void appendToFile(string text,string filename);

    public:
        void runPharmacy();
};


#endif
