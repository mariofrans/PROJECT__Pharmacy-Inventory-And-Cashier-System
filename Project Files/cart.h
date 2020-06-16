#ifndef CART_INCLUDED
#define CART_INCLUDED

#include "item.h"

class Cart{
    private:
        vector<Item> myCart;
    public:
        Cart();
        void addToCart(int pos, int q, vector<Item> Stock);
        void removeFromCart(int pos, int q);
        void showCart();
        vector<Item> getCart();
        void printBill();
        void clearCart();
};
#endif
