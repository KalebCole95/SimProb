//!
//! @file   aircrafts.test.cpp
//! @date   08/24/2023
//! @author Kaleb Cole (kalebcole95@gmail.com)
//!
//! @brief
//!
//!
//!

#include "aircrafts.hpp"

#include "gtest/gtest.h"

#include <cstdlib>
#include <iostream>

#include "chargers/charger.hpp"
#include "units/time.hpp"

////////////////////////////////////////////////////////////////////////////////

TEST(aircrafts, compiles)
{
   EXPECT_TRUE(true);
}

////////////////////////////////////////////////////////////////////////////////

TEST(aircrafts, alpha_1)
{
   chargers::ChargeStation chargeStation(3);
   aircrafts::AlphaAircraft aircraft(0);

   std::srand(0); // Should give repeatable randomizations for the faults

   Time operationTime = 0_sec;

   for(size_t ii = 0; ii < 5; ii++)
   {
      operationTime = aircraft.operate(chargeStation, operationTime);
   }

   EXPECT_EQ(2, aircraft.getTotalFlights());
   EXPECT_EQ(((long double)2 * 320 / 1.6 / 120) * 1_hour, aircraft.getTotalFlightTime());
   EXPECT_EQ(2, aircraft.getTotalCharges());
   EXPECT_EQ(1.2_hour, aircraft.getTotalChargingTime());
   EXPECT_EQ(1.2_hour, aircraft.getTotalAttemptedChargingTime());
   EXPECT_EQ(0, aircraft.getTotalFaults());
}

TEST(aircrafts, bravo_1)
{
   chargers::ChargeStation chargeStation(3);
   aircrafts::BravoAircraft aircraft(0);

   std::srand(0); // Should give repeatable randomizations for the faults

   Time operationTime = 0_sec;

   for(size_t ii = 0; ii < 5; ii++)
   {
      operationTime = aircraft.operate(chargeStation, operationTime);
   }

   EXPECT_EQ(2, aircraft.getTotalFlights());
   EXPECT_EQ(((long double)2 * 100 / 1.5 / 100) * 1_hour, aircraft.getTotalFlightTime());
   EXPECT_EQ(2, aircraft.getTotalCharges());
   EXPECT_EQ(0.4_hour, aircraft.getTotalChargingTime());
   EXPECT_EQ(0.4_hour, aircraft.getTotalAttemptedChargingTime());
   EXPECT_EQ(0, aircraft.getTotalFaults());
}

TEST(aircrafts, charlie_1)
{
   chargers::ChargeStation chargeStation(3);
   aircrafts::CharlieAircraft aircraft(0);

   std::srand(0); // Should give repeatable randomizations for the faults

   Time operationTime = 0_sec;

   for(size_t ii = 0; ii < 5; ii++)
   {
      operationTime = aircraft.operate(chargeStation, operationTime);
   }

   EXPECT_EQ(2, aircraft.getTotalFlights());
   EXPECT_EQ(((long double)2 * 220 / 2.2 / 160) * 1_hour, aircraft.getTotalFlightTime());
   EXPECT_EQ(2, aircraft.getTotalCharges());
   EXPECT_EQ(1.6_hour, aircraft.getTotalChargingTime());
   EXPECT_EQ(1.6_hour, aircraft.getTotalAttemptedChargingTime());
   EXPECT_EQ(0, aircraft.getTotalFaults());
}

TEST(aircrafts, delta_1)
{
   chargers::ChargeStation chargeStation(3);
   aircrafts::DeltaAircraft aircraft(0);

   std::srand(0); // Should give repeatable randomizations for the faults

   Time operationTime = 0_sec;

   for(size_t ii = 0; ii < 5; ii++)
   {
      operationTime = aircraft.operate(chargeStation, operationTime);
   }

   EXPECT_EQ(2, aircraft.getTotalFlights());
   EXPECT_EQ(((long double)2 * 120 / 0.8 / 90) * 1_hour, aircraft.getTotalFlightTime());
   EXPECT_EQ(2, aircraft.getTotalCharges());
   EXPECT_EQ(1.24_hour, aircraft.getTotalChargingTime());
   EXPECT_EQ(1.24_hour, aircraft.getTotalAttemptedChargingTime());
   EXPECT_EQ(0, aircraft.getTotalFaults());
}

TEST(aircrafts, echo_1)
{
   chargers::ChargeStation chargeStation(3);
   aircrafts::EchoAircraft aircraft(0);

   std::srand(0); // Should give repeatable randomizations for the faults

   Time operationTime = 0_sec;

   for(size_t ii = 0; ii < 5; ii++)
   {
      operationTime = aircraft.operate(chargeStation, operationTime);
   }

   EXPECT_EQ(2, aircraft.getTotalFlights());
   EXPECT_EQ(((long double)2 * 150 / 5.8 / 30) * 1_hour, aircraft.getTotalFlightTime());
   EXPECT_EQ(2, aircraft.getTotalCharges());
   EXPECT_EQ(0.6_hour, aircraft.getTotalChargingTime());
   EXPECT_EQ(0.6_hour, aircraft.getTotalAttemptedChargingTime());
   EXPECT_EQ(0, aircraft.getTotalFaults());
}

////////////////////////////////////////////////////////////////////////////////

TEST(aircrafts, echo_2)
{
   chargers::ChargeStation chargeStation(3);
   aircrafts::EchoAircraft aircraft(0);

   std::srand(0); // Should give repeatable randomizations for the faults

   Time operationTime = 0_sec;

   for(size_t ii = 0; ii < 100; ii++)
   {
      operationTime = aircraft.operate(chargeStation, operationTime);
   }

   EXPECT_EQ(25, aircraft.getTotalFaults());
}

////////////////////////////////////////////////////////////////////////////////