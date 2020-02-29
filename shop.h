#include<iostream>
#include<string>
using namespace std;
struct shop
{
    int data;
};
class Shop
{
private:
    shop head;
    string name;
    string phone;
    string address;
    string password;
public:
    shop*& getHead();
    Shop(string name, string phone, string address, string password);
    void printInfo();
    ~Shop();
};

