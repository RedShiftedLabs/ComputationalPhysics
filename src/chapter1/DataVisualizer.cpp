// src/chapter1/DataVisualizer.cpp

#include <DataLoader.h>
#include <GridRenderer.h>
#include <SFML/Graphics.hpp>
#include <Vector2D.h>
#include <algorithm>
#include <cmath>
#include <optional>
#include <vector>

float lerp(float a, float b, float t) { return a + (t * (b - a)); }

int main() {
  DataLoader loader("Lissajous.dat");
  const auto &timeData = loader.getColumn("Time(s)");
  const auto &xData = loader.getColumn("x(t)");
  const auto &yData = loader.getColumn("y(t)");

  if (timeData.empty()) {
    return 1;
  }

  sf::RenderWindow window(sf::VideoMode({800U, 600U}), "Data Visualizer");
  window.setFramerateLimit(60);

  sf::View view;
  view.setCenter({0.0F, 0.0F});
  view.setSize({800.0F, -600.0F});
  window.setView(view);

  GridRenderer gridRenderer;
  sf::VertexArray trail(sf::PrimitiveType::LineStrip);
  sf::CircleShape marker(4.0F);
  marker.setOrigin({4.0F, 4.0F});
  marker.setFillColor(sf::Color::Red);

  sf::Clock clock;
  const float scale = 120.0F;
  const float totalTime = timeData.back() - timeData.front();
  size_t currentIndex = 0;

  while (window.isOpen()) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    // --- TIME CALCULATION ---
    float elapsed = clock.getElapsedTime().asSeconds();
    float currentTime = timeData[0] + fmod(elapsed, totalTime);

    size_t previousIndex = currentIndex;

    // Binary search (std::upper_bound) to find the current time interval
    auto it = std::upper_bound(timeData.begin(), timeData.end(), currentTime);
    currentIndex = std::distance(timeData.begin(), it);
    if (currentIndex > 0) {
      currentIndex--;
    }

    if (currentIndex < previousIndex) {
      trail.clear();
    }

    // INTERPOLATION
    const size_t nextIndex = std::min(currentIndex + 1, timeData.size() - 1);
    const float time1 = timeData[currentIndex];
    const float time2 = timeData[nextIndex];

    // Calculate interpolation factor 't' (0.0 to 1.0)
    float t = 0.0F;
    if (time2 > time1) {
      t = (currentTime - time1) / (time2 - time1);
    }

    // Interpolate position for smooth animation
    const float interpolatedX = lerp(xData[currentIndex], xData[nextIndex], t);
    const float interpolatedY = lerp(yData[currentIndex], yData[nextIndex], t);

    // UPDATE GRAPHICS
    trail.append({{interpolatedX * scale, interpolatedY * scale},
                  sf::Color(255, 255, 255, 128)});
    marker.setPosition({interpolatedX * scale, interpolatedY * scale});

    // RENDERING
    window.clear(sf::Color{33, 33, 33, 105});
    gridRenderer.renderGrid(window);
    window.draw(trail);
    window.draw(marker);
    window.display();
  }

  return 0;
}