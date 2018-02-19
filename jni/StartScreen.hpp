#ifndef START_SCREEN_DEFINE
#define START_SCREEN_DEFINE

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "WindowGroup.hpp"

class StartScreen : public WindowGroup
{
  public:
    StartScreen(sf::RenderWindow& Source);
    void draw(sf::RenderTarget& target, sf::RenderStates states)const;
    void Update(sf::Event& e);
    virtual ~StartScreen();
  private:
    bool texturesLoaded;
    sf::Texture* Start_Button_Texture;
    sf::RectangleShape Start_Button;
    void Start_Button_Press();
};

#endif