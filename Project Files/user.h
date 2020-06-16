#ifndef USER_INCLUDED
#define USER_INCLUDED

class User{
    private:
        //user variables
        std::string username, password;
    public:
        User(std::string us, std::string pw);
        void setUsername(std::string us);
        void setPassword(std::string pw);
        std::string getUsername();
        std::string getPassword();
};

#endif 
