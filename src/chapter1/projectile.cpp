#include <fstream>
#include <iostream>
#include <stdexcept>

constexpr double g = 9.81;
constexpr double PI = 3.1415927;

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
  double theta;
  double v0x;
  double v0y;
  double v0;

  std::cout << "Enter v0, theta (in degrees): ";
  std::cin >> v0 >> theta;
  std::cout << "Enter final Time in, dt: ";
  std::cin >> tf >> dt;
  std::cout << "v0 = " << v0 << "  theta = " << theta << "°"
            << "  t0 = " << 0.0 << "  tf = " << tf << "  dt = " << dt << '\n';

  if (v0 <= 0.0) {
    throw std::invalid_argument("Illegal value of v0<=0");
  }
  if (theta <= 0.0) {
    throw std::invalid_argument("Illegal value of theta");
  }

  theta = (PI / 180.0) * theta;
  v0x = v0 * std::cos(theta);
  v0y = v0 * std::sin(theta);

  std::cout << "v0x = " << v0x << "  v0y = " << v0y;

  std::ofstream file("Projectile.dat");

  file << "Time(s) " << "x(t) " << "y(t) " << "Vx(t) " << "Vy(t)" << '\n';

  t = 0.0;
  while (t <= tf) {
    x = v0x * t;
    y = v0y * t - 0.5 * g * t * t;
    vx = v0x;
    vy = v0y - g * t;
    file << t << " " << x << " " << y << " " << vx << " " << vy << std::endl;
    t += dt;
  }

  return 0;
}