//!
//! @file   time.test.cpp
//! @date   08/20/2023
//! @author Kaleb Cole (kalebcole95@gmail.com)
//!
//! @brief
//!
//!
//!

#include "time.hpp"

#include "gtest/gtest.h"

////////////////////////////////////////////////////////////////////////////////

TEST(time, compiles)
{
   EXPECT_TRUE(true);
}

////////////////////////////////////////////////////////////////////////////////

TEST(time, seconds_10)
{
   EXPECT_EQ(10_sec, Time(10));
}

TEST(time, seconds_30)
{
   EXPECT_EQ(30_sec, Time(30));
}

TEST(time, seconds_60)
{
   EXPECT_EQ(60_sec, Time(60));
}

TEST(time, seconds_230)
{
   EXPECT_EQ(230_sec, Time(230));
}

////////////////////////////////////////////////////////////////////////////////

TEST(time, minutes_60)
{
   EXPECT_EQ(60_sec, 1_min);
}

TEST(time, minutes_60_2)
{
   EXPECT_EQ(60_sec, 1.0_min);
}

TEST(time, minutes_45)
{
   EXPECT_EQ(45_sec, 0.75_min);
}

////////////////////////////////////////////////////////////////////////////////

TEST(time, hours_1)
{
   EXPECT_EQ(3600_sec, 1_hour);
}

TEST(time, hours_1_2)
{
   EXPECT_EQ(3600_sec, 1.0_hour);
}

TEST(time, hours_25)
{
   EXPECT_EQ(150_min, 2.5_hour);
}

////////////////////////////////////////////////////////////////////////////////

TEST(time, add_60)
{
   EXPECT_EQ(60_sec, 20_sec + 40_sec);
}

TEST(time, add_60_2)
{
   EXPECT_EQ(60_sec, 15_sec + 0.75_min);
}

TEST(time, sub_60)
{
   EXPECT_EQ(60_sec, 90_sec - 0.5_min);
}

TEST(time, incr_60)
{
   Time time = 45_sec;
   time += 15_sec;

   EXPECT_EQ(60_sec, time);
}

////////////////////////////////////////////////////////////////////////////////