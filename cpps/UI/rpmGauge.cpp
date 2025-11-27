//
// Created by Carte on 27/11/2025.
//

#include "../cpps/UI/rpmGauge.h"

#include <iostream>
#include <string>
#include <iostream>

rpmGauge::rpmGauge() {
    m_position = {20.f, 20.f};

    if (!m_font.loadFromFile("../../assets/ARIAL.TTF")) {
        std::cerr << "ERROR: FAILED TO LOAD FONT";

    }

    m_rpmText.setFont(m_font);
    m_rpmText.setCharacterSize(24);
    m_rpmText.setFillColor(sf::Color::Black);
    m_rpmText.setString("RPM: 0");

    //Background
    m_backgroundBar.setSize({200.f, 20.f});
    m_backgroundBar.setFillColor(sf::Color(50, 50, 50));
    m_backgroundBar.setOutlineThickness(2.f);
    m_backgroundBar.setOutlineColor(sf::Color::White);

    //Fill section
    m_barFill.setSize({0.f, 20.f});
    m_barFill.setFillColor(sf::Color::Red);
}

void rpmGauge::update(const Car &car) {
    if (!m_visible) return;

    const CarState& state = car.getState();
    const CarSpec& spec = car.getSpec();

    float rpm = state.rpm;
    float maxRpm = spec.engine.rpmLimit;

    float rpmFraction = (maxRpm > 0.f ? rpm / maxRpm : 0.f);
    if (rpmFraction < 0.f) rpmFraction = 0.f;
    if (rpmFraction > 1.f) rpmFraction = 1.f;

    //Update text for rpm
    m_rpmText.setString("RPM: " + std::to_string((int)rpm));

    //Update rpm bar
    m_barFill.setSize({200.f * rpmFraction, 20.f});

    // Apply updates
    m_rpmText.setPosition(m_position);
    m_backgroundBar.setPosition(m_position.x, m_position.y + 30.f);
    m_barFill.setPosition(m_position.x, m_position.y + 30.f);
}

void rpmGauge::draw(sf::RenderWindow& window) {
    if (!m_visible) return;

    window.draw(m_rpmText);
    window.draw(m_backgroundBar);
    window.draw(m_barFill);
}

void rpmGauge::setPosition(float x, float y) {
    m_position = {x, y};
}

void rpmGauge::setVisible(bool visible) {
    m_visible = visible;
}
