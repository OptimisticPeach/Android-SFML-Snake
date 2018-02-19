#ifndef GRID_DEF
#define GRID_DEF
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
class Grid : public sf::Drawable
{
public:

	Grid(size_t x, size_t y, const int BWidth, const int BHeight, float XS, float YS);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int Rows;

	int Cols;

	int BWidth;

	int BHeight;

	float YSkew;

	float XSkew;

	sf::Vector2f Pos;

	std::vector< std::vector<sf::Color> >  Tiles;

	sf::Vector2f GetSize();

	sf::Rect<float> GetBounds();
};
#endif