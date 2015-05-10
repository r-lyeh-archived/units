units <a href="https://travis-ci.org/r-lyeh/units"><img src="https://api.travis-ci.org/r-lyeh/units.svg?branch=master" align="right" /></a>
=====

A C++ library to provide numerical quantities with units.  This catches many programming errors and provides implicit conversion between compatible quantities.

## Download
- Latest version: [units.hpp](units.hpp)
- Manual: [units.html](https://github.com/r-lyeh/units)
- Home page: http://calumgrant.net/units (unavailable)
- License: Boost Software License.

## Purpose
Conversion errors are very common programming errors.  It is very easy to pass a value in seconds when you mean minutes, or just pass the wrong number to the wrong argument.  Units catch such errors at compile time.

Units provide simple automatic conversion, that just do the right thing when you expect them to, so you can assign, add or compare seconds with minutes, meters with inches, or indeed any compatible quantities.  A large number of SI and imperial units are provided by the library.

Arithmetic respects units, so you can only add compatible quantities (of the same dimension) together, and when you multiply or divide values, you multiply or divide the units.  This catches mistakes in formulae.  A number of physical constants are provided with their correct units.

## Example
```c++
#include <iostream>
#include "units.hpp"
int main() {
    using namespace units::values;

    std::cout << "One mile is " << km(mile(1)) << std::endl;
    // Output: One mile is 1.60934 km

    std::cout << "Flow rate is " << m3(mile(1)*inch(80)*foot(9))/s(minute(5)) << std::endl;
    // Output: Flow rate is 29.9026 (m)^3.(s)^-1

    hour h;
    //h = cm(3); // Compile-time error: incompatible units
    //h = 4;     // Compile-time error: 4 of what?
    h = day(4);  // Ok: h is 96 hours
    std::cout << "4 days is " << h << std::endl; // Ok: h is 96 hours

    // information
    byte size(16384);
    std::cout << "16384 bytes is " << (size) << std::endl;
    std::cout << "16384 bytes is " << KiB(size) << std::endl;

    // bandwidth / transfer rate
    std::cout << "1 megabyte is " << KiB(MiB(1)) << std::endl;
    std::cout << "transfer rate is " << MiBps( MiB(10) / s(5) ) << std::endl;
}
```

## Introduction

This library is for engineers and scientists
who deal with physical quantities. Units provide a safety net that check
the validity of formulae at compile-time and ensure that different units are
converted where necessary. A large number of physical quantities are
provided by the library, including all SI units.

This library is for software engineers.
By giving a quantity a unit, it prevents the wrong value being assigned to the
wrong thing, or passing the wrong value to the wrong argument of a function.
Units documentation a program - *int* is not descriptive, but *apples* is.

The library uses templates and generative
programming techniques to handle units at compile time, so there is no
run-time overhead. Many units are predefined and it is straightforward
to add your own.

The library is installed by copying the file
[units.hpp](units.hpp) into your include directory. To use the library

```c++
#include "units.hpp"
```

**Using built in units**

The built in physical quantities are in the
namespace *units::values*, so for the purposes of this tutorial, assume
that

```c++
using namespace units::values;
```

has been written somewhere near the top of the
file. This namespace gives you access to the following physical
quantities:

- No unit: *unit, percent, dozen, bakers_dozen*
- Mass: *kg, g, mg, lb, oz, tonne*
- Time: *s, ms, ns, us, minute, hour, day, week*
- Calendar: *month, year, century, millennium*
- Distance: *m, cm, mm, km, inch, foot, yard, mile, nautical_mile*
- Temperature: *K, Celsius, Fahrenheit*
- Force: *N*
- Pressure: *Pa, kPa, psi, millibar*
- Energy: *J*
- Power: *W*
- Area: *m2, hectare, are, inch2, acre*
- Volume: *cm3, ml, cl, liter, dl, m3*
- Velocity: *mph, kph, meters_per_second, knot, mach*
- Angle: *rad, degree, grad, degree_minute, degree_second*
- Information: *byte, KiB, MiB, GiB, TiB, PiB*
- Bandwidth: *bps, KiBps, MiBps, GiBps, TiBps, PiBps*
- Other units: *A, mol, cd, rad, sr, Hz, C, V, F, Ohm, S, Wb, T, H, lm, lx, Bq, Gy, Sv, kat, rpm*


The naming convention is to use the symbol of
the SI unit. For other units, the  name is used since there are no
standard symbols.
The built-in values are all doubles, however
you can change this (see next section). The physical quantities behave
exactly as normal doubles, except that they check the units and perform
conversion where necessary.
A value can be constructed from a number,
another value, or the default constructor which initializes the value to zero.
When constructing from another value, the other value must be compatible or
you will get a compile-time error:

```c++
m x;          // x = 0
m y(10);      // y = 10
m z(cm(250)); // z = 2.5
m w(s(3));    // Compile-time error: incompatible units
kph(mph(70))  // Convert miles per hour to km per hour
```

Assignment is only possible from another value,
and the value must be compatible:

```c++
x = 10;         // Compile-time error: 10 of what?
x = cm(200);    // Ok: x = 2.0
x = s(3)        // Compile-time error: incompatible units
```

The number in the value can be obtained using the `get()` method:

```c++
x.get();        // Get current value of x
cm(m(5)).get()  // 500
```

The normal arithmetic operators are supported:
`+, -, *, /, /=, *=, ++, --`. There are some restrictions however.
You can only add or subtract compatible values. You can multiply or
divide by any other value, which returns a value with a unit with the correct
type (multiplied or divided). The `*=` and `/=` operators can
only take a number (in general if you multiply by another unit the type will
be different). e.g.

```c++
// Add two distances
miles x = m(1) + cm(10);
// Converts to meters squared
m2 area = foot(10) * yard(3);
s timer;
// Compile-time error: add 10 of what
timer += 10;
// Ok: add 10 seconds to timer
timer += s(10);
// Ok
liter v = hectare(1) * mm(1);
// A complex (but valid) formula
H h(  m(4)*m(8)*kg(2)/s(2)/s(4)/A(1)/A(2) );
// Compile-time error: Can't add time and distance
s(10) + m(4);
```

The comparison operators (`==, !=, <, <=, >, >=`) also convert between units implicitly:

```c++
minutes(2) > s(70)      // true
```

Writing a value to a stream (using `operator <<`) displays the unit after the value. Many of the built in units
have names, otherwise the text is generated, as in the following example:

```c++
 std::cout << "Flow rate is " << m3(mile(1)*inch(80)*foot(9))/s(minute(5));
// Output: Flow rate is 29.9026 (m)^3.(s)^-1
```

The `units::sqrt` function provides a square root - which also takes the root of the unit of course.

```c++
m a, b, c;
c = units::sqrt( a*a + b*b );
```

You can  take an arbitrary rational power of a number using the `units::raise` template, however you must
specify the power at compile time so that the compiler knows the unit of the return
value. e.g.

```c++
units::raise<3,1>(m(2)) == m(2)*m(2)*m(2)
```

There are some trigonometric functions (*units::sin*,
*units::cos* and *units::tan*) which take an angle. You can
supply any unit of angle to the function and the function will convert to
radians. e.g.

```c++
units::tan( degree(45) );
```

There are a number of constants available in the *units::constants* namespace. These are

```c++
k, mu, NA, G0, e0, me, eV, e, F, alpha, inv_alpha, u0, phi0, R, G, h, h_bar, mp, Rinf, c, rho, pi, lightyear, g
```

Example:

```c++
N attractive_force = units::constants::G * kg(1) * kg(2) / m(3) / m(5);
```

**Creating new units**

Values with units are provided by the `units::value<>` class template, declared as follows:

```c++
template<typename Value, typename Unit>
class value;
```

The predefined units (as used in the previous section) are declared in the `units::units` namespace. So
you can reuse any of these units but provide a different type, e.g.

```c++
units::value<float, units::units::m> length;
```

The unit can be any type, so to create a
new unit, just create a new type:

```c++
struct apples;
struct oranges;
typedef units::value<int, apples>  apples_t;
typedef units::value<int, oranges> oranges_t;
```

The new value will be protected from interoperating with naked numbers or other types of unit:

```c++
apples_t n(5);
n = oranges_t(3);    // Compile-time error
n = apples_t(10);    // Ok
```

**Displaying units**

When a value is output (using `operator<<`), it appends the unit to the stream. By default the unit will
display the text `"units"`. You can change this by declaring the name of the unit with the `UNITS_DISPLAY_NAME`
macro, which takes the unit as its first parameter, and its name as its second parameter. e.g.

```c++
UNITS_DISPLAY_NAME( apples, "apples" );
UNITS_DISPLAY_NAME( oranges, "oranges" );
```

```c++
std::cout << oranges_t(2);   // Output: 2 oranges
```

**Converting between units**

A unit can be defined in terms of other units. The templates `units::scale, units::translate, units::pow` and
`units::compose` provide a means of constructing new units which can be converted from and to another unit.
The `units::scale<>` template constructs a unit which is a multiple of another:

```c++
struct penny;
typedef units::scale<penny, 4> farthing;      // Multiply penny * 4 to get farthings
typedef units::scale<penny, 1, 12> shilling;  // Multiply penny by 1/12 to get shillings
typedef units::scale<shilling, 1, 20> pound;
typedef units::scale<penny, 1, 30> half_crown;
typedef units::scale<half_crown, 1, 2> crown;
```

```c++
std::cout << "There are " << penny(pound(1)).get() << " old pence in the pound\n";
```

The `units::translate<>` template  constructs a unit which is offset from another:

```c++
typedef units::translate<units::units::K, -27315, 100> Celcius;
// Celcius = K - 27315/100
```

The `units::pow<>` template constructs a unit which is a power of another unit:

```c++
typedef units::pow<units::units::m, 3> m3;    // One cubic meter
```

Finally the `units::compose<>` template  creates a unit which  multiplies two other units:

```c++
typedef units::compose<power, time> energy;
typedef units::compose< units::units::m, units::pow<units::units::s, -1> > meters_per_second;
```

The conversion operators are able to analyse the type of the unit and generate a conversion function automatically!

## Licenses
- [units](https://github.com/r-lyeh/units) by Calum Grant (BOOST licensed).

## Changelog
- v1.1.0
   - Binary SI units for information (byte, KiB, MiB, GiB, TiB, PiB) (@r-lyeh)
   - Binary SI units for bandwidth (bps, KiBps, MiBps, GiBps, TiBps, PiBps) (@r-lyeh)
- v1.0.0
  - Initial commit (Calum Grant)
