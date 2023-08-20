//!
//! @file   example.test.cpp
//! @date   08/19/2023
//! @author Kaleb C
//!
//! @brief
//!
//!
//!

#include "example.hpp"

#include "gtest/gtest.h"

namespace example_test
{

   ////////////////////////////////////////////////////////////////////////////////

   TEST(example, compiles)
   {
      EXPECT_TRUE(true);
   }

   TEST(example, addition_1)
   {
      EXPECT_EQ(10, example::addition(4, 6));
   }

   ////////////////////////////////////////////////////////////////////////////////

} // namespace example_test