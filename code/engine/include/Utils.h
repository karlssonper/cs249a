#ifndef UTILS_H_
#define UTILS_H_

#include "Nominal.h"
#include <limits>
#include <iostream>

using namespace std;

namespace Shipping {

    class Miles : public Ordinal<Miles, double> {
    public:
        Miles() : Ordinal<Miles, double>(1) {}
        Miles(double value) : Ordinal<Miles, double>(value) {}

        static Miles max() { return std::numeric_limits<double>::max(); }
    };

    class MilesPerHour : public Ordinal<MilesPerHour, double> {
    public:
        MilesPerHour() : Ordinal<MilesPerHour, double>(1.f) {}
        MilesPerHour(double value) : Ordinal<MilesPerHour, double>(value) {
            if (value <= 0.0)
            {
                cerr << "MilesPerHour out of range, using default value (1.0) " << endl;
                value = 1.0;
            }
        }
    };

    class Dollars : public Ordinal<Dollars, double> {
    public:
        Dollars() : Ordinal<Dollars, double>(1.f) {}
        Dollars(double value) : Ordinal<Dollars, double>(value) {
            if (value < 0.0)
            {
                cerr << "Dollars out of range, using default value (1.0)" << std::endl;
                value = 1.0;
            }
        }

        static Dollars max() { return std::numeric_limits<double>::max(); }
    };

    class Hours : public Ordinal<Hours, double> {
    public:
        Hours() : Ordinal<Hours, double>(1.f) {}
        Hours(double value) : Ordinal<Hours, double>(value) {
            if (value < 0.0)
            {
                cerr << "Hours out of range, using default value (1.0)" << std::endl;
                value = 1.0;
            }
        }
        static Hours max() { return std::numeric_limits<double>::max(); }
    };

    class DollarsPerMile : public Ordinal<DollarsPerMile, double> {
    public:
        DollarsPerMile() : Ordinal<DollarsPerMile, double>(1.f) {}
        DollarsPerMile(double value) : Ordinal<DollarsPerMile, double>(value) {
            if (value < 0.0)
            {
                cerr << "DollarsPerMile out of range, using default value (1.0)" << std::endl;
                value = 1.0;
            }
        }
    };

    class PackageCapacity : public Ordinal<PackageCapacity, unsigned int> {
    public:
        PackageCapacity() : Ordinal<PackageCapacity, unsigned int>(1) {}
        PackageCapacity(unsigned int value) : Ordinal<PackageCapacity, unsigned int>(value) {}
    };

    class TransferRate : public Ordinal<TransferRate, unsigned int> {
    public:
        TransferRate() : Ordinal<TransferRate, unsigned int>(0) {}
        TransferRate(unsigned int value) : Ordinal<TransferRate, unsigned int>(value) {}
    };

    class PackageCount : public Ordinal<PackageCount, unsigned int> {
    public:
        PackageCount() : Ordinal<PackageCount, unsigned int>(0) {}
        PackageCount(unsigned int value) : Ordinal<PackageCount, unsigned int>(value) {}
    };

    class Latency : public Ordinal<Latency, double> {
    public:
        Latency() : Ordinal<Latency, double>(0) {}
        Latency(unsigned int value) : Ordinal<Latency, double>(value) {}
    };


}

#endif /* UTILS_H_ */
