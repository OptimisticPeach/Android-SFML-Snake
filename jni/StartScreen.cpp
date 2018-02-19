#include "StartScreen.hpp"

void StartScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //target.clear(this->clearColor);
    target.draw(Start_Button, states);
}

StartScreen::StartScreen(sf::RenderWindow& Source) : WindowGroup(), Start_Button_Texture(), texturesLoaded(Start_Button_Texture->loadFromFile("StartBTN200x100.png", sf::IntRect(0, 0, 200, 100)))
{
    this->Start_Button = sf::RectangleShape(sf::Vector2f(200,100));
    this->Start_Button.setPosition(sf::Vector2f((Source.getSize().x - 200) / 2, (Source.getSize().y - 100) / 2));
    this->Start_Button.setOutlineColor(sf::Color::Cyan);
    this->Start_Button.setTexture(Start_Button_Texture);
}
void StartScreen::Update(sf::Event &e)
{
    switch (e.type)
    {
    case sf::Event::TouchBegan:
        if (this->Start_Button.getGlobalBounds().contains(sf::Vector2f(e.touch.x, e.touch.y)) && e.touch.finger == 0)
        {
            this->Start_Button.setOutlineThickness(5.f);
        }
    case sf::Event::TouchMoved:
        if (this->Start_Button.getGlobalBounds().contains(sf::Vector2f(e.touch.x, e.touch.y)) && e.touch.finger == 0)
        {
            this->Start_Button.setOutlineThickness(5.f);
        }
        else
        {
            this->Start_Button.setOutlineThickness(0.f);
        }
    case sf::Event::TouchEnded:
        if (this->Start_Button.getGlobalBounds().contains(sf::Vector2f(e.touch.x, e.touch.y)) && e.touch.finger == 0)
        {
            this->Start_Button.setOutlineThickness(0.f);
            Start_Button_Press();
        }
    }
}

void StartScreen::Start_Button_Press(){

}

StartScreen::~StartScreen(){

}