//!
//! @file   aircrafts.hpp
//! @date   08/22/2023
//! @author Kaleb Cole (kalebcole95@gmail.com)
//!
//! @brief
//!
//!
//!

#ifndef _AIRCRAFTS_AIRCRAFTS_HPP_
#define _AIRCRAFTS_AIRCRAFTS_HPP_

#include <cstdint>
#include <iostream>

#include "chargers/charger.hpp"
#include "units/time.hpp"

namespace aircrafts
{

   ////////////////////////////////////////////////////////////////////////////////

   enum struct AircraftState : uint8_t
   {
      Initialize,
      StartFlying,
      Flying,
      StartCharging,
      Charging
   };

   enum struct AircraftType : uint8_t
   {
      None,
      Alpha,
      Bravo,
      Charlie,
      Delta,
      Echo
   };

   ////////////////////////////////////////////////////////////////////////////////

   class AircraftBase
   {
   public:
      AircraftBase()
            : AircraftBase(AircraftType::None, 0, 0, 0, 0_sec, 0, 0, 0)
      {
      }

      AircraftBase(const AircraftType type,
                   const unsigned int id,
                   const unsigned int speed,
                   const unsigned int batteryCapacity,
                   const Time chargeTime,
                   const float energyPerMile,
                   const unsigned int passengerCount,
                   const float faultProbability)
            : type(type)
            , id(id)
            , speed(speed)
            , batteryCapacity(batteryCapacity)
            , chargeTime(chargeTime)
            , energyPerMile(energyPerMile)
            , passengerCount(passengerCount)
            , faultProbability(faultProbability)
            , _state(AircraftState::Initialize)
            , _batteryLevel(batteryCapacity)
            , _totalFlights(0)
            , _totalFlightTime(0_sec)
            , _totalCharges(0)
            , _totalChargingTime(0_sec)
            , _totalAttemptedChargingTime(0_sec)
            , _totalFaults(0)
      {
      }

      Time operate(chargers::ChargeStation chargerStation, Time operationTime);

      const AircraftType type;
      const unsigned int id;
      const unsigned int speed;
      const unsigned int batteryCapacity;
      const Time chargeTime;
      const float energyPerMile;
      const unsigned int passengerCount;
      const float faultProbability;

      AircraftState getState() { return _state; }
      unsigned int getBatteryLevel() { return _batteryLevel; }

      unsigned int getTotalFlights() { return _totalFlights; }
      Time getTotalFlightTime() { return _totalFlightTime; }
      unsigned int getTotalCharges() { return _totalCharges; }
      Time getTotalChargingTime() { return _totalChargingTime; }
      Time getTotalAttemptedChargingTime() { return _totalAttemptedChargingTime; }
      unsigned int getTotalFaults() { return _totalFaults; }

   protected:
      AircraftState _state;
      unsigned int _batteryLevel;

      unsigned int _totalFlights;
      Time _totalFlightTime;
      unsigned int _totalCharges;
      Time _totalChargingTime;
      Time _totalAttemptedChargingTime;
      unsigned int _totalFaults;
   };

   ////////////////////////////////////////////////////////////////////////////////

   class AlphaAircraft : public AircraftBase
   {
   public:
      AlphaAircraft(const unsigned int id)
            : AircraftBase(AircraftType::Alpha, id, 120, 320, 0.6_hour, 1.6, 4, 0.25)
      {
      }
   };

   ////////////////////////////////////////////////////////////////////////////////

   class BravoAircraft : public AircraftBase
   {
   public:
      BravoAircraft(const unsigned int id)
            : AircraftBase(AircraftType::Bravo, id, 100, 100, 0.2_hour, 1.5, 5, 0.10)
      {
      }
   };

   ////////////////////////////////////////////////////////////////////////////////

   class CharlieAircraft : public AircraftBase
   {
   public:
      CharlieAircraft(const unsigned int id)
            : AircraftBase(AircraftType::Charlie, id, 160, 220, 0.8_hour, 2.2, 3, 0.05)
      {
      }
   };

   ////////////////////////////////////////////////////////////////////////////////

   class DeltaAircraft : public AircraftBase
   {
   public:
      DeltaAircraft(const unsigned int id)
            : AircraftBase(AircraftType::Delta, id, 90, 120, 0.62_hour, .8, 2, 0.22)
      {
      }
   };

   ////////////////////////////////////////////////////////////////////////////////

   class EchoAircraft : public AircraftBase
   {
   public:
      EchoAircraft(const unsigned int id)
            : AircraftBase(AircraftType::Echo, id, 30, 150, 0.3_hour, 5.8, 2, 0.61)
      {
      }
   };

   ////////////////////////////////////////////////////////////////////////////////

} // namespace aircrafts

#endif // _AIRCRAFTS_AIRCRAFTS_HPP_