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
