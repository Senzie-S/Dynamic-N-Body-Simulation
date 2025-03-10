// Copyright 2024 Sanjana Singh
#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

namespace NB {

class CelestialBody : public sf::Drawable {
 public:
    CelestialBody();
    CelestialBody(double px, double py, double vx,
     double vy, double mass, const std::string& imageFile);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    double getMass() const;
    bool isSun() const;

    void updatePosition(double dt);
    void updateVelocity(double ax, double ay, double dt);

    friend std::istream& operator>>(std::istream& is, CelestialBody& body);
    friend std::ostream& operator<<(std::ostream& os, const CelestialBody& body);

 private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    double px, py;
    double vx, vy;
    double mass;
    std::string imageFile;
    sf::Texture texture;
    mutable sf::Sprite sprite;
};

std::istream& operator>>(std::istream& is, CelestialBody& body);
std::ostream& operator<<(std::ostream& os, const CelestialBody& body);

}  // namespace NB
