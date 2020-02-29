#include<string>
using namespace std;
class Food
{
private:
    string name;
    int type;
    int amount;
    int price;
	int total;
    string shop;
    string user;
    string category;
public:
    Food(string name, int type, int amount, int price, int total, string shop, string user, string category);
    ~Food();
};
