#include <iostream>
#include <string>
#include "shop.h"
using namespace std;

Shop::Shop(string name, string phone, string address, string password)
{
    this->name = name;
    this->phone = phone;
    this->address = address;
    this->password = password;
}
void Shop::printInfo()
{
    cout << this->name << endl;
}