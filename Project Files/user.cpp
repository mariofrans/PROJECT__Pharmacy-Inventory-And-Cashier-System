#include <iostream>
#include <string>
#include "user.h"
using namespace std;

//constructor for user object
User::User(string us, string pw){
    username = us;
    password = pw;
}

//setter function for User's username
void User::setUsername(string us){
    username = us;
}

//setter function for User's password
void User::setPassword(string pw){
    password = pw;
}

//getter function for User's username
string User::getUsername(){
    return username;
}

//getter function for User's password
string User::getPassword(){
    return password;
}

