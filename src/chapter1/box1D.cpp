//========================================================
// File box1D.cpp
// Motion of a free particle in a box 0 < x < L
// Use integration with time step dt : x = x + v * dt
//--------------------------------------------------------

#include <cstdlib>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

int main() {
  float L;
  float x0;
  float v0;
  float t0;
  float tf;
  float dt;
  float t;
  float x;
  float v;
  std::string buf;
  std::cout << "Enter L: ";
  std::cin >> L;
  std::getline(std::cin, buf);
  std::cout << "Enter x0, v0: ";
  std::cin >> x0 >> v0;
  std::cout << "Enter t0, tf, dt: ";
  std::cin >> t0 >> tf >> dt;
  std::getline(std::cin, buf);
  std::cout << std::format("t0 = {}\ntf = {}\ndt = {}\n", t0, tf, dt);
  if (L <= 0.0F) {
    std::cerr << "L <= 0\n";
    exit(1);
  }
  if (x0 < 0.0F) {
    std::cerr << "x0 < 0\n";
    exit(1);
  }
  if (x0 > L) {
    std::cerr << "x0 > L\n";
    exit(1);
  }
  if (v0 == 0.0F) {
    std::cerr << "v0 = 0\n";
    exit(1);
  }

  t = t0;
  std::ofstream file("box1D.dat");
  file.precision(9);
  file << std::setw(17) << "Time(s)" << " " << std::setw(17) << "x(t)" << " "
       << std::setw(17) << "v(t)" << '\n';

  while (t < tf) {
    x = x0 + v0 * (t - t0);
    file << std::setw(17) << t << " " << std::setw(17) << x << " "
         << std::setw(17) << v << '\n';
    if (x < 0.0F || x > L) {
      x0 = x;
      t0 = t0;
      v0 = -v0;
    }
    t += dt;
  }
  file.close();
  return 0;
}