// src/chapter1/DataVisualizer.cpp

#include <GridRenderer.h>
#include <SFML/Graphics.hpp>
#include <Vector2D.h>
#include <optional>

#include <DataLoader.h>

int main() {
  DataLoader loader("Circle.dat");
  const auto &timeData = loader.getColumn("Time(s)");
  const auto &xData = loader.getColumn("x(t)");
  const auto &yData = loader.getColumn("y(t)");

  sf::RenderWindow window(sf::VideoMode({800U, 600U}), "Data Visualizer");
  window.setFramerateLimit(60);

  sf::View view;
  view.setSize({800.0F, 600.0F});
  view.setCenter({0.0F, 0.0F});
  window.setView(view);

  GridRenderer gridRenderer;
  sf::VertexArray trail(sf::PrimitiveType::LineStrip);
  sf::CircleShape marker(4.F);
  marker.setOrigin({4.0F, 4.0F});
  marker.setFillColor(sf::Color::Red);

  sf::Clock clock;
  float scale = 70.0F;
  float totalTime = timeData.back() - timeData.front();

  while (window.isOpen()) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    float elapsed = clock.getElapsedTime().asSeconds();
    float currentTime = timeData[0] + fmod(elapsed, totalTime);

    size_t currentIndex = 0;
    for (size_t i = 0; i < timeData.size() - 1; ++i) {
      if (timeData[i] <= currentTime && currentTime < timeData[i + 1]) {
        currentIndex = i;
        break;
      }
    }

    if (elapsed > 0 &&
        fmod(elapsed, totalTime) <
            clock.getElapsedTime().asSeconds() - elapsed + 0.1F) {
      trail.clear();
    }

    trail.append({{xData[currentIndex] * scale, yData[currentIndex] * scale},
                  sf::Color{255, 255, 255, 128}});

    marker.setPosition(
        {xData[currentIndex] * scale, yData[currentIndex] * scale});

    window.clear(sf::Color{20, 20, 20, 255});
    gridRenderer.renderGrid(window);
    window.draw(trail);
    window.draw(marker);
    window.display();
  }

  return 0;
}