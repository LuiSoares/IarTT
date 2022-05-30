#include <iostream>
#include <map>
using namespace std;

class Card
{
public:
Card(string color);
string getColor();
void setCard(string color);
private:
string color;
};
