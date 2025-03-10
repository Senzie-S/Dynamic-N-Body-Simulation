// Copyright 2024 Sanjana Singh
#include "CelestialBody.hpp"
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include "Universe.hpp"

namespace NB {

const double G = 6.67e-11;

CelestialBody::CelestialBody() : px(0), py(0), vx(0), vy(0), mass(0) {}

CelestialBody::CelestialBody(double px, double py, double vx,
double vy, double mass, const std::string& imageFile)
: px(px), py(py), vx(vx), vy(vy), mass(mass), imageFile(imageFile) {
    if (!texture.loadFromFile(imageFile)) {
        throw std::runtime_error("Failed to load image: " + imageFile);
    }
    sprite.setTexture(texture);
}

sf::Vector2f CelestialBody::getPosition() const {
    return sf::Vector2f(static_cast<float>(px), static_cast<float>(py));
}

sf::Vector2f CelestialBody::getVelocity() const {
    return sf::Vector2f(static_cast<float>(vx), static_cast<float>(vy));
}

double CelestialBody::getMass() const {
    return mass;
}

void CelestialBody::updatePosition(double dt) {
    px += vx * dt;
    py += vy * dt;
}

void CelestialBody::updateVelocity(double ax, double ay, double dt) {
    vx += ax * dt;
    vy += ay * dt;
}


void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vector2u windowSize = target.getSize();
    double universeRadius = Universe::getRadius();
    double scale = windowSize.x / (2.5 * universeRadius);
    float windowX = static_cast<float>((px * scale) + (windowSize.x / 2.0f));
    float windowY = static_cast<float>((windowSize.y / 2.0f) - (py * scale));

    sprite.setPosition(windowX, windowY);
    float baseSize = 8.0f;
    float spriteScale = static_cast<float>(baseSize * (std::log10(mass / 1e20) + 1));

    spriteScale = std::max(4.0f, std::min(spriteScale, 20.0f));

    sprite.setScale(spriteScale / sprite.getTexture()->getSize().x,
                    spriteScale / sprite.getTexture()->getSize().y);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

    target.draw(sprite, states);
}

std::istream& operator>>(std::istream& is, CelestialBody& body) {
    is >> body.px >> body.py >> body.vx >> body.vy >> body.mass >> body.imageFile;
    if (!body.texture.loadFromFile(body.imageFile)) {
        throw std::runtime_error("Failed to load image: " + body.imageFile);
    }
    body.sprite.setTexture(body.texture);
    return is;
}

std::ostream& operator<<(std::ostream& os, const CelestialBody& body) {
    os << std::scientific << std::setprecision(4)
       << body.px << " " << body.py << " " << body.vx << " "
       << body.vy << " " << body.mass << " " << body.imageFile;
    return os;
}

}  // namespace NB
