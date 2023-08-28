//!
//! @file   stats.hpp
//! @date   08/25/2023
//! @author Kaleb Cole (kalebcole95@gmail.com)
//!
//! @brief
//!
//!
//!

#ifndef _STATISTICS_STATS_HPP_
#define _STATISTICS_STATS_HPP_

#include <iostream>

#include "aircrafts/aircrafts.hpp"
#include "units/time.hpp"

namespace statistics
{

   ////////////////////////////////////////////////////////////////////////////////

   class AircraftStats
   {
   public:
      AircraftStats(aircrafts::AircraftBase *aircraft)
            : type(aircraft->type)
            , speed(aircraft->speed)
            , passengerCount(aircraft->passengerCount)
            , _totalAircrafts(0)
            , _totalFlights(0)
            , _totalFlightTime(0_sec)
            , _totalCharges(0)
            , _totalChargingTime(0_sec)
            , _totalAttemptedChargingTime(0_sec)
            , _totalFaults(0)
      {
      }

      void addData(aircrafts::AircraftBase *aircraft)
      {
         _totalAircrafts++;
         _totalFlights += aircraft->getTotalFlights();
         _totalFlightTime += aircraft->getTotalFlightTime();
         _totalCharges += aircraft->getTotalCharges();
         _totalChargingTime += aircraft->getTotalChargingTime();
         _totalAttemptedChargingTime += aircraft->getTotalAttemptedChargingTime();
         _totalFaults += aircraft->getTotalFaults();
      }

      void printStatistics()
      {
         std::cout << std::endl;
         std::cout << " ===== " << type << " (" << _totalAircrafts << ") ===== " << std::endl;
         std::cout << "   Average Flight Time:\t\t\t" << (_totalFlightTime / _totalFlights) << std::endl;
         std::cout << "   Average Flight Distance:\t\t" << (_totalFlightTime / _totalFlights) / 1_hour * speed
                   << " miles" << std::endl;
         std::cout << "   Average Charging Time:\t\t" << (_totalChargingTime / _totalCharges) << std::endl;
         std::cout << "   Average Attempted Charging Time:\t" << (_totalAttemptedChargingTime / _totalCharges)
                   << std::endl;
         std::cout << "   Total Faults:\t\t\t" << _totalFaults << " faults" << std::endl;
         std::cout << "   Total Passenger Miles:\t\t" << _totalFlightTime / 1_hour * speed * passengerCount << " miles"
                   << std::endl;
         std::cout << std::endl;
      }

      const aircrafts::AircraftType type;
      const unsigned int speed;
      const unsigned int passengerCount;

   protected:
      unsigned int _totalAircrafts;
      unsigned int _totalFlights;
      Time _totalFlightTime;
      unsigned int _totalCharges;
      Time _totalChargingTime;
      Time _totalAttemptedChargingTime;
      unsigned int _totalFaults;
   };

   ////////////////////////////////////////////////////////////////////////////////

} // namespace statistics

#endif // _STATISTICS_STATS_HPP_