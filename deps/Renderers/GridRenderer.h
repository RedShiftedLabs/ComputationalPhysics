#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>

class GridRenderer {
public:
  void renderGrid(sf::RenderWindow &window) {
    sf::View currentView = window.getView();
    sf::Vector2f viewSize = currentView.getSize();
    sf::Vector2f viewCenter = currentView.getCenter();

    if (needsUpdate || viewSize != lastViewSize ||
        viewCenter != lastViewCenter) {
      buildGrid(currentView);
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
  const int primaryLineFactor = 5;

  const sf::Color primaryColor{100, 100, 100, 205};
  const sf::Color secondaryColor{60, 60, 60, 155};
  const sf::Color xAxisColor{118, 178, 23, 215};
  const sf::Color yAxisColor{205, 56, 79, 215};

  void buildGrid(const sf::View &view) {
    primaryLines.clear();
    secondaryLines.clear();
    axisLines.clear();
    primaryLines.setPrimitiveType(sf::PrimitiveType::Lines);
    secondaryLines.setPrimitiveType(sf::PrimitiveType::Lines);
    axisLines.setPrimitiveType(sf::PrimitiveType::Lines);

    const sf::Vector2f viewSize = view.getSize();
    const sf::Vector2f viewCenter = view.getCenter();

    float left = viewCenter.x - (viewSize.x / 2.0F);
    float right = viewCenter.x + (viewSize.x / 2.0F);
    float top = viewCenter.y - (viewSize.y / 2.0F);
    float bottom = viewCenter.y + (viewSize.y / 2.0F);

    if (top > bottom) {
      std::swap(top, bottom);
    }

    int startX = static_cast<int>(std::floor(left / secondaryStep));
    int endX = static_cast<int>(std::ceil(right / secondaryStep));
    int startY = static_cast<int>(std::floor(top / secondaryStep));
    int endY = static_cast<int>(std::ceil(bottom / secondaryStep));

    for (int i = startX; i <= endX; ++i) {
      float x = static_cast<float>(i) * secondaryStep;
      sf::Vertex topVertex({x, top}, secondaryColor);
      sf::Vertex bottomVertex({x, bottom}, secondaryColor);

      if (i == 0) { // Y-axis
        topVertex.color = yAxisColor;
        bottomVertex.color = yAxisColor;
        axisLines.append(topVertex);
        axisLines.append(bottomVertex);
      } else if (i % primaryLineFactor == 0) { // Primary line
        topVertex.color = primaryColor;
        bottomVertex.color = primaryColor;
        primaryLines.append(topVertex);
        primaryLines.append(bottomVertex);
      } else { // Secondary line
        secondaryLines.append(topVertex);
        secondaryLines.append(bottomVertex);
      }
    }

    for (int i = startY; i <= endY; ++i) {
      float y = static_cast<float>(i) * secondaryStep;
      sf::Vertex leftVertex({left, y}, secondaryColor);
      sf::Vertex rightVertex({right, y}, secondaryColor);

      if (i == 0) { // X-axis
        leftVertex.color = xAxisColor;
        rightVertex.color = xAxisColor;
        axisLines.append(leftVertex);
        axisLines.append(rightVertex);
      } else if (i % primaryLineFactor == 0) { // Primary line
        leftVertex.color = primaryColor;
        rightVertex.color = primaryColor;
        primaryLines.append(leftVertex);
        primaryLines.append(rightVertex);
      } else { // Secondary line
        secondaryLines.append(leftVertex);
        secondaryLines.append(rightVertex);
      }
    }
  }
};