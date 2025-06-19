// ==============================================================
// File MiniGolf.cpp
// Motion of a free particle in a box 0 < x < Lx, 0 < y < Ly
// The box is open at x=0 and has a hole at (xc, yc) of radius R
// Ball is shot at (0, Ly/2) with speed vO, angle theta (degrees)
// Use integration with time step dt:
// x = x + vx * dt
// y = y + vy * dt
// Ball stops in hole (success) or at x=0 (failure)
//---------------------------------------------------------------

#include <Physics.h>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

int main() {
  double Lx;
  double Ly;
  double x0;
  double y0;
  double v0x;
  double v0y;
  double t0;
  double tf;
  double dt;
  double t;
  double x;
  double y;
  double vx;
  double vy;
  double v0;
  double theta;
  double xc;
  double yc;
  double R;
  double R2;
  int i;
  int nx;
  int ny;
  std::string result;
  std::string buf;

  std::cout << "Enter Lx, Ly: ";
  std::cin >> Lx >> Ly;
  std::getline(std::cin, buf);
  std::cout << "Lx = " << Lx << " Ly = " << Ly << std::endl;

  std::cout << "Enter hole position and radius: (xc, yc), R: ";
  std::cin >> xc >> yc >> R;
  std::getline(std::cin, buf);
  std::cout << " (xc, yc) = ( " << xc << ", " << yc << " ) "
            << " R= " << R << std::endl;

  std::cout << "Enter v0, theta(degrees): ";
  std::cin >> v0 >> theta;
  std::getline(std::cin, buf);
  std::cout << "v0= " << v0 << " theta= " << theta << " degrees " << std::endl;

  std::cout << "Enter dt: ";
  std::cin >> dt;
  std::getline(std::cin, buf);

  if (Lx <= 0.0) {
    std::cerr << "Lx <= 0\n";
    std::exit(1);
  }
  if (Ly <= 0.0) {
    std::cerr << "Ly <= 0\n";
    std::exit(1);
  }
  if (v0 <= 0.0) {
    std::cerr << "v0 <= 0\n";
    std::exit(1);
  }
  if (std::abs(theta) > 90.0) {
    std::cerr << "theta > 90\n";
    std::exit(1);
  }

  t0 = 0.0;
  x0 = 0.00001;
  y0 = Ly / 2.0;
  R2 = R * R;
  theta = Phy::utils::deg2rad(theta);
  v0x = v0 * std::cos(theta);
  v0y = v0 * std::sin(theta);

  std::cout << "x0= " << x0 << " y0= " << y0 << " v0x= " << v0x
            << " v0y= " << v0y << std::endl;

  i = 0;
  nx = 0;
  ny = 0;
  t = t0;
  x = x0;
  y = y0;
  vx = v0x;
  vy = v0y;

  std::ofstream file("MiniGolf.dat");
  file.precision(17);
  file << "Time(s), " << "x(t), " << "y(t), " << "Vx(t), "
       << "Vy(t)\n";

  while (true) {
    file << t << ", " << x << ", " << y << ", " << vx << ", " << vy << "\n";

    i++;
    t = t0 + i * dt;
    x += vx * dt;
    y += vy * dt;

    if (x > Lx) {
      vx = -vx;
      nx++;
    }
    if (y < 0.0) {
      vy = -vy;
      ny++;
    }
    if (y > Ly) {
      vy = -vy;
      ny++;
    }
    if (x <= 0.0) {
      result = "Failure";
      break;
    }
    if (((x - xc) * (x - xc) + (y - yc) * (y - yc)) <= R2) {
      result = "Success";
      break;
    }
  }

  file.close();
  std::cout << "Number of collisions:\n";
  std::cout << "Result= " << result << " nx= " << nx << " ny= " << ny
            << std::endl;
}