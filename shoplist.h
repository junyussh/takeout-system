#include "shop.h"
#include <list>

class ShopList
{
private:
    list<Shop*> shops;
    list<string>* data;
public:
    ShopList();
    ShopList(string name, string phone, string address, string password);
    void newShop(string name, string phone, string address, string password);
    void newShop();
    void setData(list<string> *);
    void addData(string);
    ~ShopList();
};


