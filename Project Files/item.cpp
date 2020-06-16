#include "item.h"

// Item constructor
Item::Item(string n, int p, int q){
    itemName = n;
    itemPrice = p;
    itemQuantity = q;
}

//setter functions for item price
void Item::setItemPrice(int p){
    itemPrice = p;
}

//setter functions for item quantity
void Item::setItemQuantity(int q){
    itemQuantity = q;
}

//setter functions for item name
void Item::setItemName(string n){
    itemName = n;
}

//getter functions for item price
int Item::getItemPrice(){
    return itemPrice;
}

//getter functions for item quantity
int Item::getItemQuantity(){
    return itemQuantity;
}

//getter functions for item name
string Item::getItemName(){
    return itemName;
}

//function to reduce quantity of an item
void Item::reduceItemQuantity(int q){
    itemQuantity -= q;
}

//function to increase quantity of an item
void Item::addItemQuantity(int q){
    itemQuantity += q;
}
