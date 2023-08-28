//!
//! @file   aircrafts.cpp
//! @date   08/22/2023
//! @author Kaleb Cole (kalebcole95@gmail.com)
//!
//! @brief
//!
//!
//!

#include "aircrafts.hpp"

#include <cstdlib>

namespace aircrafts
{
   ////////////////////////////////////////////////////////////////////////////////

   std::ostream &operator<<(std::ostream &ostream, const AircraftType &aircraftType)
   {
      switch(aircraftType)
      {
         case AircraftType::Alpha:
            ostream << "Alpha Aircraft";
            break;
         case AircraftType::Bravo:
            ostream << "Bravo Aircraft";
            break;
         case AircraftType::Charlie:
            ostream << "Charlie Aircraft";
            break;
         case AircraftType::Delta:
            ostream << "Delta Aircraft";
            break;
         case AircraftType::Echo:
            ostream << "Echo Aircraft";
            break;
         default:
            ostream << "Unknown Aircraft Type";
      }
      return ostream;
   }

   ////////////////////////////////////////////////////////////////////////////////

   Time AircraftBase::operate(chargers::ChargeStation &chargeStation, Time operationTime)
   {
      switch(_state)
      {
         case AircraftState::FinishCharging:
            chargeStation.leave(id);
         case AircraftState::StartFlying:
            _totalFlights++;
            _state = AircraftState::Flying;
         case AircraftState::Flying:
            _batteryLevel -= (operationTime / 1_hour) * speed * energyPerMile;
            _totalFlightTime += operationTime;
            _totalFaults += ((rand() % 100) < ((long double)faultProbability * 100 * operationTime) / 1_hour) ? 1 : 0;

            if(_batteryLevel <= 0)
            {
               _batteryLevel = 0;
               _state = AircraftState::StartCharging;
               return chargeTime;
            }
            else
            {
               return (((long double)_batteryLevel / (long double)energyPerMile) / (long double)speed) * 1_hour;
            }
            break;
         case AircraftState::StartCharging:
            _totalCharges++;
            _state = AircraftState::Charging;
         case AircraftState::Charging:
            _totalAttemptedChargingTime += operationTime;
            if(chargeStation.charge(id))
            {
               _totalChargingTime += operationTime;
               _batteryLevel += (chargeTime / operationTime) * batteryCapacity;
            }

            if(_batteryLevel >= batteryCapacity)
            {
               _batteryLevel = batteryCapacity;
               _state = AircraftState::FinishCharging;
               return (((long double)_batteryLevel / energyPerMile) / speed) * 1_hour;
            }
            else
            {
               return (((long double)batteryCapacity - _batteryLevel) / batteryCapacity) * chargeTime;
            }
            break;
         case AircraftState::Initialize:
         default:
            _state = AircraftState::StartFlying;
            return (long double)((_batteryLevel / energyPerMile) / speed) * 1_hour;
      }

      return 0_sec;
   }

   ////////////////////////////////////////////////////////////////////////////////

} // namespace aircrafts