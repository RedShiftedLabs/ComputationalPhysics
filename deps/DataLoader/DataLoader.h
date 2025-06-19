#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class DataLoader {
public:
  DataLoader(const std::string &filename, char delimiter = ',')
      : m_filename(filename), m_delimiter(delimiter) {
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

    if (m_headers.empty() || m_data.at(m_headers[0]).empty()) {
      return;
    }

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

private:
  std::unordered_map<std::string, std::vector<float>> m_data;
  std::vector<std::string> m_headers;
  std::string m_filename;
  char m_delimiter;

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
      if (line.empty() || line.find_first_not_of(" \t") == std::string::npos) {
        continue;
      }

      std::vector<std::string> tokens;

      // Use logic based on the delimiter
      if (m_delimiter == ' ') {
        // Use stringstream extraction for space-separated data
        // This handles multiple spaces gracefully
        std::istringstream iss(line);
        std::string token;
        while (iss >> token) {
          tokens.push_back(token);
        }
      } else {
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, m_delimiter)) {
          const auto first = token.find_first_not_of(" \t\n\r");
          if (first == std::string::npos) {
            continue;
          }
          const auto last = token.find_last_not_of(" \t\n\r");
          tokens.push_back(token.substr(first, last - first + 1));
        }
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