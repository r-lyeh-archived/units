#include "units.hpp"
#include <iostream>
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
}
