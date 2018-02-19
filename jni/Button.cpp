#include "Button.hpp"

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_Internal, states);
   
    // optionalText.move(m_Internal.getPosition());
    target.draw(optionalText, states);
}

void Button::setPosition(sf::Vector2f pos)
{
    sf::Vector2f offset = optionalText.getPosition() - m_Internal.getPosition();
    m_Internal.setPosition(pos);
    optionalText.setPosition(pos + offset);
}

sf::Vector2f Button::getPosition()
{
    return m_Internal.getPosition();
}

void Button::setTexture(sf::Texture *t)
{
    m_Texture = t;
    m_Internal.setTexture(m_Texture);
}

sf::Texture Button::getTexture()
{
    return *(m_Texture);
}

sf::RectangleShape &Button::getInternalRectangle()
{
    return m_Internal;
}

Button::Button()
{
}

Button::Button(Button &other)
{
    this->m_Internal = other.m_Internal;
    this->m_Texture = other.m_Texture;
}

Button::Button(sf::Vector2f position)
{
    m_Internal.setPosition(position);
}

Button::Button(sf::Rect<int> size)
{
    m_Internal = sf::RectangleShape(sf::Vector2f(size.width, size.height));
    m_Internal.setPosition(size.left, size.top);
}

Button::Button(sf::Vector2f size, sf::Vector2f position, sf::Texture *Texture)
{
    m_Internal = sf::RectangleShape(size);
    m_Internal.setPosition(position);
    m_Texture = Texture;
    m_Internal.setTexture(m_Texture);
}

Button::Button(sf::RectangleShape Rect)
{
    m_Internal = Rect;
    m_Texture = (sf::Texture *)Rect.getTexture();
    m_Internal.setTexture(m_Texture);
}

bool Button::isTouched(sf::Event::TouchEvent e)
{
    return m_Internal.getGlobalBounds().contains(sf::Vector2f(e.x, e.y));
}

void Button::setSize(sf::Vector2f size)
{
    m_Internal.setSize(size);
}

sf::FloatRect Button::getSize()
{
    return m_Internal.getGlobalBounds();
}

void Button::setTextPosition(sf::Vector2f pos)
{
    optionalText.setPosition(m_Internal.getPosition() + pos);
}

sf::Vector2f Button::getTextPosition()
{
    return optionalText.getPosition();
}