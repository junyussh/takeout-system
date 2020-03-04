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
    string name;
    string phone;
    string address;
    string password;
public:
    Shop(string name, string phone, string address, string password);
    void printInfo();
    ~Shop();
};

