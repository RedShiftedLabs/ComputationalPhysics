//========================================================
// File box1D_1.cpp
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
  struct Time {
    float t0;
    float tf;
    float dt;
    float t;
  };
  float x;
  float v;
  std::string buf;
  Time time;
  std::cout << "Enter L: ";
  std::cin >> L;
  std::getline(std::cin, buf);
  std::cout << "Enter x0, v0: ";
  std::cin >> x0 >> v0;
  std::cout << "Enter t0, tf, dt: ";
  std::cin >> time.t0 >> time.tf >> time.dt;
  std::getline(std::cin, buf);
  std::cout << std::format("t0 = {}\ntf = {}\ndt = {}\n", time.t0, time.tf,
                           time.dt);
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

  time.t = time.t0;
  x = x0;
  v = v0;
  std::ofstream file("box1D_1.dat");
  file.precision(9);
  file << std::setw(17) << "Time(s)" << " " << std::setw(17) << "x(t)" << " "
       << std::setw(17) << "v(t)" << '\n';
  while (time.t < time.tf) {
    file << std::setw(17) << time.t << " " << std::setw(17) << x << " "
         << std::setw(17) << v << '\n';
    x += v * time.dt;
    time.t += time.dt;
    if (x < 0.0F || x > L) {
      v = -v;
    }
  }
  file.close();
  return 0;
}