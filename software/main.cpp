//!
//! @file   main.cpp
//! @date   08/24/2023
//! @author Kaleb Cole (kalebcole95@gmail.com)
//!
//! @brief
//!
//!
//!

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "aircrafts/aircrafts.hpp"
#include "units/time.hpp"

constexpr unsigned int chargerCount = 3;
constexpr unsigned int aircraftCount = 20;
constexpr Time totalRunTime = 3_hour;

int main()
{
   aircrafts::AircraftBase **aircraftArray = new aircrafts::AircraftBase *[aircraftCount];

   std::srand(std::time(nullptr));

   std::cout << "Generating aircrafts..." << std::endl;
   for(size_t ii = 0; ii < aircraftCount; ii++)
   {
      switch(std::rand() % 5)
      {
         case 0:
            aircraftArray[ii] = new aircrafts::AlphaAircraft(ii);
            std::cout << "   Alpha" << std::endl;
            break;
         case 1:
            aircraftArray[ii] = new aircrafts::BravoAircraft(ii);
            std::cout << "   Bravo" << std::endl;
            break;
         case 2:
            aircraftArray[ii] = new aircrafts::CharlieAircraft(ii);
            std::cout << "   Charlie" << std::endl;
            break;
         case 3:
            aircraftArray[ii] = new aircrafts::DeltaAircraft(ii);
            std::cout << "   Delta" << std::endl;
            break;
         case 4:
         default:
            aircraftArray[ii] = new aircrafts::EchoAircraft(ii);
            std::cout << "   Echo" << std::endl;
            break;
      }
   }

   chargers::ChargeStation chargeStation(3);
   Time totalTimeRemaining = totalRunTime;
   Time nextOperationTime = totalRunTime;
   Time currentOperationTime = totalRunTime;

   std::cout << "Starting Simulation" << std::endl;
   while(totalTimeRemaining > 0_sec)
   {
      for(size_t ii = 0; ii < aircraftCount; ii++)
      {
         nextOperationTime = std::min(nextOperationTime,
                                      aircraftArray[ii]->operate(chargeStation, currentOperationTime));
      }

      totalTimeRemaining -= currentOperationTime;
      currentOperationTime = nextOperationTime;
      nextOperationTime = totalRunTime;
   }
   std::cout << "Simulation Complete" << std::endl;
}