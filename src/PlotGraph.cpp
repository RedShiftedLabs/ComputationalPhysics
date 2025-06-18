// src/PlotGraph.cpp

#include <DataLoader.h>
#include <GridRenderer.h>
#include <LineRenderer.h>
#include <SFML/Graphics.hpp>
#include <Vector2D.h>
#include <optional>

void updateViewOnResize(sf::RenderWindow &window, sf::View &view) {
  sf::Vector2u size = window.getSize();
  float aspectRatio = static_cast<float>(size.x) / static_cast<float>(size.y);
  view.setSize({600.0F * aspectRatio, -600.0F});
  view.setCenter({0.0F, 0.0F});
  window.setView(view);
}

void handleEvents(const std::vector<float> &xData,
                  const std::vector<float> &yData, sf::RenderWindow &window,
                  sf::View &view, LineRenderer &lineRenderer,
                  const float &scale) {
  while (const std::optional<sf::Event> event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    } else if (event->is<sf::Event::Resized>()) {
      updateViewOnResize(window, view);
      lineRenderer.setData(xData, yData, scale, scale);
    }
  }
}

int main() {
  DataLoader loader("Lissajous.dat");
  const auto &xData = loader.getColumn("x(t)");
  const auto &yData = loader.getColumn("y(t)");

  sf::ContextSettings settings;
  settings.antiAliasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode({800U, 600U}), "Data Visualizer",
                          sf::Style::Default, sf::State::Windowed, settings);
  window.setFramerateLimit(60);

  sf::View view;
  updateViewOnResize(window, view);

  GridRenderer gridRenderer;
  LineRenderer lineRenderer;

  const float scale = 120.0F;

  lineRenderer.setThickness(2.0F);
  lineRenderer.setColor(sf::Color(225, 225, 225, 200));

  lineRenderer.setData(xData, yData, scale, scale);

  while (window.isOpen()) {
    handleEvents(xData, yData, window, view, lineRenderer, scale);

    window.clear(sf::Color{33, 33, 33, 105});
    gridRenderer.renderGrid(window);
    lineRenderer.draw(window);
    window.display();
  }

  return 0;
}