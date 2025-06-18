#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class DataLoader {
public:
  DataLoader(const std::string &filename) : m_filename(filename) {
    parseFile();
  }

  const std::vector<std::string> &getHeaders() const { return m_headers; }

  const std::unordered_map<std::string, std::vector<float>> &getData() const {
    return m_data;
  }

  const std::vector<float> &getColumn(const std::string &header) const {
    static std::vector<float> empty;
    auto it = m_data.find(header);
    return (it != m_data.end()) ? it->second : empty;
  }

  void printData() const {
    for (size_t i = 0; i < m_headers.size(); ++i) {
      std::cout << m_headers[i];
      if (i < m_headers.size() - 1) {
        std::cout << "\t";
      }
    }
    std::cout << std::endl;

    if (!m_headers.empty()) {
      size_t numRows = m_data.at(m_headers[0]).size();

      for (size_t row = 0; row < numRows; ++row) {
        for (size_t col = 0; col < m_headers.size(); ++col) {
          const auto &columnData = m_data.at(m_headers[col]);
          if (row < columnData.size()) {
            std::cout << columnData[row];
          }
          if (col < m_headers.size() - 1) {
            std::cout << "\t";
          }
        }
        std::cout << std::endl;
      }
    }
  }

private:
  std::unordered_map<std::string, std::vector<float>> m_data;
  std::vector<std::string> m_headers;
  std::string m_filename;

  void parseFile() {
    std::ifstream datFile(m_filename);

    if (!datFile.is_open()) {
      std::cerr << "Error: Could not open file '" << m_filename << "'"
                << std::endl;
      return;
    }

    std::string line;
    bool isFirstLine = true;

    while (std::getline(datFile, line)) {
      if (line.empty()) {
        continue;
      }

      std::istringstream iss(line);
      std::string token;
      std::vector<std::string> tokens;

      while (iss >> token) {
        tokens.push_back(token);
      }

      if (isFirstLine) {
        m_headers = tokens;

        for (const auto &header : m_headers) {
          m_data[header] = std::vector<float>();
        }

        isFirstLine = false;
      } else {
        for (size_t i = 0; i < tokens.size() && i < m_headers.size(); ++i) {
          try {
            float value = std::stof(tokens[i]);
            m_data[m_headers[i]].push_back(value);
          } catch (const std::exception &e) {
            std::cerr << "Warning: Could not parse value '" << tokens[i]
                      << "' for column '" << m_headers[i] << "'" << std::endl;
          }
        }
      }
    }

    datFile.close();
  }
};