#include <Physics.h>
#include <Vector2D.h>
#include <cmath>
#include <fstream>
#include <iostream>

int main() {
  double l;
  double theta0;
  double t0;
  double tf;
  double dt;

  // Ask user for input
  std::cout << "Enter l: ";
  std::cin >> l;
  std::cout << "Enter theta0: ";
  std::cin >> theta0;

  std::cout << "Enter t0, tf, dt: ";
  std::cin >> t0 >> tf >> dt;

  std::cout << "l= " << l << " theta0= " << theta0 << '\n';
  std::cout << "t0 = " << t0 << " tf = " << tf << " dt = " << dt << '\n';

  // Initialize
  double omega = std::sqrt(Physics::constants::GRAVITATIONAL_CONSTANT / l);
  std::cout << "omega = " << omega
            << " T = " << (2.0 * Physics::constants::PI / omega) << '\n';

  // Open file to save data
  std::ofstream file(
      "/Users/redshifted/Documents/Wolfram/PhysicsData/SimplePendulum.dat");

  // Compute
  for (double t = t0; t <= tf; t += dt) {
    double theta = theta0 * std::cos(omega * (t - t0));
    double dthetaDt = -omega * theta0 * std::sin(omega * (t - t0));
    double x = l * std::sin(theta);
    double y = -l * std::cos(theta);
    double vx = l * dthetaDt * std::cos(theta);
    double vy = l * dthetaDt * std::sin(theta);

    file << t << " " << x << " " << y << " " << vx << " " << vy << " " << theta
         << " " << dthetaDt << '\n';
  }

  file.close();
  return 0;
}