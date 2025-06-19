//=========================================================
// File box2D.cpp
// Motion of a free particle in a box 0<x<Lx 0<y<Ly
// Use integration with time step dt:
// x = x + vx * dt
// y = y + vy * dt
//---------------------------------------------------------

#include <cstdlib>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

int main() {
  float Lx;
  float Ly;
  float x0;
  float y0;
  float v0x;
  float v0y;
  float t0;
  float tf;
  float dt;
  float t;
  float x;
  float y;
  float vx;
  float vy;
  int i;
  int nx;
  int ny;
  std::string buf;

  std::cout << "Motion of a free particle in a box 0 < x < Lx 0 < y < Ly\n";
  std::cout << "Enter Lx, Ly: ";
  std::cin >> Lx >> Ly;
  std::getline(std::cin, buf);
  std::cout << "Enter x0, y0, vx, vy: ";
  std::cin >> x0 >> y0 >> vx >> vy;
  std::cout << "Enter t0, tf, dt: ";
  std::cin >> t0 >> tf >> dt;
  std::getline(std::cin, buf);
  std::cout << std::format("t0 = {}\ntf = {}\ndt = {}\n", t0, tf, dt);

  if (Lx <= 0.0 || Ly <= 0.0) {
    std::cerr << "Lx and Ly should be +ve\n";
    exit(1);
  }
  if (x0 < 0.0 || x0 > Lx) {
    std::cerr << "The range of x will be: 0 < x0 < Lx\n";
    exit(1);
  }
  std::cerr << "\n";
  if (y0 < 0.0 || y0 > Ly) {
    std::cerr << "The range of y will be: 0 < y0 < Ly\n";
    exit(1);
  }
  if (v0x * v0x + v0y * v0y == 0.0) {
    std::cerr << "v0 = 0\n";
    exit(1);
  }

  i = 0;
  nx = 0;
  ny = 0;
  t = t0;
  x = x0;
  y = y0;
  vx = v0x;
  vy = v0y;
  std::ofstream file("box2D.dat");
  file.precision(17);
  file << "Time(s), " << "x(t), " << "y(t), " << "vx(t), " << "vy(t)" << '\n';

  while (t < tf) {
    file << t << ", " << x << ", " << y << ", " << vx << ", " << vy << '\n';
    i++;
    t = y0 + i * dt;
    x += vx * dt;
    y += vy * dt;
    if (x < 0.0 || x > Lx) {
      vx = -vx;
      nx++;
    }
    if (y < 0.0 || y > Ly) {
      vy = -vy;
      ny++;
    }
  }
  file.close();
  std::cout << "Number of x bounces = " << nx << '\n';
  std::cout << "Number of y bounces = " << ny << '\n';
  return 0;
}