#include "Button.h"

Button::Button(const std::string& buttonText, const sf::Vector2f& position) {

    isActive = false;

    //font.loadFromFile("C:/Users/Razvan/Desktop/Coding Projects/Fonts/ARIALUNI.TTF");
    font.loadFromFile("C:/Users/Razvan/Desktop/Coding Projects/Fonts/coolvetica.ttf");
    label.setFont(font);
    label.setOutlineColor(sf::Color::Black);
    label.setOutlineThickness(2);
    label.setString(buttonText);
    label.setCharacterSize(20);

    float button_width = label.getLocalBounds().width + 20;
    float button_height = label.getLocalBounds().height + 30;



    label.setFillColor(sf::Color::White);
    label.setPosition(position.x + 8, position.y + 10);

    //shape.setSize(sf::Vector2f(150.f, 50.f));
    shape.setSize(sf::Vector2f(button_width, button_height));
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Black);

}

bool Button::isClicked(const sf::Vector2i& mousePos) {
    return shape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

void Button::ChangeColor(sf::Color color)
{
    shape.setFillColor(color);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(label);
}

void Button::SetStatus(bool activeStatus)
{
    isActive = activeStatus;
}

int Button::GetActiveStatus()
{
    return isActive;
}