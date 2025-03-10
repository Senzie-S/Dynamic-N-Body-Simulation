// Copyright 2024 Sanjana Singh
#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {

class Universe : public sf::Drawable {
 public:
    Universe();
    explicit Universe(const std::string& filename);

    size_t size() const;
    static double getRadius();
    std::shared_ptr<CelestialBody> operator[](size_t index);
    const std::shared_ptr<CelestialBody> operator[](size_t index) const;

    void step(double dt);

    friend std::istream& operator>>(std::istream& is, Universe& universe);
    friend std::ostream& operator<<(std::ostream& os, const Universe& universe);

 private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::vector<std::shared_ptr<CelestialBody>> celestialBodies;
    static double universeRadius;
    const double G = 6.67e-11;
};

}  // namespace NB
