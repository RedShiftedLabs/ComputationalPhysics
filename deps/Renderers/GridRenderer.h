#pragma once

#include <SFML/Graphics.hpp>

class GridRenderer {
public:
  void renderGrid(sf::RenderWindow &window) {
    sf::Vector2f size = static_cast<sf::Vector2f>(window.getSize());

    if (needsUpdate || size != lastSize) {
      buildGrid(size);
      lastSize = size;
      needsUpdate = false;
    }

    window.draw(secondaryLines);
    window.draw(primaryLines);
  }

  void invalidate() { needsUpdate = true; }

private:
  sf::VertexArray primaryLines;
  sf::VertexArray secondaryLines;
  sf::Vector2f lastSize{0, 0};
  bool needsUpdate = true;

  const float primaryStep = 100.0F;
  const float secondaryStep = 20.0F; // primaryStep / 5
  const sf::Color primaryColor{100, 100, 100, 255};
  const sf::Color secondaryColor{60, 60, 60, 255};

  void buildGrid(sf::Vector2f size) {
    primaryLines.clear();
    secondaryLines.clear();
    primaryLines.setPrimitiveType(sf::PrimitiveType::Lines);
    secondaryLines.setPrimitiveType(sf::PrimitiveType::Lines);

    // Pre-calculate counts and reserve space
    int primaryX = static_cast<int>(size.x / primaryStep) + 1;
    int primaryY = static_cast<int>(size.y / primaryStep) + 1;
    int secondaryX = static_cast<int>(size.x / secondaryStep);
    int secondaryY = static_cast<int>(size.y / secondaryStep);

    primaryLines.resize((primaryX + primaryY) * 2);
    secondaryLines.resize((secondaryX + secondaryY) * 2);

    size_t primaryIndex = 0;
    size_t secondaryIndex = 0;

    // Primary vertical lines
    for (int i = 0; i <= primaryX; ++i) {
      float x = i * primaryStep;
      if (x <= size.x) {
        primaryLines[primaryIndex++] = {{x, 0}, primaryColor};
        primaryLines[primaryIndex++] = {{x, size.y}, primaryColor};
      }
    }

    // Primary horizontal lines
    for (int i = 0; i <= primaryY; ++i) {
      float y = i * primaryStep;
      if (y <= size.y) {
        primaryLines[primaryIndex++] = {{0, y}, primaryColor};
        primaryLines[primaryIndex++] = {{size.x, y}, primaryColor};
      }
    }

    // Secondary vertical lines (skip multiples of 5)
    for (int i = 1; i < secondaryX; ++i) {
      if (i % 5 != 0) {
        float x = i * secondaryStep;
        secondaryLines[secondaryIndex++] = {{x, 0}, secondaryColor};
        secondaryLines[secondaryIndex++] = {{x, size.y}, secondaryColor};
      }
    }

    // Secondary horizontal lines (skip multiples of 5)
    for (int i = 1; i < secondaryY; ++i) {
      if (i % 5 != 0) {
        float y = i * secondaryStep;
        secondaryLines[secondaryIndex++] = {{0, y}, secondaryColor};
        secondaryLines[secondaryIndex++] = {{size.x, y}, secondaryColor};
      }
    }

    // Resize to actual used size
    primaryLines.resize(primaryIndex);
    secondaryLines.resize(secondaryIndex);
  }
};