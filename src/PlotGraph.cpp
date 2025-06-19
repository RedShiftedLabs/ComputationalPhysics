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

void handleEvents(sf::RenderWindow &window, sf::View &view) {
  while (const std::optional<sf::Event> event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    } else if (event->is<sf::Event::Resized>()) {
      updateViewOnResize(window, view);
    }
  }
}

int main() {
  DataLoader loader("Box2D.dat");
  const auto &Time = loader.getColumn("Time(s)");
  const auto &xData = loader.getColumn("x(t)");
  const auto &yData = loader.getColumn("y(t)");
  const auto &vx = loader.getColumn("vx(t)");
  const auto &vy = loader.getColumn("vy(t)");

  sf::ContextSettings settings;
  settings.antiAliasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode({800U, 600U}), "Data Visualizer",
                          sf::Style::Default, sf::State::Windowed, settings);
  window.setFramerateLimit(60);

  sf::View view;
  updateViewOnResize(window, view);

  GridRenderer gridRenderer;
  LineRenderer lineRenderer1;
  LineRenderer lineRenderer2;
  LineRenderer lineRenderer3;
  LineRenderer lineRenderer4;

  const float scaleX = 5.0F;
  const float scaleY = 10.0F;

  //   lineRenderer1.setThickness(2.0F);
  //   lineRenderer1.setColor(sf::Color(205, 0, 0, 200));
  //   lineRenderer1.setData(Time, xData, scaleX, scaleY);

  //   lineRenderer2.setThickness(2.0F);
  //   lineRenderer2.setColor(sf::Color(0, 205, 0, 200));
  //   lineRenderer2.setData(Time, yData, scaleX, scaleY);

  lineRenderer3.setThickness(2.0F);
  lineRenderer3.setColor(sf::Color(0, 205, 0, 200));
  lineRenderer3.setData(Time, vx, scaleX, scaleY);

  lineRenderer4.setThickness(2.0F);
  lineRenderer4.setColor(sf::Color(205, 0, 0, 200));
  lineRenderer4.setData(Time, vy, scaleX, scaleY);

  while (window.isOpen()) {
    handleEvents(window, view);
    window.clear(sf::Color{33, 33, 33, 105});
    gridRenderer.renderGrid(window);

    // lineRenderer1.draw(window);
    // lineRenderer2.draw(window);
    lineRenderer3.draw(window);
    lineRenderer4.draw(window);

    window.display();
  }

  return 0;
}