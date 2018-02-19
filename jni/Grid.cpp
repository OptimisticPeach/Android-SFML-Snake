

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "Grid.hpp"
#include <vector>

Grid::Grid(const size_t x, const size_t y, const int BWidth, const int BHeight, float XS, float YS)
{
	this->Cols = x;
	this->Rows = y;
	this->BWidth = BWidth;
	this->BHeight = BHeight;
	this->Tiles = std::vector<std::vector<sf::Color>>(x, std::vector<sf::Color>(y, sf::Color::Black));
	XSkew = XS;
	YSkew = YS;
}

void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	//drawOverlay(target, states);
	//target.clear(sf::Color(42, 40, 42));
	for (int i = 0; i != this->Tiles.size(); i++)
	{
		for (int j = 0; j != this->Tiles[i].size(); j++)
		{
			sf::RectangleShape RectO(sf::Vector2f(this->BWidth, this->BHeight));
			RectO.setFillColor(sf::Color::Black);
			RectO.setPosition(sf::Vector2f(1 + i * (BWidth + 1), 1 + j * (BWidth + 1)) + Pos);
			target.draw(RectO, states);
		}
	}
	for (int i = 0; i != this->Tiles.size(); i++)
	{ //X
		for (int j = 0; j != this->Tiles[i].size(); j++)
		{ //Y
			if (Tiles[i][j] == sf::Color::Black)
				continue;
			sf::RectangleShape Bottom(sf::Vector2f(this->BWidth, this->BHeight));
			Bottom.setFillColor(Tiles[i][j] - sf::Color(90, 90, 90, 0));
			Bottom.setPosition(sf::Vector2f((1 + i * (BWidth + 1) + 2 * XSkew) + Pos.x, (1 + j * (BWidth + 1) + 2 * YSkew) + Pos.y));
			target.draw(Bottom, states);
			sf::RectangleShape Middle(sf::Vector2f(this->BWidth, this->BHeight));
			Middle.setFillColor(Tiles[i][j] - sf::Color(50, 50, 50, 0));
			Middle.setPosition(sf::Vector2f((1 + i * (BWidth + 1) + XSkew) + Pos.x, (1 + j * (BWidth + 1) + YSkew) + Pos.y));
			target.draw(Middle, states);
			sf::RectangleShape Top(sf::Vector2f(this->BWidth, this->BHeight));
			Top.setFillColor(Tiles[i][j]);
			Top.setPosition(sf::Vector2f((1 + i * (this->BWidth + 1)) + Pos.x, (1 + j * (this->BHeight + 1)) + Pos.y));
			target.draw(Top, states);
		}
	}
}

sf::Rect<float> Grid::GetBounds()
{
	int width = this->BWidth * this->Cols;
	int height = this->BHeight * this->Rows;
	return sf::Rect<float>(this->Pos, sf::Vector2f(width, height));
}

sf::Vector2f Grid::GetSize()
{
	return sf::Vector2f(
		(this->BWidth + 1) * Cols,
		(this->BHeight + 1) * Rows);
}