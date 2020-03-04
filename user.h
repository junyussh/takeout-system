#include<string>
using namespace std;
class User
{
private:
    string name;
    string card;
    string password;
public:
    User(string name, string card, string password);
    ~User();
};

