#pragma once

#include <SFML/Graphics.hpp>

class GridRenderer {
public:
  void renderGrid(sf::RenderWindow &window) {
    sf::View currentView = window.getView();
    sf::Vector2f viewSize = currentView.getSize();
    sf::Vector2f viewCenter = currentView.getCenter();

    if (needsUpdate || viewSize != lastViewSize ||
        viewCenter != lastViewCenter) {
      buildGrid(viewSize, viewCenter);
      lastViewSize = viewSize;
      lastViewCenter = viewCenter;
      needsUpdate = false;
    }

    window.draw(secondaryLines);
    window.draw(primaryLines);
    window.draw(axisLines);
  }

  void invalidate() { needsUpdate = true; }

private:
  sf::VertexArray primaryLines;
  sf::VertexArray secondaryLines;
  sf::VertexArray axisLines;
  sf::Vector2f lastViewSize{0, 0};
  sf::Vector2f lastViewCenter{0, 0};
  bool needsUpdate = true;

  const float primaryStep = 100.0F;
  const float secondaryStep = 20.0F;
  const sf::Color primaryColor{100, 100, 100, 205};
  const sf::Color secondaryColor{60, 60, 60, 155};
  const sf::Color xAxisColor{118, 178, 23, 215};
  const sf::Color yAxisColor{205, 56, 79, 215};

  void buildGrid(sf::Vector2f viewSize, sf::Vector2f viewCenter) {
    primaryLines.clear();
    secondaryLines.clear();
    axisLines.clear();
    primaryLines.setPrimitiveType(sf::PrimitiveType::Lines);
    secondaryLines.setPrimitiveType(sf::PrimitiveType::Lines);
    axisLines.setPrimitiveType(sf::PrimitiveType::Lines);

    // Calculate the visible world bounds
    float left = viewCenter.x - (viewSize.x / 2.0F);
    float right = viewCenter.x + (viewSize.x / 2.0F);
    float top = viewCenter.y - (viewSize.y / 2.0F);
    float bottom = viewCenter.y + (viewSize.y / 2.0F);

    // Find the range of grid lines to draw
    int startX = static_cast<int>(std::floor(left / primaryStep));
    int endX = static_cast<int>(std::ceil(right / primaryStep));
    int startY = static_cast<int>(std::floor(top / primaryStep));
    int endY = static_cast<int>(std::ceil(bottom / primaryStep));

    int secondaryStartX = static_cast<int>(std::floor(left / secondaryStep));
    int secondaryEndX = static_cast<int>(std::ceil(right / secondaryStep));
    int secondaryStartY = static_cast<int>(std::floor(top / secondaryStep));
    int secondaryEndY = static_cast<int>(std::ceil(right / secondaryStep));

    // Draw primary grid lines (vertical)
    for (int i = startX; i <= endX; ++i) {
      float x = i * primaryStep;
      if (x != 0.0F) { // Don't draw the main axis here
        primaryLines.append({{x, top}, primaryColor});
        primaryLines.append({{x, bottom}, primaryColor});
      }
    }

    // Draw primary grid lines (horizontal)
    for (int i = startY; i <= endY; ++i) {
      float y = i * primaryStep;
      if (y != 0.0F) { // Don't draw the main axis here
        primaryLines.append({{left, y}, primaryColor});
        primaryLines.append({{right, y}, primaryColor});
      }
    }

    // Draw secondary grid lines (vertical)
    for (int i = secondaryStartX; i <= secondaryEndX; ++i) {
      if (i % 5 != 0) { // Skip lines that coincide with primary lines
        float x = i * secondaryStep;
        if (x != 0.0F) { // Don't draw over the main axis
          secondaryLines.append({{x, top}, secondaryColor});
          secondaryLines.append({{x, bottom}, secondaryColor});
        }
      }
    }

    // Draw secondary grid lines (horizontal)
    for (int i = secondaryStartY; i <= secondaryEndY; ++i) {
      if (i % 5 != 0) { // Skip lines that coincide with primary lines
        float y = i * secondaryStep;
        if (y != 0.0F) { // Don't draw over the main axis
          secondaryLines.append({{left, y}, secondaryColor});
          secondaryLines.append({{right, y}, secondaryColor});
        }
      }
    }

    // Draw main axes (X and Y axes through origin)
    // X-axis (horizontal line through y=0)
    if (top <= 0.0F && bottom >= 0.0F) {
      axisLines.append({{left, 0.0F}, xAxisColor});
      axisLines.append({{right, 0.0F}, xAxisColor});
    }

    // Y-axis (vertical line through x=0)
    if (left <= 0.0F && right >= 0.0F) {
      axisLines.append({{0.0F, top}, yAxisColor});
      axisLines.append({{0.0F, bottom}, yAxisColor});
    }
  }
};