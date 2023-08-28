//!
//! @file   time.cpp
//! @date   08/25/2023
//! @author Kaleb Cole (kalebcole95@gmail.com)
//!
//! @brief
//!
//!
//!

#include "time.hpp"

std::ostream &operator<<(std::ostream &output, const Time &rhs)
{
   Time overflow = rhs;

   output << (unsigned)(overflow / 1_hour) << "h ";
   overflow = overflow % 1_hour;
   output << (unsigned)(overflow / 1_min) << "m ";
   overflow = overflow % 1_min;
   output << (unsigned)(overflow / 1_sec) << "s ";
   overflow = overflow % 1_sec;
   output << overflow.milliseconds << "ms";

   return output;
}