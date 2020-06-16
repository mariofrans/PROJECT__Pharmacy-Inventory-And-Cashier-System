#ifndef ITEM_INCLUDED
#define ITEM_INCLUDED

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Item class
class Item{
    private:
        //variables for the item object
        int itemPrice;
        int itemQuantity;
        string itemName;

    public:
        Item(string n, int p, int q);
        void setItemPrice(int p);
        void setItemQuantity(int q);
        void setItemName(string n);
        int getItemPrice();
        int getItemQuantity();
        string getItemName();
        void reduceItemQuantity(int q);
        void addItemQuantity(int q);
};

#endif
