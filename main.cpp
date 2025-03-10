// Copyright 2024 Sanjana Singh
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Universe.hpp"

std::string formatTime(double seconds) {
    seconds = fmod(seconds, 31557600.0);
    int days = static_cast<int>(seconds / 86400.0);
    seconds = fmod(seconds, 86400.0);
    int hours = static_cast<int>(seconds / 3600);
    int minutes = (static_cast<int>(seconds) % 3600) / 60;
    int secs = static_cast<int>(seconds) % 60;
    std::ostringstream oss;
    oss << days << " days, "
        << std::setfill('0') << std::setw(2) << hours << ":"
        << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << secs;
    return oss.str();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " T dt" << std::endl;
        return 1;
    }

    double T = std::stod(argv[1]);
    double dt = std::stod(argv[2]);

    NB::Universe universe;
    std::cin >> universe;

    sf::RenderWindow window(sf::VideoMode(600, 600), "The Solar System");
    window.setFramerateLimit(60);

    sf::Texture bg_texture;
    if (!bg_texture.loadFromFile("background.png")) {
        std::cerr << "Failed to load background image" << std::endl;
        return EXIT_FAILURE;
    }
    sf::Sprite background(bg_texture);

    float scaleX = static_cast<float>(window.getSize().x) / bg_texture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / bg_texture.getSize().y;
    float scale = std::max(scaleX, scaleY);

    background.setScale(scale, scale);
     background.setPosition(
        (window.getSize().x - bg_texture.getSize().x * scale) / 2.f,
        (window.getSize().y - bg_texture.getSize().y * scale) / 2.f);

    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(10, 10);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("sound.wav")) {
        std::cerr << "Failed to load sound file" << std::endl;
        return EXIT_FAILURE;
    }
    sf::Sound universe_sound;
    universe_sound.setBuffer(buffer);
    universe_sound.play();
    universe_sound.setLoop(true);

    double elapsedTime = 0.0;
    const double ONE_YEAR = 31557600.0;

    while (window.isOpen() && elapsedTime < std::min(T, ONE_YEAR)) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                universe_sound.stop();
                window.close();
            }
        }

        double stepTime = std::min(dt, ONE_YEAR - elapsedTime);
        universe.step(stepTime);
        elapsedTime += stepTime;

        window.clear();
        window.draw(background);
        window.draw(universe);

        std::ostringstream oss;
        oss << "Elapsed Time: " << formatTime(elapsedTime);
        timeText.setString(oss.str());
        window.draw(timeText);

        window.display();
    }

    universe_sound.stop();

    std::cout << universe.size() << std::endl;
    std::cout << std::scientific << std::setprecision(4) << NB::Universe::getRadius() << std::endl;
    std::cout << universe;

    return 0;
}
