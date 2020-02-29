#include"food.h"

Food::Food(string name, int type, int amount, int price, int total, string shop, string user, string category)
{
    this->name = name;
    this->type = type;
    this->amount = amount;
    this->total = total;
    this->shop = shop;
    this->user = user;
    this->category = category;
}

Food::~Food()
{
}
