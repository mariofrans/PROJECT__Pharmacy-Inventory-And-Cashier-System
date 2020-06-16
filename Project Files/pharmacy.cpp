#include "pharmacy.h"
#include "user.h"
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

 // Print every Item's name, price, and stock in database
void Pharmacy::display(vector<Item> Stock){
    cout << "================================================" << endl
         << "    Product               " << "Price         " << "Quantity" << endl
         << "================================================" << endl;
    for(int i = 0; i < Stock.size(); i++){
        printf("%-2d. %-18s  | Rp.%-10d | %-10d\n", i+1, Stock[i].getItemName().c_str(), Stock[i].getItemPrice(), Stock[i].getItemQuantity());
    }
    cout << "================================================" << endl;
}

// display all the user/s in the database
void Pharmacy::displayUser(vector<User> userList){
    for(int i = 0; i < userList.size(); i++){
        cout << i+1 << " " << userList[i].getUsername() << endl;
    }
}

//getter funtion to return total revenue
int Pharmacy::getRevenue(){
    double total_revenue = 0;

    //loop through ecery index and sum all transactions made
    for(int i = 0; i < revenue.size(); i++){
        total_revenue += revenue[i];
    }
    return total_revenue;
}

//function for the user interface in the console
void Pharmacy::phOption(){
    int opt, opt1, opt2;
    string username, password, email, password2;
    while(true){
        cout << "=====================================" << endl
             << "Welcome to the Pharmacy" << endl
             << "To continue, please select one of the following: " << endl
             << "1. Login" << endl
             << "2. Register" << endl
             << "=====================================" << endl
             << "Input: ";
        appendToFile(to_string(getRevenue()), "totalrevenue.txt");
        cin >> opt1;
        if(opt1 == 1){
            //bool to check if login is successful or not
            bool login = false;
            // while the login fails, ask users to re-login (loop until successful)
            while(login == false){
                bool found = false;
                cout << "=====================================" << endl
                     << "To login, please enter the following:" << endl
                     << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;
                cout << "=====================================" << endl;
                for(int i = 0; i < userList.size(); i++){
                    // if the username and password matches the user database, login successful
                    if((userList[i].getUsername() == username) && (userList[i].getPassword() == password)){
                        cout << "Login successful!" << endl;
                        found = true;
                        login = true;
                    }
                }
                //if username/password input by user is not found in the database
                if(found == false){
                    cout << "Your username/password is incorrect!" << endl;
                }
                //if login is successful, bool = true
                if(login == true){
                    break;
                }
            }

            // after login, ask the user if they want to log in as a customer/store owner
            bool login2 = false;
            while(login2 == false){
                cout << "=====================================" << endl
                     << "Login as: " << endl
                     << "1. Customer" << endl
                     << "2. Manager" << endl
                     << "=====================================" << endl
                     << "Input: ";
                cin >> opt2;
                
                // nested if statements for the different options
                if(opt2 == 1){
                    while(true){
                       display(Stock);
                        cout << "=====================================" << endl
                             << "1. Add item/s to your cart" << endl
                             << "2. Remove cart item/s" << endl
                             << "3. View Cart" << endl
                             << "4. Initiate Checkout" << endl
                             << "5. Exit" << endl
                             << "=====================================" << endl
                             << "Input: ";
                        cin >> opt;
                        if(opt==1){
                            phAddToCart();
                        }
                        else if(opt==2){
                            //if cart is empty
                            if(Cart.getCart().empty()==true){
                                cout << "Your cart is currently empty" << endl;
                                continue;
                            }
                            //remove Item from Cart
                            phRemoveFromCart();
                        }
                        else if(opt==3){
                           Cart.showCart();
                        }
                        else if(opt==4){
                            //if cart is empty
                            if(Cart.getCart().empty()==true){
                                cout << "Your cart is currently empty" << endl;
                                continue;
                            }
                            double total, subtotal = 0;
                            //add the billing total to the revenue vector
                            for(int i = 0; i < Cart.getCart().size(); i++){
                                total = Cart.getCart()[i].getItemPrice() * Cart.getCart()[i].getItemQuantity();
                                subtotal += Cart.getCart()[i].getItemPrice() * Cart.getCart()[i].getItemQuantity();
                            }
                            revenue.push_back(subtotal);
                            phCheckout();
                            //clear contents in Cart
                            Cart.clearCart();
                            login2 = true;
                            break;
                        }
                        else if(opt==5){
                            bool foundInStock = false;
                            //return all Items in Cart to Stock if customer abandons checkout
                            for(int i = 0; i < Cart.getCart().size(); i++){
                                for(int j = 0; j < Stock.size(); j++){
                                    if(Cart.getCart()[i].getItemName() == Stock[j].getItemName()){
                                        Stock[j].addItemQuantity(Cart.getCart()[i].getItemQuantity());
                                        foundInStock = true;
                                        break;
                                    }
                                }
                                //if Item is not found in Stock
                                if(foundInStock == false){
                                    Stock.push_back(Cart.getCart()[i]);
                                }
                            }
                            //clear contents in Cart
                            Cart.clearCart();
                            login2 = true;
                            break;
                        }
                        //if input is out of range (1-5)
                        else{
                            cout << "Invalid Input!" << endl;
                        }
                    }
                }
                else if(opt2 == 2){
                    int opt3;
                    while(true){
                        cout << "=====================================" << endl
                             << "1. View Total Pharmacy Revenue" << endl
                             << "2. View Pharmacy Stock" << endl
                             << "3. Add New Product to Stock" << endl
                             << "4. Exit" << endl
                             << "=====================================" << endl
                             << "Input: ";
                        cin >> opt3;
                        if(opt3 == 1){
                            cout << "Total pharmacy revenue is: Rp." << getRevenue() << endl;
                        }
                        else if(opt3 == 2){
                            //display the current items in pharmacy Stock
                            cout << "================================================" << endl
                                 << "    Product               " << "Quantity        " << endl
                                 << "================================================" << endl;

                            for(int i = 0; i < Stock.size(); i++){
                                printf("%-2d. %-18s | %-10d\n", i+1, Stock[i].getItemName().c_str(), Stock[i].getItemQuantity());
                            }
                            cout << "================================================" << endl;
                        }
                        else if(opt3 == 3){
                            string npname;
                            double npprice;
                            int npquantity;
                            bool foundInStock = false, addNewProduct = false;
                            while(addNewProduct == false){
                                cout << "Name of New Product: ";
                                cin >> npname;
                                cout << "Price of New Product: ";
                                cin >> npprice;
                                cout << "Quantity of New Product: ";
                                cin >> npquantity;
                                for(int i = 0; i < Stock.size(); i++){
                                    if(Stock[i].getItemName() == npname){
                                        foundInStock = true;
                                        cout << "Item is already in Stock" << endl;
                                        break;
                                    }
                                }
                                if(npprice <= 0 || npquantity <= 0){
                                    cout << "Invalid price or quantity" << endl;
                                    continue;
                                }

                                if(foundInStock == false){
                                    string npdata = npname + ',' + to_string(npprice) + ',' + to_string(npquantity);
                                    Stock.push_back(Item(npname, npprice, npquantity));
                                    appendToFile(npdata, "stocks.txt");
                                    addNewProduct = true;
                                    break;
                                }
                            }
                        }
                        else if(opt3 == 4){
                            login2 = true;
                            break;
                        }
                        else{
                            cout << "Invalid Input!" << endl;
                        }
                    }

                }
                else{
                    cout << "Invalid Input!" << endl;
                }
            }


        }
        else if(opt1 == 2){
            bool regis = false;
            while(regis == false){
                bool found = false;
                cout << "=====================================" << endl
                     << "To register, please create a new account" << endl
                     << "Create new username: ";
                cin >> username;
                cout << "Create new password: ";
                cin >> password;
                cout << "Confirm new password: ";
                cin >> password2;
                cout << "=====================================" << endl;

                for(int i = 0; i < userList.size(); i++){
                    //if username is found in database
                    if(userList[i].getUsername() == username){
                        found = true;
                        cout << "This username already exists" << endl;
                        break;
                    }
                }
                //if username is not found
                if(found == false){
                    //if password confirmation succeeds
                    if(password == password2){
                        userList.push_back(User(username, password));
                        string userdata = username + ',' + password;
                        appendToFile(userdata, "userdatabase.txt");
                        regis = true;
                    }
                    //if password confirmation fails
                    else{
                        cout << "Please enter the same password for confirmation!" << endl;
                        continue;
                    }
                }
            }
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }
}


//function to add to cart and reducing quantity of stock in the pharmacy
void Pharmacy::phAddToCart(){
    int num, q, check;
    //display contents in Cart
    Cart.showCart();
    cout << "Input item index to be added to cart" << endl;
    cin >> num;
    cout << "Quantity: " << endl;
    cin >> q;
    //int variable check is for counting the quantity after removal from Stock to Cart
    check = Stock[num-1].getItemQuantity() - q;
    //if Item is still found in stock after removing
    if(check >= 0){
        //reduce quantity of Item in Pharmacy Stock
        Stock[num-1].reduceItemQuantity(q);
        cout << Stock[num-1].getItemName() << " successfully added to cart!" << endl;
        //if item in Stock is 0 after emoving
        if(Stock[num-1].getItemQuantity() == 0){
            //add Item to Cart
            Cart.addToCart(num, q, Stock);
            //erase item from Stock
            Stock.erase(Stock.begin() + num - 1);
        }
        //if Item is not fully removed from Stock
        else{
            Cart.addToCart(num, q, Stock);
        }
    }
    //if quantity after removal is < 0
    else if(check < 0){
        cout << "Invalid Amount" << endl;
    }
}

//function to remove from cart focusing on adding quantity of stock in pharmacy
void Pharmacy::phRemoveFromCart(){
    int num, q;
    //bool value to check if item is in Stock
    bool foundInStock = false;

    //display contents in Cart
    Cart.showCart();
    cout << "Input index number of item to be removed from the cart" << endl;
    cin >> num;
    cout << "Quantity: " << endl;
    cin >> q;
    //int variable check is for counting the quantity after removal from Cart to Stock
    int check = Cart.getCart()[num-1].getItemQuantity() - q;
    //if all quantity of the Item is removed
    if(check == 0){
        for(int i = 0; i < Stock.size(); i++){
            //if Item is found in Stock
            if(Cart.getCart()[num-1].getItemName() == Stock[i].getItemName()){
                foundInStock = true;
                //add the quantity of that Item
                Stock[i].addItemQuantity(q);
            }
        }
        //if Item is not found in Stock
        if(foundInStock == false){
            //add the Item to Stock
            Stock.push_back(Cart.getCart()[num-1]);
            //set its quantity to 'q'
            Stock.back().setItemQuantity(q);
        }
    }
    //if Item is not fully removed from Cart
    else if(check > 0){
        for(int i = 0; i < Stock.size(); i++){
            //if Item is found in Stock
            if(Cart.getCart()[num-1].getItemName() == Stock[i].getItemName()){
                foundInStock = true;
                //add the quantity of that Item in Stock
                Stock[i].addItemQuantity(q);
            }
        }
        //if item is not found in Stock
        if(foundInStock == false){
            //add the Item to Stock
            Stock.push_back(Cart.getCart()[num-1]);
            //set its quantity to 'q'
            Stock.back().setItemQuantity(q);
        }
    }
    //remove item from Cart
    Cart.removeFromCart(num, q);
}

//function for checking out of pharmacy(print bill and payment)
void Pharmacy::phCheckout(){
    //print the bill and do the billing system
    Cart.printBill();
}

//function for the creating the default stock of pharmacy and the users in the database
void Pharmacy::phStock(){
    string line, line2;
    ifstream infile;
    ifstream infile2;
    //open txt file for pharmacy stock
    infile.open("stocks.txt");
    //open txt file for pharmacy user database
    infile2.open("userdatabase.txt");

    //if file is found and able to be open then
    if(infile){
        //while file is being read
        while (infile){
            //get the line from the txt file
            getline (infile,line);
            //create a vector to store what is read from the txt file
            vector<string> result;
            //if line contains text/token
            if(line!=""){
                stringstream ss(line);
                while(ss.good()){
                    string substr;
                    getline(ss,substr,',');
                    //add token to result vector
                    result.push_back(substr);
                }
                //add the items to the pharmacy Stock
                Stock.push_back(Item(result[0],atof(result[1].c_str()), stoi(result[2])));
            }
        }
        infile.close();
    }
    //if file is cannot be opened
    else{
        cout << "unable to open file";
    }

    //if file is found and able to be open
    if(infile2){
        //while file is being read
        while (infile2){
            //get the line from the txt file
            getline (infile2,line2);
            //create a vector to store what is read from the txt file
            vector<string> result2;
            //if line contains text/token
            if(line2!=""){
                stringstream ss(line2);
                while(ss.good()){
                    string substr;
                    getline(ss,substr,',');
                    //add token to result vector
                    result2.push_back(substr);
                }
                //add the users to the pharmacy database
                userList.push_back(User(result2[0],result2[1]));
            }
        }
        infile2.close();
    }
    //if file is cannot be opened
    else{
        cout << "unable to open file";
    }
}

//function to simulate the online pharmacy experience
void Pharmacy::runPharmacy()
{
    //input all Items and Users into database
    phStock();
    //simulate online pharmacy experience
    phOption();
}

//function to append data to txt file
void Pharmacy::appendToFile(string text, string filename)
{
    string line;
    ofstream myfile;
    myfile.open(filename, ios::out | ios::app);
    myfile << text << endl;
    myfile.close();
}
                         
