//!
//! @file   stats.test.cpp
//! @date   08/25/2023
//! @author Kaleb Cole (kalebcole95@gmail.com)
//!
//! @brief
//!
//!
//!

#include "stats.hpp"

#include "gtest/gtest.h"

#include "aircrafts/aircrafts.hpp"
#include "chargers/charger.hpp"
#include "units/time.hpp"

////////////////////////////////////////////////////////////////////////////////

TEST(stats, compiles)
{
   EXPECT_TRUE(true);
}

////////////////////////////////////////////////////////////////////////////////

TEST(stats, alpha_1)
{
   aircrafts::AlphaAircraft *alphacraft = new aircrafts::AlphaAircraft(0);
   statistics::AircraftStats stats(alphacraft);
   chargers::ChargeStation chargeStation(3);

   alphacraft->operate(chargeStation, 0_sec);
   alphacraft->operate(chargeStation, 1_hour + 2_min + 3_sec + 4_ms);

   stats.addData(alphacraft);
   stats.printStatistics();
}

////////////////////////////////////////////////////////////////////////////////