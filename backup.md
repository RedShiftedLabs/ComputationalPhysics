```cpp
// src/chapter1/DataVisualizer.cpp

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

struct PathData {
  std::vector<sf::Vector2f> points;
};

bool loadPathFromFile(const std::string &filename, PathData &data) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
    return false;
  }
  std::string header;
  std::getline(file, header);
  float t;
  float x;
  float y;
  float vx;
  float vy;
  while (file >> t >> x >> y >> vx >> vy) {
    float screenX = (x * 200.F) + 400.F;
    float screenY = (-y * 200.F) + 300.F;
    data.points.push_back({screenX, screenY});
  }
  std::cout << "Loaded " << data.points.size() << " points from " << filename
            << std::endl;
  return true;
}

int main() {
  std::string dataFilename = "Circle.dat";

  PathData path;
  if (!loadPathFromFile(dataFilename, path) || path.points.empty()) {
    return 1;
  }

  sf::RenderWindow window(sf::VideoMode({800U, 600U}), "Data Visualizer");
  window.setFramerateLimit(60);

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

    if (currentPointIndex < path.points.size()) {
      const auto &point = path.points[currentPointIndex];

      trail.append({point, sf::Color{255, 255, 255, 255}});

      marker.setPosition(point);
      currentPointIndex++;
    }

    window.clear(sf::Color{25, 25, 25, 255});
    window.draw(trail);
    if (currentPointIndex > 0) {
      window.draw(marker);
    }
    window.display();
  }

  return 0;
}

void renderGrid(sf::RenderWindow &window) {
  sf::VertexArray primaryLines(sf::PrimitiveType::Lines);
  sf::VertexArray secondaryLines(sf::PrimitiveType::Lines);

  sf::Vector2f size = static_cast<sf::Vector2f>(window.getSize());

  sf::Color primaryGridColor{100, 100, 100, 255};
  sf::Color secondaryGridColor{60, 60, 60, 255};

  float primaryStep = 100.0F;
  float secondaryStep = primaryStep / 5.0F;

  auto addLine = [](sf::VertexArray &lines, float x1, float y1, float x2,
                    float y2, sf::Color color) {
    lines.append({{x1, y1}, color});
    lines.append({{x2, y2}, color});
  };

  // Main Grid
  for (float x = 0; x <= size.x; x += primaryStep) {
    addLine(primaryLines, x, 0.0F, x, size.y, primaryGridColor);
  }
  for (float y = 0; y <= size.y; y += primaryStep) {
    addLine(primaryLines, 0.0F, y, size.x, y, primaryGridColor);
  }

  //   Secondary Grid
  for (float x = secondaryStep; x <= size.x; x += secondaryStep) {
    if (i % 5 != 0) {
      addLine(secondaryLines, x, 0.0F, x, size.y, secondaryGridColor);
    }
  }
  for (float y = secondaryStep; y <= size.y; y += secondaryStep) {
    if (i % 5 != 0) {
      addLine(secondaryLines, 0.0F, y, size.x, y, secondaryGridColor);
    }
  }

  window.draw(secondaryLines);
  window.draw(primaryLines);
}
```