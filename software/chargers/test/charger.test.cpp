//!
//! @file   charger.test.cpp
//! @date   08/24/2023
//! @author Kaleb Cole (kalebcole95@gmail.com)
//!
//! @brief
//!
//!
//!

#include "charger.hpp"

#include "gtest/gtest.h"

////////////////////////////////////////////////////////////////////////////////

TEST(chargers, compiles)
{
   EXPECT_TRUE(true);
}

////////////////////////////////////////////////////////////////////////////////

TEST(chargers, size_1)
{
   chargers::ChargeStation chargers(3);

   chargers.charge(0);

   EXPECT_EQ(1, chargers.queueSize());
}

TEST(chargers, size_3)
{
   chargers::ChargeStation chargers(3);

   chargers.charge(0);
   chargers.charge(1);
   chargers.charge(2);

   EXPECT_EQ(3, chargers.queueSize());
}

TEST(chargers, size_25)
{
   chargers::ChargeStation chargers(3);

   for(size_t ii = 0; ii < 25; ii++)
   {
      chargers.charge(ii);
   }

   EXPECT_EQ(25, chargers.queueSize());
}

////////////////////////////////////////////////////////////////////////////////

TEST(chargers, pos_0_1)
{
   chargers::ChargeStation chargers(3);

   chargers.charge(0);

   EXPECT_EQ(0, chargers.getPos(0));
}

TEST(chargers, pos_1_5)
{
   chargers::ChargeStation chargers(3);

   for(size_t ii = 0; ii < 5; ii++)
   {
      chargers.charge(ii);
   }

   EXPECT_EQ(1, chargers.getPos(1));
}

TEST(chargers, pos_5_10)
{
   chargers::ChargeStation chargers(3);

   for(size_t ii = 0; ii < 10; ii++)
   {
      chargers.charge(ii);
   }

   EXPECT_EQ(5, chargers.getPos(5));
}

////////////////////////////////////////////////////////////////////////////////

TEST(chargers, isCharging_0)
{
   chargers::ChargeStation chargers(3);

   EXPECT_TRUE(chargers.charge(0));
}

TEST(chargers, isCharging_1)
{
   chargers::ChargeStation chargers(3);

   chargers.charge(0);

   EXPECT_TRUE(chargers.charge(1));
}

TEST(chargers, isCharging_2)
{
   chargers::ChargeStation chargers(3);

   chargers.charge(0);
   chargers.charge(1);

   EXPECT_TRUE(chargers.charge(2));
}

TEST(chargers, isCharging_3)
{
   chargers::ChargeStation chargers(3);

   chargers.charge(0);
   chargers.charge(1);
   chargers.charge(2);

   EXPECT_FALSE(chargers.charge(3));
}

TEST(chargers, isCharging_4)
{
   chargers::ChargeStation chargers(3);

   chargers.charge(0);
   chargers.charge(1);
   chargers.charge(2);
   chargers.charge(3);

   EXPECT_FALSE(chargers.charge(4));
}

////////////////////////////////////////////////////////////////////////////////

TEST(chargers, duplicates_1)
{
   chargers::ChargeStation chargers(3);

   for(size_t ii = 0; ii < 5; ii++)
   {
      chargers.charge(0);
   }

   EXPECT_EQ(1, chargers.queueSize());
}

TEST(chargers, duplicates_2)
{
   chargers::ChargeStation chargers(3);

   for(size_t ii = 0; ii < 20; ii++)
   {
      chargers.charge(ii % 2);
   }

   EXPECT_EQ(2, chargers.queueSize());
}

////////////////////////////////////////////////////////////////////////////////