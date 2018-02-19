#ifndef BUTTON_DEFINE
#define BUTTON_DEFINE

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

class Button : public sf::Drawable
{
  public:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
    void setTexture(sf::Texture *t);
    sf::Texture getTexture();
    sf::RectangleShape &getInternalRectangle();
    void setSize(sf::Vector2f size);
    sf::Rect<float> getSize();
    Button();
    Button(Button &other);
    Button(sf::Rect<int> size);
    Button(sf::Vector2f size);
    Button(sf::Vector2f size, sf::Vector2f position, sf::Texture *Texture);
    Button(sf::RectangleShape Rect);
    bool isTouched(sf::Event::TouchEvent e);
    
    sf::Text optionalText; //Will need to be managed directly, button class won't provide an interface
                           //Position will be an offset from the Button position
    void setTextPosition(sf::Vector2f pos);
    sf::Vector2f getTextPosition();

  private:
    sf::RectangleShape m_Internal;
    sf::Texture *m_Texture;
};

#endif //BUTTON_DEFINE