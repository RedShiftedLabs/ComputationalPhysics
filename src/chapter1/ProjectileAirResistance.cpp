//========================================================
// File ProjectileAirResistance.cpp
// Shooting a projectile near the earth surface.
// No air resistance.
// Starts at (0,0), set k, (vO, theta) .
//--------------------------------------------------------

#include "Physics.h"
#include <Vector2D.h>
#include <cmath>
#include <fstream>
#include <iostream>

int main() {
  double x0;
  double y0;
  double R;
  double x;
  double y;
  double vx;
  double vy;
  double t;
  double tf;
  double dt;
  double k;
  double theta;
  double v0;
  double v0x;
  double v0y;
  std::string buf;

  std::cout << "Enter k,v0,theta (in degrees): ";
  std::cin >> k >> v0 >> theta;
  std::getline(std::cin, buf);
  std::cout << "Enter tf,dt: ";
  std::cin >> tf >> dt;
  std::getline(std::cin, buf);
  std::cout << "k = " << k << std::endl;
  std::cout << "v0= " << v0 << " theta= " << theta << "o (degrees)"
            << std::endl;
  std::cout << "t0= " << 0.0 << " tf= " << tf << " dt= " << dt << std::endl;

  if (v0 <= 0.0) {
    std::cerr << "Illegal value of v0 <= 0\n";
    std::exit(1);
  }
  if (k <= 0.0) {
    std::cerr << "Illegal value of k <= 0\n";
    std::exit(1);
  }
  if (theta <= 0.0) {
    std::cerr << "Illegal value of theta <= 0\n";
    std::exit(1);
  }
  if (theta >= 90.0) {
    std::cerr << "Illegal value of theta >= 90\n";
    std::exit(1);
  }

  theta = Phy::utils::degToRad(theta);
  v0x = v0 * std::cos(theta);
  v0y = v0 * std::sin(theta);

  std::cout << "v0x= " << v0x << " v0y= " << v0y << std::endl;

  std::ofstream file("ProjectileAirResistance.dat");
  file.precision(17);

  file << "Time(s) " << "x(t) " << "y(t) " << "Vx(t) "
       << "Vy(t) " << std::endl;

  t = 0.0;
  while (t <= tf) {
    x = (v0x / k) * (1.0 - std::exp(-k * t));
    y = (1.0 / k) * (v0y + (Phy::Const::g / k)) * (1.0 - std::exp(-k * t)) -
        (Phy::Const::g / k) * t;
    vx = v0x * std::exp(-k * t);
    vy = (v0y + (Phy::Const::g / k)) * std::exp(-k * t) - Phy::Const::g * t;
    file << t << " " << x << " " << y << " " << vx << " " << vy << std::endl;
    t += dt;
  }

  file.close();

  return 0;
}