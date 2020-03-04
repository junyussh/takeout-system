#include "shoplist.h"

ShopList::ShopList()
{
    this->data = new list<string>;
}
ShopList::ShopList(string name, string phone, string address, string password)
{
    this->data = new list<string>;
    this->newShop(name, phone, address, password);
}

void ShopList::newShop(string name, string phone, string address, string password)
{
    Shop *shop = new Shop(name, phone, address, password);
    this->shops.push_back(shop);
}
void ShopList::setData(list<string> *value)
{
    data = value;
}
void ShopList::newShop()
{
    list<string>::iterator it = data->begin();
    string name = *(it++);
    string phone = *(it++);
    string address = *(it++);
    string password = *it;
    this->newShop(name, phone, address, password);
}

void ShopList::addData(string value)
{

    this->data->push_front(value);
}
ShopList::~ShopList()
{
}