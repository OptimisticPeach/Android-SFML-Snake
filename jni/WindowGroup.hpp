#ifndef WINDOWGROUP_DEFINE
#define WINDOWGROUP_DEFINE

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class WindowGroup : public sf::Drawable
{
public:
    WindowGroup():Drawable(){}
    void draw(sf::RenderTarget& target, sf::RenderStates states){}
    sf::Color clearColor;
    ~WindowGroup(){}
};


#endif