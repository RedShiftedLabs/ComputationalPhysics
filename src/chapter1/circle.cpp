#include <Physics.h>
#include <cmath>
#include <fstream>
#include <iostream>

int main() {
  // Variables
  double x0;
  double y0;
  double R;
  double x;
  double y;
  double vx;
  double vy;
  double t;
  double t0;
  double tf;
  double dt;
  double theta;
  double omega;

  // User input
  std::cout << "Enter angular velocity (omega): ";
  std::cin >> omega;

  std::cout << "Enter center of circle (x0, y0) and radius (R): ";
  std::cin >> x0 >> y0 >> R;

  std::cout << "Enter initial time (t0), final time (tf), and time step (dt): ";
  std::cin >> t0 >> tf >> dt;

  std::cout << "Omega = " << omega << '\n';
  std::cout << "Center: (" << x0 << ", " << y0 << ")  Radius = " << R << '\n';
  std::cout << "Time range: t0 = " << t0 << ", tf = " << tf << ", dt = " << dt
            << '\n';

  // Validity checks
  if (R <= 0.0) {
    std::cerr << "Error: Invalid radius (R must be positive)" << '\n';
    return 1;
  }
  if (omega <= 0.0) {
    std::cerr << "Error: Invalid omega (must be positive)" << '\n';
    return 1;
  }

  std::cout << "Time period T = " << (2.0 * Phy::Const::PI / omega) << '\n';

  // Open file to store results
  std::ofstream file("Circle.dat");
  if (!file) {
    std::cerr << "Error: Could not open file for writing" << '\n';
    return 1;
  }

  file << "Time(s) " << "x(t) " << "y(t) " << "Vx(t) " << "Vy(t)" << '\n';

  // Compute motion
  t = t0;
  while (t <= tf) {
    theta = omega * (t - t0);
    x = x0 + R * cos(theta);
    y = y0 + R * sin(theta);
    vx = -omega * R * sin(theta);
    vy = omega * R * cos(theta);
    file << t << " " << x << " " << y << " " << vx << " " << vy << '\n';
    t += dt;
  }

  file.close();
  return 0;
}