
#include "Snake.hpp"
#include <math.h>
#include "Util.hpp"

#define TWO_DIVIDED_BY_PI 0.63661977236758134307553505349006f

Snake::Snake(sf::Vector2f start, sf::Vector2f Bounds)
{
	this->Bounds = sf::FloatRect(sf::Vector2f(0, 0), Bounds);
	this->Head = start;
	this->Body = std::vector<sf::Vector2f>(3, start); //Will have three leading tails
	this->GhostTail = start;
}

void Snake::Move()
{

	sf::Vector2f velocity = this->Dir;

	this->GhostTail = this->Body[this->Body.size() - 1];

	/*for (int i = this->Body.size() - 1; i > 1; i--) {
		this->Body[i] = this->Body[i - 1];
	}*/

	for (int i = this->Body.size() - 1; i != 0; i--)
	{
		this->Body[i] = this->Body[i - 1];
	}

	this->Body[0] = this->Head;

	this->Head += velocity;

	if(!this->Bounds.contains(this->Head)) this->Head -= velocity;
}

void Snake::setVel(sf::Vector2f start, sf::Vector2f stop)
{
	int dir = static_cast<int>(round((getAngle(stop, start) * TWO_DIVIDED_BY_PI))) % 4;

	// int dir = static_cast<int>(round((atan2f(((-a.y)+b.y)/(a.x - b.x)) + 2* 3.1415926535897932384626433832795f * (2 / 3.1415926535897932386426433832795f)))) % 4;
	/*start = sf::Vector2f(start.x, -start.y);
	stop = sf::Vector2f(stop.x, -stop.y);
	//first we set one of them to zero so we can do relative calculations
	sf::Vector2f centered = stop - start;
	//We need the angle and we have the hypotenuse and the height, therefore we use asin of height/hypotenuse

	float angle = (atan2(centered.y, centered.x)+3.1415926535f) * 180 / 3.1415926535f; //asin returns radians

	//We use the rule of three to make it between 0 and 400

	float newAngle = (angle * 400) / 360;
	//We then divide by 100 and round down and cast to int to get the direction

	newAngle /= 100;

	int dir = static_cast<int>(round(newAngle));

	dir %= 4;

	
	
	This all can be simpified to:

	              ( (-stop.y)+start.y )    
	dir = ||arctan( ----------------- ) *  (2/PI)||
				  ( stop.x - start.x  )    
	*/

	sf::Vector2f old = this->Dir;

	switch (dir)
	{
	case 0:
		this->Dir = sf::Vector2f(-1, 0);
		break;
	case 1:
		this->Dir = sf::Vector2f(0, 1);
		break;
	case 2:
		this->Dir = sf::Vector2f(1, 0);
		break;
	case 3:
		this->Dir = sf::Vector2f(0, -1);
		break;
	}

	if(old + this->Dir == sf::Vector2f(0,0)) this->Dir = old;
}

bool Snake::IsStuffed()
{
	//Will always return false beacuse we need to implement death
	bool isBodyStuffed = true;
	for (int i = 1; i != this->Body.size() - 1; i++)
	{
		isBodyStuffed &= this->Body[i] == this->Body[i - 1];
	}
	isBodyStuffed &= this->Head == this->Body[0];
	return isBodyStuffed;
}

bool Snake::CheckDead()
{
	int isBodyStuffed = -1;
	for (sf::Vector2<float> v : Body)
	{
		if (isBodyStuffed == -1)
		{
			isBodyStuffed = false;
			continue;
		}
		isBodyStuffed |= v == this->Head;
	}
	//isBodyStuffed |= this->Bounds.contains(this->Head);
	isBodyStuffed |= this->Head == this->Body[0];
	return isBodyStuffed;
}

bool Snake::Contains(sf::Vector2f pos){
	bool end = false;
	end |= Head == pos;
	for(sf::Vector2f i : Body){
		end |= pos == i;
	}
	return end;
}