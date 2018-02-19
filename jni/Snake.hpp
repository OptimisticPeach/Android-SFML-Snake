#ifndef SNAKE_DEF
#define SNAKE_DEF
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <vector>

class Snake
{
public:
	
	Snake(sf::Vector2f start, sf::Vector2f Bounds);
	sf::Vector2f Head;
	std::vector<sf::Vector2f> Body;
	sf::Vector2f GhostTail;
	sf::FloatRect Bounds;
	sf::Vector2f Dir;
	void Move();

	bool CheckDead();

	bool Contains(sf::Vector2f pos);

	void setVel(sf::Vector2f start, sf::Vector2f stop);

	bool IsStuffed();
};

#endif