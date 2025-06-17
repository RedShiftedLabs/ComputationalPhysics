# Physics Library Documentation

## Overview

This is a simplified C++ physics library that provides physical constants, unit conversions, type-safe physical quantities, and common physics calculations. The library is designed to be easy to use while preventing common unit-related errors.

## Features

- 📊 **Physical Constants**: All major physical constants in SI units
- 🔄 **Unit Conversions**: Simple functions for common unit conversions
- 🛡️ **Type Safety**: `Quantity` class prevents unit mixing errors
- 🧮 **Physics Calculations**: Common physics formulas and equations
- ⚡ **Performance**: Constexpr functions for compile-time evaluation
- 📖 **Easy to Use**: Simple, intuitive API

## Quick Start

```cpp
#include "physics.hpp"
#include <iostream>

int main() {
    using namespace physics;
    
    // Use physical constants
    std::cout << "Speed of light: " << constants::SPEED_OF_LIGHT << " m/s\n";
    
    // Convert units
    double temp_f = units::celsius_to_fahrenheit(25.0);
    std::cout << "25°C = " << temp_f << "°F\n";
    
    // Calculate kinetic energy
    double ke = calculations::kinetic_energy(10.0, 5.0); // 10 kg, 5 m/s
    std::cout << "Kinetic energy: " << ke << " J\n";
    
    return 0;
}
```

## Detailed Usage

### 1. Physical Constants

All constants are in the `physics::constants` namespace and use SI base units:

```cpp
using namespace physics::constants;

// Universal constants
double c = SPEED_OF_LIGHT;           // 299,792,458 m/s
double G = GRAVITATIONAL_CONSTANT;   // 6.674×10⁻¹¹ m³/(kg·s²)
double h = PLANCK_CONSTANT;          // 6.626×10⁻³⁴ J·s

// Particle masses
double m_e = ELECTRON_MASS;          // 9.109×10⁻³¹ kg
double m_p = PROTON_MASS;            // 1.673×10⁻²⁷ kg

// Earth constants
double g = EARTH_GRAVITY;            // 9.80665 m/s²
double M_earth = EARTH_MASS;         // 5.972×10²⁴ kg
```

### 2. Unit Conversions

Simple conversion functions in the `physics::units` namespace:

```cpp
using namespace physics::units;

// Length conversions
double feet = meters_to_feet(10.0);      // 10 m → feet
double meters = feet_to_meters(30.0);    // 30 ft → meters
double miles = km_to_miles(100.0);       // 100 km → miles

// Temperature conversions
double kelvin = celsius_to_kelvin(25.0); // 25°C → K
double fahrenheit = celsius_to_fahrenheit(0.0); // 0°C → °F

// Energy conversions
double calories = joules_to_calories(1000.0); // 1000 J → calories
double eV = joules_to_eV(1.6e-19);           // Joules → electron volts

// Mass conversions
double pounds = kg_to_pounds(70.0);       // 70 kg → pounds
```

### 3. Type-Safe Physical Quantities

The `Quantity` class prevents unit mixing errors:

```cpp
using namespace physics;

// Create quantities with units
Length distance(100.0, "m");
Mass mass(50.0, "kg");
Time time(10.0, "s");

// Safe arithmetic (same units only)
Length total_distance = Length(50.0, "m") + Length(25.0, "m"); // OK
// Length invalid = Length(50.0, "m") + Mass(10.0, "kg");     // ERROR!

// Scalar operations
Velocity velocity = distance / 10.0; // Scale by scalar

// Display with units
std::cout << distance.toString() << std::endl; // "100.000000 m"

// Access value and unit separately
double value = distance.value();    // 100.0
std::string unit = distance.unit(); // "m"
```

### 4. Physics Calculations

Common physics formulas in the `physics::calculations` namespace:

#### Mechanics

```cpp
using namespace physics::calculations;

// Kinetic energy: KE = ½mv²
double ke = kinetic_energy(10.0, 5.0); // 10 kg, 5 m/s → 125 J

// Potential energy: PE = mgh
double pe = potential_energy(10.0, 100.0); // 10 kg, 100 m → 9806.65 J

// Momentum: p = mv
double p = momentum(10.0, 5.0); // 10 kg, 5 m/s → 50 kg⋅m/s

// Work: W = F⋅d⋅cos(θ)
double w = work(100.0, 10.0, 0.0); // 100 N, 10 m, 0° → 1000 J

// Power: P = W/t
double power_val = power(1000.0, 10.0); // 1000 J, 10 s → 100 W
```

#### Gravitation

```cpp
// Gravitational force between two masses
double F = gravitational_force(1000.0, 2000.0, 10.0); // F = GMm/r²

// Escape velocity from a planet
double v_escape = escape_velocity(constants::EARTH_MASS, constants::EARTH_RADIUS);

// Orbital velocity for circular orbit
double v_orbital = orbital_velocity(constants::EARTH_MASS, 400000.0); // 400 km altitude

// Orbital period using Kepler's 3rd law
double period = orbital_period(400000.0, constants::EARTH_MASS);
```

#### Electromagnetism

```cpp
// Electric force (Coulomb's law)
double F_electric = electric_force(1e-6, 2e-6, 0.1); // 1 μC, 2 μC, 0.1 m apart
```

#### Waves and Optics

```cpp
// Photon energy from wavelength
double E_photon = photon_energy(500e-9); // 500 nm light

// Wavelength from frequency
double lambda = wavelength_from_frequency(1e14); // 100 THz
```

#### Relativity

```cpp
// Lorentz factor for relativistic effects
double gamma = lorentz_factor(0.9 * constants::SPEED_OF_LIGHT); // v = 0.9c

// Rest mass energy: E = mc²
double E_rest = rest_mass_energy(1.0); // 1 kg → 9×10¹⁶ J
```

#### Thermodynamics

```cpp
// Ideal gas pressure: PV = nRT
double pressure = ideal_gas_pressure(1.0, 300.0, 0.001); // 1 mol, 300 K, 0.001 m³

// Blackbody radiation power
double power_rad = blackbody_power(300.0, 1.0); // 300 K, 1 m² surface
```

### 5. Utility Functions

Helper functions in the `physics::utils` namespace:

```cpp
using namespace physics::utils;

// Angle conversions
double radians = deg_to_rad(90.0);  // 90° → π/2 rad
double degrees = rad_to_deg(3.14159); // π rad → 180°

// Floating point comparison
bool equal = approximately_equal(1.0/3.0, 0.333333, 1e-5);

// Value clamping
double clamped = clamp(15.0, 0.0, 10.0); // Result: 10.0

// Linear interpolation
double interpolated = lerp(0.0, 100.0, 0.5); // Result: 50.0
```

## Example Programs

### 1. Projectile Motion Calculator

```cpp
#include "physics.hpp"
#include <iostream>
#include <cmath>

int main() {
    using namespace physics;
    
    double initial_velocity = 20.0; // m/s
    double angle_deg = 45.0;        // degrees
    double angle_rad = utils::deg_to_rad(angle_deg);
    
    // Calculate components
    double v_x = initial_velocity * std::cos(angle_rad);
    double v_y = initial_velocity * std::sin(angle_rad);
    
    // Time of flight
    double time_flight = 2.0 * v_y / constants::EARTH_GRAVITY;
    
    // Maximum height
    double max_height = calculations::potential_energy(1.0, v_y * v_y / (2.0 * constants::EARTH_GRAVITY)) / constants::EARTH_GRAVITY;
    
    // Range
    double range = v_x * time_flight;
    
    std::cout << "Projectile Motion Results:\n";
    std::cout << "Time of flight: " << time_flight << " s\n";
    std::cout << "Maximum height: " << max_height << " m\n";
    std::cout << "Range: " << range << " m\n";
    
    return 0;
}
```

### 2. Planetary Data Calculator

```cpp
#include "physics.hpp"
#include <iostream>

int main() {
    using namespace physics;
    
    // Mars data
    double mars_mass = 6.39e23;    // kg
    double mars_radius = 3.390e6;  // m
    
    // Calculate Mars properties
    double mars_gravity = constants::GRAVITATIONAL_CONSTANT * mars_mass / (mars_radius * mars_radius);
    double mars_escape_vel = calculations::escape_velocity(mars_mass, mars_radius);
    
    std::cout << "Mars Properties:\n";
    std::cout << "Surface gravity: " << mars_gravity << " m/s²\n";
    std::cout << "Escape velocity: " << mars_escape_vel << " m/s\n";
    std::cout << "Escape velocity: " << units::meters_to_feet(mars_escape_vel) << " ft/s\n";
    
    // Compare with Earth
    std::cout << "\nComparison with Earth:\n";
    std::cout << "Mars gravity / Earth gravity: " << mars_gravity / constants::EARTH_GRAVITY << "\n";
    
    return 0;
}
```

### 3. Energy Conversion Calculator

```cpp
#include "physics.hpp"
#include <iostream>

int main() {
    using namespace physics;
    
    double energy_joules = 1000.0; // 1 kJ
    
    std::cout << "Energy Conversions for " << energy_joules << " J:\n";
    std::cout << "Calories: " << units::joules_to_calories(energy_joules) << " cal\n";
    std::cout << "kWh: " << units::joules_to_kwh(energy_joules) << " kWh\n";
    std::cout << "eV: " << units::joules_to_eV(energy_joules) << " eV\n";
    
    // Equivalent mass (E = mc²)
    double equiv_mass = energy_joules / (constants::SPEED_OF_LIGHT * constants::SPEED_OF_LIGHT);
    std::cout << "Equivalent mass: " << equiv_mass << " kg\n";
    
    return 0;
}
```

## Error Handling

The library includes basic error handling:

```cpp
try {
    // This will throw an exception
    Length result = Length(10.0, "m") + Mass(5.0, "kg");
} catch (const std::invalid_argument& e) {
    std::cout << "Error: " << e.what() << std::endl;
}

// Safe comparison with error handling
try {
    Length distance1(10.0, "m");
    Mass mass1(5.0, "kg");
    
    // This will throw an exception
    bool result = distance1 < mass1;
} catch (const std::invalid_argument& e) {
    std::cout << "Cannot compare different unit types: " << e.what() << std::endl;
}
```

## Best Practices

### 1. Use Appropriate Namespaces

```cpp
// Good: Use specific namespaces
using namespace physics::constants;
using namespace physics::calculations;

// Avoid: Using the entire physics namespace
// using namespace physics; // Can cause name conflicts
```

### 2. Prefer constexpr for Compile-Time Constants

```cpp
// Good: Compile-time evaluation
constexpr double earth_escape_velocity = 
    std::sqrt(2.0 * GRAVITATIONAL_CONSTANT * EARTH_MASS / EARTH_RADIUS);

// The calculation happens at compile time when possible
```

### 3. Use Type-Safe Quantities for Complex Calculations

```cpp
// Good: Type-safe approach
Length height(100.0, "m");
Mass mass(10.0, "kg");
Energy potential = Energy(calculations::potential_energy(mass.value(), height.value()), "J");

// Better: Create helper functions
Energy calculate_potential_energy(const Mass& m, const Length& h) {
    return Energy(calculations::potential_energy(m.value(), h.value()), "J");
}
```

### 4. Handle Edge Cases

```cpp
// Check for division by zero
double safe_divide(double numerator, double denominator) {
    if (utils::approximately_equal(denominator, 0.0)) {
        throw std::invalid_argument("Division by zero");
    }
    return numerator / denominator;
}

// Check for negative values in square root calculations
double safe_sqrt(double value) {
    if (value < 0.0) {
        throw std::invalid_argument("Cannot take square root of negative number");
    }
    return std::sqrt(value);
}
```

## Advanced Examples

### 1. Orbital Mechanics Simulator

```cpp
#include "physics.hpp"
#include <iostream>
#include <vector>
#include <cmath>

struct OrbitData {
    double semi_major_axis;  // m
    double eccentricity;     // dimensionless
    double period;           // s
    double velocity_periapsis; // m/s
    double velocity_apoapsis;  // m/s
};

OrbitData calculate_orbit(double central_mass, double periapsis, double apoapsis) {
    using namespace physics;
    
    OrbitData orbit;
    
    orbit.semi_major_axis = (periapsis + apoapsis) / 2.0;
    orbit.eccentricity = (apoapsis - periapsis) / (apoapsis + periapsis);
    orbit.period = calculations::orbital_period(orbit.semi_major_axis, central_mass);
    
    // Vis-viva equation for velocities
    double mu = constants::GRAVITATIONAL_CONSTANT * central_mass;
    orbit.velocity_periapsis = std::sqrt(mu * (2.0/periapsis - 1.0/orbit.semi_major_axis));
    orbit.velocity_apoapsis = std::sqrt(mu * (2.0/apoapsis - 1.0/orbit.semi_major_axis));
    
    return orbit;
}

int main() {
    using namespace physics;
    
    // Calculate orbit for ISS-like parameters
    double earth_mass = constants::EARTH_MASS;
    double periapsis = constants::EARTH_RADIUS + 400000;  // 400 km altitude
    double apoapsis = constants::EARTH_RADIUS + 420000;   // 420 km altitude
    
    OrbitData iss_orbit = calculate_orbit(earth_mass, periapsis, apoapsis);
    
    std::cout << "ISS-like Orbit Analysis:\n";
    std::cout << "Semi-major axis: " << iss_orbit.semi_major_axis/1000 << " km\n";
    std::cout << "Eccentricity: " << iss_orbit.eccentricity << "\n";
    std::cout << "Orbital period: " << iss_orbit.period/60 << " minutes\n";
    std::cout << "Velocity at periapsis: " << iss_orbit.velocity_periapsis/1000 << " km/s\n";
    std::cout << "Velocity at apoapsis: " << iss_orbit.velocity_apoapsis/1000 << " km/s\n";
    
    return 0;
}
```

### 2. Electromagnetic Field Calculator

```cpp
#include "physics.hpp"
#include <iostream>
#include <cmath>

class ElectricField {
private:
    double charge_;     // C
    double x_, y_, z_;  // m (position)
    
public:
    ElectricField(double charge, double x, double y, double z)
        : charge_(charge), x_(x), y_(y), z_(z) {}
    
    // Calculate electric field at a point
    std::tuple<double, double, double> field_at_point(double px, double py, double pz) const {
        using namespace physics::constants;
        
        double dx = px - x_;
        double dy = py - y_;
        double dz = pz - z_;
        double r = std::sqrt(dx*dx + dy*dy + dz*dz);
        
        if (r < 1e-10) return {0, 0, 0}; // Avoid singularity
        
        double k = 1.0 / (4.0 * PI * VACUUM_PERMITTIVITY);
        double field_magnitude = k * charge_ / (r * r);
        
        // Unit vector components
        double ux = dx / r;
        double uy = dy / r;
        double uz = dz / r;
        
        return {field_magnitude * ux, field_magnitude * uy, field_magnitude * uz};
    }
    
    // Calculate potential at a point
    double potential_at_point(double px, double py, double pz) const {
        using namespace physics::constants;
        
        double dx = px - x_;
        double dy = py - y_;
        double dz = pz - z_;
        double r = std::sqrt(dx*dx + dy*dy + dz*dz);
        
        if (r < 1e-10) return 0; // Avoid singularity
        
        double k = 1.0 / (4.0 * PI * VACUUM_PERMITTIVITY);
        return k * charge_ / r;
    }
};

int main() {
    // Create two point charges
    ElectricField charge1(1e-9, -1.0, 0.0, 0.0);  // +1 nC at (-1, 0, 0)
    ElectricField charge2(-1e-9, 1.0, 0.0, 0.0);  // -1 nC at (1, 0, 0)
    
    // Calculate field at origin
    auto [Ex1, Ey1, Ez1] = charge1.field_at_point(0, 0, 0);
    auto [Ex2, Ey2, Ez2] = charge2.field_at_point(0, 0, 0);
    
    double Ex_total = Ex1 + Ex2;
    double Ey_total = Ey1 + Ey2;
    double Ez_total = Ez1 + Ez2;
    
    std::cout << "Electric Field at Origin:\n";
    std::cout << "Ex: " << Ex_total << " N/C\n";
    std::cout << "Ey: " << Ey_total << " N/C\n";
    std::cout << "Ez: " << Ez_total << " N/C\n";
    
    double field_magnitude = std::sqrt(Ex_total*Ex_total + Ey_total*Ey_total + Ez_total*Ez_total);
    std::cout << "Total field magnitude: " << field_magnitude << " N/C\n";
    
    return 0;
}
```

### 3. Thermodynamics Calculator

```cpp
#include "physics.hpp"
#include <iostream>
#include <cmath>

class IdealGas {
private:
    double moles_;
    double volume_;     // m³
    double temperature_; // K
    double pressure_;   // Pa
    
public:
    IdealGas(double moles, double volume, double temperature)
        : moles_(moles), volume_(volume), temperature_(temperature) {
        update_pressure();
    }
    
    void update_pressure() {
        pressure_ = physics::calculations::ideal_gas_pressure(moles_, temperature_, volume_);
    }
    
    void set_temperature(double temp) {
        temperature_ = temp;
        update_pressure();
    }
    
    void set_volume(double vol) {
        volume_ = vol;
        update_pressure();
    }
    
    // Isothermal process (constant temperature)
    void isothermal_expansion(double new_volume) {
        double old_pressure = pressure_;
        set_volume(new_volume);
        
        std::cout << "Isothermal Process:\n";
        std::cout << "P1V1 = " << old_pressure * (volume_ / new_volume * volume_) << " Pa⋅m³\n";
        std::cout << "P2V2 = " << pressure_ * volume_ << " Pa⋅m³\n";
    }
    
    // Adiabatic process (no heat exchange)
    void adiabatic_expansion(double new_volume, double gamma = 1.4) {
        // For adiabatic process: PV^γ = constant
        double old_pressure = pressure_;
        double old_volume = volume_;
        
        pressure_ = old_pressure * std::pow(old_volume / new_volume, gamma);
        volume_ = new_volume;
        
        // Update temperature using ideal gas law
        temperature_ = pressure_ * volume_ / (moles_ * physics::constants::GAS_CONSTANT);
        
        std::cout << "Adiabatic Process:\n";
        std::cout << "P1V1^γ = " << old_pressure * std::pow(old_volume, gamma) << "\n";
        std::cout << "P2V2^γ = " << pressure_ * std::pow(volume_, gamma) << "\n";
    }
    
    // Calculate internal energy (for monoatomic gas)
    double internal_energy() const {
        return 1.5 * moles_ * physics::constants::GAS_CONSTANT * temperature_;
    }
    
    // Getters
    double pressure() const { return pressure_; }
    double volume() const { return volume_; }
    double temperature() const { return temperature_; }
    double moles() const { return moles_; }
};

int main() {
    using namespace physics;
    
    // Create an ideal gas: 1 mole at 300 K in 0.001 m³
    IdealGas gas(1.0, 0.001, 300.0);
    
    std::cout << "Initial State:\n";
    std::cout << "Pressure: " << gas.pressure() << " Pa\n";
    std::cout << "Volume: " << gas.volume() << " m³\n";
    std::cout << "Temperature: " << gas.temperature() << " K\n";
    std::cout << "Internal Energy: " << gas.internal_energy() << " J\n\n";
    
    // Isothermal expansion to double the volume
    gas.isothermal_expansion(0.002);
    std::cout << "After isothermal expansion:\n";
    std::cout << "Pressure: " << gas.pressure() << " Pa\n";
    std::cout << "Temperature: " << gas.temperature() << " K\n\n";
    
    // Reset and try adiabatic expansion
    IdealGas gas2(1.0, 0.001, 300.0);
    gas2.adiabatic_expansion(0.002, 1.4);
    std::cout << "After adiabatic expansion:\n";
    std::cout << "Pressure: " << gas2.pressure() << " Pa\n";
    std::cout << "Temperature: " << gas2.temperature() << " K\n";
    std::cout << "Temperature change: " << gas2.temperature() - 300.0 << " K\n";
    
    return 0;
}
```

## Compilation and Integration

### CMakeLists.txt Example

```cmake
cmake_minimum_required(VERSION 3.10)
project(PhysicsLibraryExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the physics library header
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create executable
add_executable(physics_example main.cpp)

# Optional: Add compiler flags for optimization
target_compile_options(physics_example PRIVATE -O3 -Wall -Wextra)
```

### Makefile Example

```makefile
CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -Iinclude
TARGET = physics_example
SOURCES = main.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: clean
```

## Library Limitations and Future Enhancements

### Current Limitations

1. **Unit System**: Currently focuses on SI units with basic conversions
2. **Error Handling**: Basic exception throwing, could be more sophisticated
3. **Complex Numbers**: No support for complex calculations (AC circuits, quantum mechanics)
4. **Vector Operations**: No built-in vector/tensor operations
5. **Numerical Methods**: No integration, differentiation, or ODE solvers

### Potential Future Enhancements

1. **Extended Unit System**: Full dimensional analysis with automatic unit derivation
2. **Vector/Matrix Library**: Built-in support for 3D vectors and matrices
3. **Numerical Methods**: Integration, differentiation, root finding
4. **Specialized Physics Modules**: Quantum mechanics, fluid dynamics, thermodynamics
5. **Plotting Interface**: Integration with plotting libraries
6. **Configuration File Support**: Load constants and settings from files
7. **Parallel Computing**: OpenMP support for computationally intensive calculations

## Contributing

To extend this library:

1. **Adding Constants**: Add new constants to the appropriate namespace in `constants`
2. **Adding Conversions**: Implement new conversion functions in `units` namespace
3. **Adding Calculations**: Create new calculation functions in `calculations` namespace
4. **Documentation**: Update this documentation with new examples
5. **Testing**: Add unit tests for new functionality

### Example: Adding a New Calculation

```cpp
namespace physics {
namespace calculations {

/**
 * @brief Calculate centripetal force (F = mv²/r)
 * @param mass Mass in kg
 * @param velocity Velocity in m/s
 * @param radius Radius in m
 * @return Centripetal force in N
 */
inline double centripetal_force(double mass, double velocity, double radius) {
    return mass * velocity * velocity / radius;
}

} // namespace calculations
} // namespace physics
```

This physics library provides a solid foundation for physics calculations while remaining simple and easy to use. The modular design makes it easy to extend with additional functionality as needed.