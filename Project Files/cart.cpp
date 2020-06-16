#include "cart.h"

// constructor
Cart::Cart(){

}

// remove all items in cart
void Cart::clearCart(){
    myCart.clear();
}

// add item/s into cart
void Cart::addToCart(int pos, int q, vector<Item> ss){
    Item s = ss[pos-1];
    bool found = false;

    for(int i = 0; i < myCart.size(); i++){
        //add quantity of item in Cart if item is already found in Cart
        if(myCart[i].getItemName() == s.getItemName()){
            found = true;
            myCart[i].addItemQuantity(q);
        }
    }
    //Put item in Cart if item is not found in Cart
    if(found == false){
        s.setItemQuantity(q);
        myCart.push_back(s);
    }
}

// remove an item from the cart
void Cart::removeFromCart(int pos,int q){
    bool found = false;
    int check = myCart[pos-1].getItemQuantity() - q;

    //loop to check if item is in Cart
    for(int i = 0; i < myCart.size(); i++){
        if((pos-1) == i){
            found = true;
            //if quantity of item is 0 after removing then delete the item
            if(check == 0){
                cout << myCart[pos-1].getItemName() << " removed from cart" << endl;
                myCart.erase(myCart.begin() + pos - 1);
            }
            //if quantity is >0 then just reduce the quantity
            else if(check > 0){
                myCart[pos-1].reduceItemQuantity(q);
                cout << myCart[pos-1].getItemName() << " removed from cart" << endl;
            }
            //if quantity removed is more than quantity in Cart
            else{
                cout << "invalid amount" << endl;
            }
        }
    }
    //if item is not found in Cart
    if(found == false){
        cout << "Item not found in cart!" << endl;
    }
}

//funciton to display the items in the cart
void Cart::showCart()
{
    cout << "============================" << endl
         << "Cart Items:" << endl
         << "============================" << endl;

    //loop to print all items in the cart
    for(int i = 0; i < myCart.size(); i++)
    {
        cout << i + 1 << ". " << myCart[i].getItemName() << " Quantity: " << myCart[i].getItemQuantity() << endl;
    }
}

//getter function to return Cart vector
vector<Item> Cart::getCart(){
    return myCart;
}

//print the bill and checkout
void Cart::printBill(){
    int total, pay, change;
    int subtotal = 0;
    string rupiah = "Rp.";
    cout << "==========================================================" << endl
         << "Product              " << "Price         " << "Quantity     " << "Total" << endl
         << "==========================================================" << endl;
    //calculate and display the total price of items(quantity*price) and subtotal(total price of all items)
    for(int i = 0; i < myCart.size(); i++){
        total = myCart[i].getItemPrice() * myCart[i].getItemQuantity();
        subtotal += myCart[i].getItemPrice() * myCart[i].getItemQuantity();
        printf("%-18s | Rp.%-10d | %-10d | Rp.%-10d\n", myCart[i].getItemName().c_str(), myCart[i].getItemPrice(), myCart[i].getItemQuantity(), total);
    }
    printf("%49c%d\n", 'Rp.', subtotal);
    while(true){
        cout << "Enter amount to pay:";
        cin >> pay;
        //get the change
        change = pay-subtotal;
        //if payment amount is less than the bill
        if(change < 0){
            cout << "Payment amount is not enough" << endl;
        }
        //transaction is successful
        else{
            printf("%48s%c%d\n", "Change: ", 'Rp.', change);
            cout << "\n==========================================================" << endl
                 << "Thank you for purchasing from us!" << endl
                 << "We will be sending out your item as soon as possible!" << endl
                 << "==========================================================" << endl;
            break;
        }
    }
}
