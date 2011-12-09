#ifndef UTILS_H_
#define UTILS_H_

#include "Nominal.h"
#include "Exception.h"
#include <limits>
#include <iostream>

using namespace std;

namespace Shipping {

    class Miles : public Ordinal<Miles, double> {
    public:
        Miles() : Ordinal<Miles, double>(1.0) {}
        Miles(double value) : Ordinal<Miles, double>(value) {
            if (value < 0.0) {
                std::cerr << "Miles out of range" << std::endl;
                throw(Fwk::RangeException("Miles"));
            }
        }
        static Miles max() { return std::numeric_limits<double>::max(); }
    };

    class MilesPerHour : public Ordinal<MilesPerHour, double> {
    public:
        MilesPerHour() : Ordinal<MilesPerHour, double>(1.0) {}
        MilesPerHour(double value) : Ordinal<MilesPerHour, double>(value) {
            if (value < 0.0)
            {
                cerr << "MilesPerHour out of range" << endl;
                throw(Fwk::RangeException("MilesPerHour"));
            }
        }
        static MilesPerHour max() {return std::numeric_limits<double>::max();}
    };

    class Dollars : public Ordinal<Dollars, double> {
    public:
        Dollars() : Ordinal<Dollars, double>(1.0) {}
        Dollars(double value) : Ordinal<Dollars, double>(value) {
            if (value < 0.0)
            {
                cerr << "Dollars out of range" << std::endl;
                throw(Fwk::RangeException("Dollars"));
            }
        }
        static Dollars max() { return std::numeric_limits<double>::max(); }
    };

    class Hours : public Ordinal<Hours, double> {
    public:
        Hours() : Ordinal<Hours, double>(0.0) {}
        Hours(double value) : Ordinal<Hours, double>(value) {
            if (value < 0.0)
            {
                cerr << "Hours out of range" << std::endl;
                throw(Fwk::RangeException("Hours"));
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
                cerr << "DollarsPerMile out of range" << std::endl;
                throw(Fwk::RangeException("DollarsPerMile"));
            }
        }
        static DollarsPerMile max() { return std::numeric_limits<double>::max(); }
    };

    class TransferRate : public Ordinal<TransferRate, unsigned int> {
    public:
        TransferRate() : Ordinal<TransferRate, unsigned int>(0) {}
        TransferRate(unsigned int value)
            : Ordinal<TransferRate, unsigned int>(value) {}
    };

    class PackageCount : public Ordinal<PackageCount, unsigned int> {
    public:
        PackageCount() : Ordinal<PackageCount, unsigned int>(0) {}
        PackageCount(unsigned int value)
            : Ordinal<PackageCount, unsigned int>(value) {}
    };

    class ShipmentCount : public Ordinal<ShipmentCount, unsigned int> {
    public:
        ShipmentCount() : Ordinal<ShipmentCount, unsigned int>(0) {}
        ShipmentCount(unsigned int value)
            : Ordinal<ShipmentCount, unsigned int>(value) {}
    };

    class Latency : public Ordinal<Latency, double> {
    public:
        Latency() : Ordinal<Latency, double>(0.0) {}
        Latency(unsigned int value) : Ordinal<Latency, double>(value) {
            if (value < 0.0)
            {
                cerr << "Latency out of range" << std::endl;
                throw(Fwk::RangeException("Latency"));
            }
        }
        static Latency max() { return std::numeric_limits<double>::max(); }
    };

    class TimeOfDay : public Ordinal<TimeOfDay, unsigned int> {
    public:
        TimeOfDay() : Ordinal<TimeOfDay, unsigned int>(0) {}
        TimeOfDay(unsigned int value)
            : Ordinal<TimeOfDay, unsigned int>(value){
             if (value > 23)
            {
                cerr << "TimeOfDay out of range" << std::endl;
                throw(Fwk::RangeException("TimeOfDay"));
            }
        }
    };


}

#endif /* UTILS_H_ */
