// Copyright 2024 Sanjana Singh
#include <iostream>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include "Universe.hpp"

const double EPSILON = 1e-6;  // For comparing floating-points

bool areValuesClose(double value1, double value2) {
    return std::fabs(value1 - value2) < EPSILON;
}

void testCelestialBodyInputOutput() {
    NB::CelestialBody planet;
    std::stringstream inputStream("1.0 2.0 3.0 4.0 5.0 earth.gif");
    inputStream >> planet;
    std::stringstream outputStream;
    outputStream << planet;
    std::cout << "Actual output: " << outputStream.str() << std::endl;

    double xPosition, yPosition, xVelocity, yVelocity, planetMass;
    std::string imageFile;
    std::stringstream verificationStream(outputStream.str());
    verificationStream >> xPosition >> yPosition >> xVelocity
     >> yVelocity >> planetMass >> imageFile;
     if (!areValuesClose(xPosition, 1.0) || !areValuesClose(yPosition, 2.0) ||
        !areValuesClose(xVelocity, 3.0) || !areValuesClose(yVelocity, 4.0) ||
        !areValuesClose(planetMass, 5.0) || imageFile != "earth.gif") {
        throw std::runtime_error("CelestialBody input/output test failed");
    }
    std::cout << "CelestialBody input/output test passed.\n";
}

void testUniverseInputOutput() {
    NB::Universe solarSystem;
    std::stringstream inputStream(
        "2 100.0\n"
        "1.0 2.0 3.0 4.0 5.0 mars.gif\n"
        "6.0 7.0 8.0 9.0 10.0 mercury.gif");
    inputStream >> solarSystem;
    std::stringstream outputStream;
    outputStream << solarSystem;
    std::cout << "Actual Universe output: " << outputStream.str() << std::endl;

    int planetCount;
    double universeRadius;
    std::stringstream verificationStream(outputStream.str());
    verificationStream >> planetCount >> universeRadius;
     if (planetCount != 2 || !areValuesClose(universeRadius, 100.0)) {
        throw std::runtime_error("Universe header check failed");
    }
    double xPosition, yPosition, xVelocity, yVelocity, planetMass;
    std::string imageFile;

    verificationStream >> xPosition >> yPosition >> xVelocity >>
     yVelocity >> planetMass >> imageFile;
    if (!areValuesClose(xPosition, 1.0) || !areValuesClose(yPosition, 2.0)
     || imageFile != "mars.gif") {
        throw std::runtime_error("First planet check failed");
    }

    verificationStream >> xPosition >> yPosition >> xVelocity >>
     yVelocity >> planetMass >> imageFile;
    if (!areValuesClose(xPosition, 6.0) || !areValuesClose(yPosition, 7.0)
     || imageFile != "mercury.gif") {
        throw std::runtime_error("Second planet check failed");
    }

    std::cout << "Universe input/output test passed.\n";
}

int main() {
    try {
        testCelestialBodyInputOutput();
        testUniverseInputOutput();
        std::cout << "All tests passed.\n";
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
