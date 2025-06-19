// Physics.hpp

#pragma once

#include <cmath>
#include <stdexcept>
#include <string>

/**
 * @file physics.hpp
 * @brief A simplified C++ physics library with constants, units, and
 * utilities
 * @version 2.0
 * @author Physics Library Team
 *
 * This library provides:
 * - Physical constants (SI units)
 * - Simple unit conversions
 * - Common physics calculations
 * - Type-safe physical quantities
 */

namespace Phy {

//=============================================================================
// PHYSICAL CONSTANTS
//=============================================================================

/**
 * @brief Fundamental physical constants in SI units
 *
 * All constants are defined as constexpr double for compile-time evaluation
 * and follow the 2018 CODATA recommended values.
 */
namespace Const {

// Mathematical constants
constexpr double PI = 3.14159265358979323846;
constexpr double E = 2.71828182845904523536;
constexpr double SQRT_2 = 1.41421356237309504880;

// Universal constants
constexpr double c = 299792458.0;        // m/s
constexpr double G = 6.67430e-11;        // m³/(kg·s²)
constexpr double h = 6.62607015e-34;     // J·s
constexpr double hbar = 1.054571817e-34; // J·s (ℏ)
constexpr double k_B = 1.380649e-23;     // J/K
constexpr double Na = 6.02214076e23;     // mol⁻¹ (Avogadro's number)
constexpr double R = 8.31446261815324;   // J/(mol·K) (gas constant)

// Electromagnetic constants
constexpr double ELEMENTARY_CHARGE = 1.602176634e-19;    // C
constexpr double ε = 8.8541878128e-12;                   // F/m
constexpr double VACUUM_PERMEABILITY = 1.25663706212e-6; // H/m
constexpr double FINE_STRUCTURE = 7.2973525693e-3;       // dimensionless

// Particle masses
constexpr double ELECTRON_MASS = 9.1093837015e-31;     // kg
constexpr double PROTON_MASS = 1.67262192369e-27;      // kg
constexpr double NEUTRON_MASS = 1.67492749804e-27;     // kg
constexpr double ATOMIC_MASS_UNIT = 1.66053906660e-27; // kg

// Atomic constants
constexpr double BOHR_RADIUS = 5.29177210903e-11;    // m
constexpr double RYDBERG_CONSTANT = 10973731.568160; // 1/m
constexpr double BOHR_MAGNETON = 9.2740100783e-24;   // J/T

// Thermodynamic constants
constexpr double AVOGADRO_NUMBER = 6.02214076e23;   // 1/mol
constexpr double GAS_CONSTANT = 8.31446261815324;   // J/(mol·K)
constexpr double BOLTZMANN_CONSTANT = 1.380649e-23; // J/K
constexpr double STEFAN_BOLTZMANN = 5.670374419e-8; // W/(m²·K⁴)
constexpr double FARADAY_CONSTANT = 96485.33212;    // C/mol

// Earth and astronomical constants
constexpr double g = 9.80665;                        // m/s²
constexpr double MassEarth = 5.9722e24;              // kg
constexpr double EARTH_RADIUS = 6.3781e6;            // m
constexpr double ATMOSPHERIC_PRESSURE = 101325.0;    // Pa
constexpr double ASTRONOMICAL_UNIT = 1.495978707e11; // m
constexpr double LIGHT_YEAR = 9.4607304725808e15;    // m
constexpr double PARSEC = 3.0856775814671916e16;     // m
constexpr double SOLAR_MASS = 1.9884e30;             // kg
constexpr double SOLAR_RADIUS = 6.957e8;             // m

} // namespace Const

//=============================================================================
// UNIT CONVERSIONS
//=============================================================================

/**
 * @brief Simple unit conversion functions
 *
 * These functions provide easy conversion between common units.
 * All conversions are performed with high precision.
 */
namespace units {

// Length conversions
constexpr double meters_to_feet(double m) { return m * 3.28084; }
constexpr double feet_to_meters(double ft) { return ft / 3.28084; }
constexpr double meters_to_inches(double m) { return m * 39.3701; }
constexpr double inches_to_meters(double in) { return in / 39.3701; }
constexpr double km_to_miles(double km) { return km * 0.621371; }
constexpr double miles_to_km(double mi) { return mi / 0.621371; }

// Mass conversions
constexpr double kg_to_pounds(double kg) { return kg * 2.20462; }
constexpr double pounds_to_kg(double lb) { return lb / 2.20462; }
constexpr double grams_to_ounces(double g) { return g * 0.035274; }
constexpr double ounces_to_grams(double oz) { return oz / 0.035274; }

// Temperature conversions
constexpr double celsius_to_kelvin(double c) { return c + 273.15; }
constexpr double kelvin_to_celsius(double k) { return k - 273.15; }
constexpr double celsius_to_fahrenheit(double c) {
  return (c * 9.0 / 5.0) + 32.0;
}
constexpr double fahrenheit_to_celsius(double f) {
  return (f - 32.0) * 5.0 / 9.0;
}
constexpr double kelvin_to_fahrenheit(double k) {
  return celsius_to_fahrenheit(kelvin_to_celsius(k));
}
constexpr double fahrenheit_to_kelvin(double f) {
  return celsius_to_kelvin(fahrenheit_to_celsius(f));
}

// Energy conversions
constexpr double joules_to_calories(double j) { return j * 0.239006; }
constexpr double calories_to_joules(double cal) { return cal / 0.239006; }
constexpr double joules_to_eV(double j) { return j / Const::ELEMENTARY_CHARGE; }
constexpr double eV_to_joules(double ev) {
  return ev * Const::ELEMENTARY_CHARGE;
}
constexpr double joules_to_kwh(double j) { return j / 3.6e6; }
constexpr double kwh_to_joules(double kwh) { return kwh * 3.6e6; }

// Power conversions
constexpr double watts_to_horsepower(double w) { return w / 745.7; }
constexpr double horsepower_to_watts(double hp) { return hp * 745.7; }

// Pressure conversions
constexpr double pascals_to_atm(double pa) {
  return pa / Const::ATMOSPHERIC_PRESSURE;
}
constexpr double atm_to_pascals(double atm) {
  return atm * Const::ATMOSPHERIC_PRESSURE;
}
constexpr double pascals_to_psi(double pa) { return pa * 0.000145038; }
constexpr double psi_to_pascals(double psi) { return psi / 0.000145038; }

} // namespace units

//=============================================================================
// PHYSICAL QUANTITY CLASS
//=============================================================================

/**
 * @brief Type-safe physical quantity with automatic unit tracking
 *
 * This class represents a physical quantity with its value and unit.
 * It prevents unit mixing errors and provides automatic conversions.
 */
template <typename T = double> class Quantity {
private:
  T value_;
  std::string unit_;

public:
  /**
   * @brief Constructor
   * @param value The numerical value
   * @param unit The unit as a string (e.g., "m", "kg", "s")
   */
  constexpr Quantity(T value = 0, const std::string &unit = "")
      : value_(value), unit_(unit) {}

  // Getters
  constexpr T value() const { return value_; }
  const std::string &unit() const { return unit_; }

  // Arithmetic operations (same units only)
  Quantity operator+(const Quantity &other) const {
    if (unit_ != other.unit_ && !unit_.empty() && !other.unit_.empty()) {
      throw std::invalid_argument(
          "Cannot add quantities with different units: " + unit_ + " and " +
          other.unit_);
    }
    return Quantity(value_ + other.value_, unit_.empty() ? other.unit_ : unit_);
  }

  Quantity operator-(const Quantity &other) const {
    if (unit_ != other.unit_ && !unit_.empty() && !other.unit_.empty()) {
      throw std::invalid_argument(
          "Cannot subtract quantities with different units: " + unit_ +
          " and " + other.unit_);
    }
    return Quantity(value_ - other.value_, unit_.empty() ? other.unit_ : unit_);
  }

  // Scalar multiplication
  Quantity operator*(T scalar) const {
    return Quantity(value_ * scalar, unit_);
  }

  Quantity operator/(T scalar) const {
    return Quantity(value_ / scalar, unit_);
  }

  // Comparison operators
  bool operator==(const Quantity &other) const {
    return value_ == other.value_ && unit_ == other.unit_;
  }

  bool operator<(const Quantity &other) const {
    if (unit_ != other.unit_ && !unit_.empty() && !other.unit_.empty()) {
      throw std::invalid_argument(
          "Cannot compare quantities with different units");
    }
    return value_ < other.value_;
  }

  bool operator>(const Quantity &other) const { return other < *this; }

  // String representation
  std::string toString() const {
    return std::to_string(value_) + (unit_.empty() ? "" : " " + unit_);
  }
};

// Convenient type aliases
using Length = Quantity<double>;
using Mass = Quantity<double>;
using Time = Quantity<double>;
using Velocity = Quantity<double>;
using Acceleration = Quantity<double>;
using Force = Quantity<double>;
using Energy = Quantity<double>;
using Power = Quantity<double>;
using Temperature = Quantity<double>;

//=============================================================================
// PHYSICS CALCULATIONS
//=============================================================================

/**
 * @brief Common physics calculations and formulas
 *
 * These functions implement fundamental physics equations.
 * All calculations use SI units unless otherwise specified.
 */
namespace calculations {

/**
 * @brief Calculate kinetic energy (KE = ½mv²)
 * @param mass Mass in kg
 * @param velocity Velocity in m/s
 * @return Kinetic energy in J
 */
inline double kinetic_energy(double mass, double velocity) {
  return 0.5 * mass * velocity * velocity;
}

/**
 * @brief Calculate potential energy (PE = mgh)
 * @param mass Mass in kg
 * @param height Height in m
 * @param gravity Gravitational acceleration in m/s² (default: Earth's gravity)
 * @return Potential energy in J
 */
inline double potential_energy(double mass, double height,
                               double gravity = Const::g) {
  return mass * gravity * height;
}

/**
 * @brief Calculate gravitational force between two masses
 * @param mass1 First mass in kg
 * @param mass2 Second mass in kg
 * @param distance Distance between centers in m
 * @return Gravitational force in N
 */
inline double gravitational_force(double mass1, double mass2, double distance) {
  return Const::G * mass1 * mass2 / (distance * distance);
}

/**
 * @brief Calculate electric force between two charges (Coulomb's law)
 * @param charge1 First charge in C
 * @param charge2 Second charge in C
 * @param distance Distance between charges in m
 * @return Electric force in N
 */
inline double electric_force(double charge1, double charge2, double distance) {
  constexpr double k = 1.0 / (4.0 * Const::PI * Const::ε);
  return k * charge1 * charge2 / (distance * distance);
}

/**
 * @brief Calculate momentum (p = mv)
 * @param mass Mass in kg
 * @param velocity Velocity in m/s
 * @return Momentum in kg⋅m/s
 */
inline double momentum(double mass, double velocity) { return mass * velocity; }

/**
 * @brief Calculate work done (W = F⋅d)
 * @param force Force in N
 * @param distance Distance in m
 * @param angle Angle between force and displacement in radians (default: 0)
 * @return Work in J
 */
inline double work(double force, double distance, double angle = 0.0) {
  return force * distance * std::cos(angle);
}

/**
 * @brief Calculate power (P = W/t)
 * @param work Work in J
 * @param time Time in s
 * @return Power in W
 */
inline double power(double work, double time) { return work / time; }

/**
 * @brief Calculate escape velocity
 * @param mass Mass of celestial body in kg
 * @param radius Radius of celestial body in m
 * @return Escape velocity in m/s
 */
inline double escape_velocity(double mass, double radius) {
  return std::sqrt(2.0 * Const::G * mass / radius);
}

/**
 * @brief Calculate orbital velocity for circular orbit
 * @param central_mass Mass of central body in kg
 * @param orbital_radius Orbital radius in m
 * @return Orbital velocity in m/s
 */
inline double orbital_velocity(double central_mass, double orbital_radius) {
  return std::sqrt(Const::G * central_mass / orbital_radius);
}

/**
 * @brief Calculate orbital period using Kepler's third law
 * @param semi_major_axis Semi-major axis in m
 * @param central_mass Mass of central body in kg
 * @return Orbital period in s
 */
inline double orbital_period(double semi_major_axis, double central_mass) {
  return 2.0 * Const::PI *
         std::sqrt(std::pow(semi_major_axis, 3) / (Const::G * central_mass));
}

/**
 * @brief Calculate photon energy from wavelength
 * @param wavelength Wavelength in m
 * @return Photon energy in J
 */
inline double photon_energy(double wavelength) {
  return Const::h * Const::c / wavelength;
}

/**
 * @brief Calculate wavelength from frequency
 * @param frequency Frequency in Hz
 * @return Wavelength in m
 */
inline double wavelength_from_frequency(double frequency) {
  return Const::c / frequency;
}

/**
 * @brief Calculate Lorentz factor for relativistic effects
 * @param velocity Velocity in m/s
 * @return Lorentz factor (dimensionless)
 */
inline double lorentz_factor(double velocity) {
  double beta = velocity / Const::c;
  return 1.0 / std::sqrt(1.0 - (beta * beta));
}

/**
 * @brief Calculate rest mass energy (E = mc²)
 * @param mass Rest mass in kg
 * @return Energy in J
 */
inline double rest_mass_energy(double mass) {
  return mass * Const::c * Const::c;
}

/**
 * @brief Calculate ideal gas pressure (PV = nRT)
 * @param moles Number of moles
 * @param temperature Temperature in K
 * @param volume Volume in m³
 * @return Pressure in Pa
 */
inline double ideal_gas_pressure(double moles, double temperature,
                                 double volume) {
  return moles * Const::R * temperature / volume;
}

/**
 * @brief Calculate blackbody radiation power (Stefan-Boltzmann law)
 * @param temperature Temperature in K
 * @param surface_area Surface area in m²
 * @param emissivity Emissivity (0-1, default: 1 for perfect blackbody)
 * @return Radiated power in W
 */
inline double blackbody_power(double temperature, double surface_area,
                              double emissivity = 1.0) {
  return emissivity * Const::STEFAN_BOLTZMANN * surface_area *
         std::pow(temperature, 4);
}

} // namespace calculations

//=============================================================================
// UTILITY FUNCTIONS
//=============================================================================

/**
 * @brief Utility functions for common operations
 */
namespace utils {

/**
 * @brief Convert degrees to radians
 */
constexpr double deg2rad(double degrees) { return degrees * Const::PI / 180.0; }

/**
 * @brief Convert radians to degrees
 */
constexpr double rad2deg(double radians) { return radians * 180.0 / Const::PI; }

/**
 * @brief Check if a number is approximately equal to another (useful for
 * floating point comparison)
 */
inline bool approximately_equal(double a, double b, double tolerance = 1e-9) {
  return std::abs(a - b) < tolerance;
}

/**
 * @brief Clamp a value between min and max
 */
template <typename T> constexpr T clamp(T value, T min_val, T max_val) {
  if (value < min_val) {
    return min_val;
  }
  if (value > max_val) {
    return max_val;
  }
  return value;
}

/**
 * @brief Linear interpolation between two values
 */
template <typename T> constexpr T lerp(T a, T b, double t) {
  return a + (t * (b - a));
}

} // namespace utils

} // namespace Phy