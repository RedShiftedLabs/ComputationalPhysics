// deps/Renderers/LineRenderer.h

#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

class LineRenderer {
public:
  LineRenderer() : m_thickness(1.0F) {
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
  }

  void setData(const std::vector<float> &xData, const std::vector<float> &yData,
               float scaleX = 1.0F, float scaleY = 1.0F) {
    if (xData.size() != yData.size() || xData.size() < 2) {
      m_vertices.clear();
      return;
    }

    size_t segmentCount = xData.size() - 1;
    m_vertices.resize(segmentCount * 6);

    const float halfThickness = m_thickness * 0.5F;

    for (size_t i = 0; i < segmentCount; ++i) {
      sf::Vector2f p1(xData[i] * scaleX, yData[i] * scaleY);
      sf::Vector2f p2(xData[i + 1] * scaleX, yData[i + 1] * scaleY);

      createSegment(p1, p2, i * 6);
    }
  }

  void appendPoint(float x, float y, float scaleX = 1.0F, float scaleY = 1.0F) {
    sf::Vector2f newPoint(x * scaleX, y * scaleY);

    if (m_vertices.getVertexCount() == 0) {
      m_lastPoint = newPoint;
      return;
    }

    size_t currentCount = m_vertices.getVertexCount();
    m_vertices.resize(currentCount + 6);
    createSegment(m_lastPoint, newPoint, currentCount);
    m_lastPoint = newPoint;
  }

  void setThickness(float thickness) { m_thickness = thickness; }
  void setColor(const sf::Color &color) { m_color = color; }
  void clear() {
    m_vertices.clear();
    m_lastPoint = sf::Vector2f();
  }
  size_t getVertexCount() const { return m_vertices.getVertexCount(); }

  void draw(sf::RenderTarget &target,
            const sf::RenderStates &states = sf::RenderStates::Default) const {
    if (m_vertices.getVertexCount() > 0) {
      target.draw(m_vertices, states);
    }
  }

private:
  sf::VertexArray m_vertices;
  sf::Vector2f m_lastPoint;
  float m_thickness;
  sf::Color m_color = sf::Color(225, 225, 225, 128);

  void createSegment(const sf::Vector2f &p1, const sf::Vector2f &p2,
                     size_t startIndex) {
    const float halfThickness = m_thickness * 0.5F;

    sf::Vector2f dir = p2 - p1;
    float length = std::sqrt((dir.x * dir.x) + (dir.y * dir.y));

    if (length < 1e-6F) {
      // Degenerate segment - create point
      for (size_t j = 0; j < 6; ++j) {
        m_vertices[startIndex + j] = sf::Vertex(p1, m_color);
      }
      return;
    }

    dir /= length;
    sf::Vector2f perp(-dir.y * halfThickness, dir.x * halfThickness);

    sf::Vector2f p1_up = p1 + perp;
    sf::Vector2f p1_down = p1 - perp;
    sf::Vector2f p2_up = p2 + perp;
    sf::Vector2f p2_down = p2 - perp;

    // Two triangles forming the line segment
    m_vertices[startIndex + 0] = sf::Vertex(p1_up, m_color);
    m_vertices[startIndex + 1] = sf::Vertex(p1_down, m_color);
    m_vertices[startIndex + 2] = sf::Vertex(p2_up, m_color);

    m_vertices[startIndex + 3] = sf::Vertex(p1_down, m_color);
    m_vertices[startIndex + 4] = sf::Vertex(p2_down, m_color);
    m_vertices[startIndex + 5] = sf::Vertex(p2_up, m_color);
  }
};