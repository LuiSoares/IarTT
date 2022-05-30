#include "card.hpp"

Card::Card(string color)
{
	this->color = color;
}

string Card::getColor()
{
return this->color;
}

void Card::setCard(string color)
{
this->color = color;
}
