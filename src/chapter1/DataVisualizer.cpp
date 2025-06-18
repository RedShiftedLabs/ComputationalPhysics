// src/chapter1/DataVisualizer.cpp

#include <GridRenderer.h>
#include <SFML/Graphics.hpp>
#include <Vector2D.h>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

struct CircleData {
  float time;
  std::vector<Vector2Df> positions;
  std::vector<Vector2Df> velocity;
};

template <typename T, typename Parser>
bool loadDataFromFile(const std::string &filename, T &dataContainer,
                      Parser parseLine) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
    return false;
  }

  std::string line;
  std::getline(file, line);

  while (std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }

    parseLine(line, dataContainer);
  }

  return true;
}

int main() {
  std::string dataFilename = "Circle.dat";

  CircleData circleData;
  auto circleParser = [](const std::string &line, CircleData &data) {
    std::stringstream ss(line);
    float t;
    float x;
    float y;
    float vx;
    float vy;
    if (ss >> t >> x >> y >> vx >> vy) {
      data.positions.push_back({x, y});
      data.velocity.push_back({vx, vy});
    }
  };

  if (loadDataFromFile("Circle.dat", circleData, circleParser)) {
    std::cout << "Successfully loaded " << circleData.positions.size()
              << " points into CircleData.\n";
  }

  sf::RenderWindow window(sf::VideoMode({800U, 600U}), "Data Visualizer");
  window.setFramerateLimit(60);

  GridRenderer gridRenderer;

  sf::VertexArray trail(sf::PrimitiveType::LineStrip);
  sf::CircleShape marker(4.F);
  marker.setOrigin({4.0F, 4.0F});
  marker.setFillColor(sf::Color::Red);

  size_t currentPointIndex = 0;

  while (window.isOpen()) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    if (currentPointIndex < circleData.positions.size()) {
      const auto &point = circleData.positions[currentPointIndex];

      trail.append({{point.x, point.y}, sf::Color{255, 255, 255, 255}});

      marker.setPosition({point.x, point.y});
      currentPointIndex++;
    }

    window.clear(sf::Color{20, 20, 20, 255});
    gridRenderer.renderGrid(window);
    window.draw(trail);
    if (currentPointIndex > 0) {
      window.draw(marker);
    }

    window.display();
  }

  return 0;
}