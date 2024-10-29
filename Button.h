#pragma once
#include<iostream>
#include "ButtonType.h"
#include "SFML/Graphics.hpp"
#include<string>
class Button {
    
    sf::Text label;
    sf::RectangleShape shape;
    sf::Font font;
    bool isActive;

public:    

    Button(const std::string& buttonText, const sf::Vector2f& position);
   
    bool isClicked(const sf::Vector2i& mousePos);

    void ChangeColor(sf::Color color);

    void draw(sf::RenderWindow& window);

    void SetStatus(bool activeStatus);

    int GetActiveStatus();
};

