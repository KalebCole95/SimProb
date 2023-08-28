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
#include <vector>

#include "aircrafts/aircrafts.hpp"
#include "statistics/stats.hpp"
#include "units/time.hpp"

constexpr unsigned int chargerCount = 1;
constexpr unsigned int aircraftCount = 20;
constexpr Time totalRunTime = 3_hour;

int main()
{
   std::vector<aircrafts::AircraftBase *> aircraftVector;

   std::srand(std::time(nullptr));

   std::cout << "Generating aircrafts..." << std::endl;
   for(size_t ii = 0; ii < aircraftCount; ii++)
   {
      switch(std::rand() % 5)
      {
         case 0:
            aircraftVector.push_back(new aircrafts::AlphaAircraft(ii));
            std::cout << "   Alpha" << std::endl;
            break;
         case 1:
            aircraftVector.push_back(new aircrafts::BravoAircraft(ii));
            std::cout << "   Bravo" << std::endl;
            break;
         case 2:
            aircraftVector.push_back(new aircrafts::CharlieAircraft(ii));
            std::cout << "   Charlie" << std::endl;
            break;
         case 3:
            aircraftVector.push_back(new aircrafts::DeltaAircraft(ii));
            std::cout << "   Delta" << std::endl;
            break;
         case 4:
         default:
            aircraftVector.push_back(new aircrafts::EchoAircraft(ii));
            std::cout << "   Echo" << std::endl;
            break;
      }
   }

   chargers::ChargeStation chargeStation(3);
   Time totalTimeRemaining = totalRunTime;
   Time nextOperationTime = totalRunTime;
   Time currentOperationTime = 0_sec;

   std::cout << "Starting Simulation..." << std::endl;
   while(totalTimeRemaining > 0_sec)
   {
      for(size_t ii = 0; ii < aircraftCount; ii++)
      {
         nextOperationTime = std::min(nextOperationTime,
                                      aircraftVector[ii]->operate(chargeStation, currentOperationTime));
      }

      totalTimeRemaining -= currentOperationTime < totalTimeRemaining ? currentOperationTime : totalTimeRemaining;
      currentOperationTime = nextOperationTime;
      nextOperationTime = totalRunTime;
   }

   std::cout << "Compiling Results..." << std::endl;

   statistics::AircraftStats alphaStats(new aircrafts::AlphaAircraft(0));
   statistics::AircraftStats bravoStats(new aircrafts::BravoAircraft(0));
   statistics::AircraftStats charlieStats(new aircrafts::CharlieAircraft(0));
   statistics::AircraftStats deltaStats(new aircrafts::DeltaAircraft(0));
   statistics::AircraftStats echoStats(new aircrafts::EchoAircraft(0));


   for(size_t ii = 0; ii < aircraftCount; ii++)
   {
      switch(aircraftVector[ii]->type)
      {
         case aircrafts::AircraftType::Alpha:
            alphaStats.addData(aircraftVector[ii]);
            break;
         case aircrafts::AircraftType::Bravo:
            bravoStats.addData(aircraftVector[ii]);
            break;
         case aircrafts::AircraftType::Charlie:
            charlieStats.addData(aircraftVector[ii]);
            break;
         case aircrafts::AircraftType::Delta:
            deltaStats.addData(aircraftVector[ii]);
            break;
         case aircrafts::AircraftType::Echo:
            echoStats.addData(aircraftVector[ii]);
            break;
         default:
            break;
      }
   }

   std::cout << "Printing Results..." << std::endl;
   alphaStats.printStatistics();
   bravoStats.printStatistics();
   charlieStats.printStatistics();
   deltaStats.printStatistics();
   echoStats.printStatistics();

   std::cout << "Simulation Complete" << std::endl;
}