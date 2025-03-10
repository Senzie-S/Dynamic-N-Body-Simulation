// Copyright 2024 Sanjana Singh
#include "Universe.hpp"
#include <fstream>
#include <cmath>

namespace NB {

double Universe::universeRadius = 0.0;

Universe::Universe() {}

Universe::Universe(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> *this;
    }
}

size_t Universe::size() const {
    return celestialBodies.size();
}

double Universe::getRadius() {
    return universeRadius;
}

std::shared_ptr<CelestialBody> Universe::operator[](size_t index) {
    return celestialBodies[index];
}

const std::shared_ptr<CelestialBody> Universe::operator[](size_t index) const {
    return celestialBodies[index];
}

void Universe::step(double dt) {
    std::vector<double> fx(celestialBodies.size(), 0.0);
    std::vector<double> fy(celestialBodies.size(), 0.0);

    // Calculate forces
    for (size_t i = 0; i < celestialBodies.size(); ++i) {
        for (size_t j = i + 1; j < celestialBodies.size(); ++j) {
            double dx = celestialBodies[j]->getPosition().x - celestialBodies[i]->getPosition().x;
            double dy = celestialBodies[j]->getPosition().y - celestialBodies[i]->getPosition().y;
            double distance = std::sqrt(dx * dx + dy * dy);
            double force = (G * celestialBodies[i]->getMass() *
             celestialBodies[j]->getMass()) / (distance * distance);

            double fx_ij = force * dx / distance;
            double fy_ij = force * dy / distance;

            fx[i] += fx_ij;
            fy[i] += fy_ij;
            fx[j] -= fx_ij;
            fy[j] -= fy_ij;
        }
    }

    // Update velocities and positions
    for (size_t i = 0; i < celestialBodies.size(); ++i) {
        double ax = fx[i] / celestialBodies[i]->getMass();
        double ay = fy[i] / celestialBodies[i]->getMass();
        celestialBodies[i]->updateVelocity(ax, ay, dt);
        celestialBodies[i]->updatePosition(dt);
    }
}

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& body : celestialBodies) {
        target.draw(*body, states);
    }
}

std::istream& operator>>(std::istream& is, Universe& universe) {
    size_t numBodies;
    is >> numBodies >> Universe::universeRadius;

    universe.celestialBodies.clear();
    for (size_t i = 0; i < numBodies; ++i) {
        auto body = std::make_shared<CelestialBody>();
        is >> *body;
        universe.celestialBodies.push_back(body);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Universe& universe) {
    os << universe.celestialBodies.size() << "\n";
    os << Universe::universeRadius << "\n";
    for (const auto& body : universe.celestialBodies) {
        os << *body << "\n";
    }
    return os;
}

}  // namespace NB
