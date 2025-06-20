#include <DataLoader.h>
#include <GridRenderer.h>
#include <SFML/Graphics.hpp>
#include <Vector2D.h>
#include <algorithm>
#include <cmath>
#include <optional>
#include <vector>

inline float lerp(float a, float b, float t) {
  t = std::clamp(t, 0.0F, 1.0F);
  return a + (t * (b - a));
}

void updateViewOnResize(sf::RenderWindow &window, sf::View &view) {
  sf::Vector2u size = window.getSize();
  float aspectRatio = static_cast<float>(size.x) / static_cast<float>(size.y);
  view.setSize({600.0F * aspectRatio, -600.0F});
  view.setCenter({0.0F, 0.0F});
  window.setView(view);
}

int main() {
  DataLoader loader("MiniGolf.dat");
  const std::vector<float> &timeData = loader.getColumn("Time(s)");
  const std::vector<float> &xData = loader.getColumn("x(t)");
  const std::vector<float> &yData = loader.getColumn("y(t)");

  if (timeData.empty()) {
    return 1;
  }

  sf::RenderWindow window(sf::VideoMode({800U, 600U}), "Data Visualizer");
  window.setFramerateLimit(60);

  sf::View view;
  updateViewOnResize(window, view);

  GridRenderer gridRenderer;
  sf::VertexArray trail(sf::PrimitiveType::LineStrip);
  sf::CircleShape marker(4.0F);
  marker.setOrigin({4.0F, 4.0F});
  marker.setFillColor(sf::Color::Red);

  sf::Clock clock;
  const float simulationScale = 35.0F;
  const float totalTime = timeData.back() - timeData.front();
  size_t currentIndex = 0;

  while (window.isOpen()) {
    // Handle events
    while (const std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if (event->is<sf::Event::Resized>()) {
        updateViewOnResize(window, view);
        trail.clear();
      }
    }

    // Calculate current time and position
    float elapsed = clock.getElapsedTime().asSeconds();
    float currentTime = timeData[0] + fmod(elapsed, totalTime);

    // Find data index using binary search
    std::__wrap_iter<const float *> it =
        std::upper_bound(timeData.begin(), timeData.end(), currentTime);
    size_t newIndex =
        (it == timeData.begin()) ? 0 : std::distance(timeData.begin(), it) - 1;

    if (newIndex < currentIndex) {
      trail.clear();
    }
    currentIndex = newIndex;

    // Interpolate position
    size_t nextIndex = std::min(currentIndex + 1, timeData.size() - 1);
    float t = (timeData[nextIndex] > timeData[currentIndex])
                  ? (currentTime - timeData[currentIndex]) /
                        (timeData[nextIndex] - timeData[currentIndex])
                  : 0.0F;

    float x = lerp(xData[currentIndex], xData[nextIndex], t) * simulationScale;
    float y = lerp(yData[currentIndex], yData[nextIndex], t) * simulationScale;

    // Update graphics
    trail.append({{x, y}, sf::Color(225, 225, 225, 128)});
    marker.setPosition({x, y});

    // Render
    window.clear(sf::Color{33, 33, 33, 105});
    gridRenderer.renderGrid(window);
    window.draw(trail);
    window.draw(marker);
    window.display();
  }

  return 0;
}