#include <Vector2D.h>
#include <fstream>
#include <iostream>

int main() {
  Vector2D Position;
  Vector2D velocity;
  double R = 1.0;
  double t0 = 0.0;
  double tf;
  double dt;
  double w1;
  double w2;
  double T1;
  double T2;

  std::cout << "Enter the angular frequencies (w1, w2): ";
  std::cin >> w1 >> w2;
  std::cout << "Enter the final time (tf) and time step (dt): ";
  std::cin >> tf >> dt;

  if (w1 <= 0.0 || w2 <= 0.0) {
    std::cerr << "Error: Angular frequencies must be positive." << std::endl;
    return 1;
  }

  T1 = 2.0 * M_PI / w1;
  T2 = 2.0 * M_PI / w2;

  std::cout << "w1 = " << w1 << ", w2 = " << w2 << "\n";
  std::cout << "t0 = " << t0 << ", tf = " << tf << ", dt = " << dt << "\n";
  std::cout << "T1 = " << T1 << ", T2 = " << T2 << "\n";

  std::ofstream file("Lissajous.dat");
  file.precision(10);

  file << "Time(s) " << "x(t) " << "y(t) " << "Vx(t) " << "Vy(t)" << '\n';

  double t = t0;
  while (t <= tf) {
    Position = {R * cos(w1 * t), R * sin(w2 * t)};
    velocity = {R * w1 * cos(w1 * t), R * w2 * cos(w2 * t)};
    file << t << " " << Position.x << " " << Position.y << " " << velocity.x
         << " " << velocity.y << "\n";
    t += dt;
  }

  return 0;
}