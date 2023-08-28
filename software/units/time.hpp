//!
//! @file   time.hpp
//! @date   08/20/2023
//! @author Kaleb Cole (kalebcole95@gmail.com)
//!
//! @brief
//!
//!
//!

#ifndef _UNITS_TIME_HPP_
#define _UNITS_TIME_HPP_

#include <cmath>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

class Time
{
public:
   explicit constexpr Time(unsigned long long int milliseconds = 0)
         : milliseconds(milliseconds)
   {
   }

   Time &operator+=(const Time &rhs)
   {
      this->milliseconds += rhs.milliseconds;
      return *this;
   }

   Time &operator-=(const Time &rhs)
   {
      this->milliseconds -= rhs.milliseconds;
      return *this;
   }

   friend bool operator==(const Time &lhs, const Time &rhs) { return lhs.milliseconds == rhs.milliseconds; }
   friend bool operator!=(const Time &lhs, const Time &rhs) { return !(lhs == rhs); }
   friend bool operator<(const Time &lhs, const Time &rhs) { return lhs.milliseconds < rhs.milliseconds; }
   friend bool operator<=(const Time &lhs, const Time &rhs) { return (lhs < rhs || lhs == rhs); }
   friend bool operator>(const Time &lhs, const Time &rhs) { return (rhs < lhs); }
   friend bool operator>=(const Time &lhs, const Time &rhs) { return (lhs > rhs || lhs == rhs); }

   friend Time operator+(const Time &lhs, const Time &rhs)
   {
      Time result(0);
      result.milliseconds = lhs.milliseconds + rhs.milliseconds;
      return result;
   }

   friend Time operator-(const Time &lhs, const Time &rhs)
   {
      Time result(0);
      result.milliseconds = lhs.milliseconds - rhs.milliseconds;
      return result;
   }

   friend long double operator/(const Time &lhs, const Time &rhs)
   {
      return (long double)lhs.milliseconds / (long double)rhs.milliseconds;
   }

   friend Time operator%(const Time &lhs, const Time &rhs)
   {
      Time result(0);
      result.milliseconds = lhs.milliseconds % rhs.milliseconds;
      return result;
   }

   friend Time operator/(const Time &lhs, unsigned int rhs)
   {
      Time result(0);

      if(rhs == 0)
      {
         return result;
      }

      result.milliseconds = lhs.milliseconds / rhs;
      return result;
   }

   friend Time operator*(const unsigned long long lhs, const Time &rhs)
   {
      Time result(0);
      result.milliseconds = lhs * rhs.milliseconds;
      return result;
   }

   friend Time operator*(const long double lhs, const Time &rhs)
   {
      Time result(0);
      // @todo - Implement a better way of accounting for imprecision with floating point math (probably calculating
      // everything in ns and converting back to ms for storage)
      result.milliseconds = std::round(lhs * rhs.milliseconds / 10) * 10;
      return result;
   }
   friend Time operator*(const Time &lhs, const unsigned long long rhs) { return rhs * lhs; }
   friend Time operator*(const Time &lhs, const long double rhs) { return rhs * lhs; }

   friend std::ostream &operator<<(std::ostream &output, const Time &rhs);

protected:
   long long milliseconds;
};

////////////////////////////////////////////////////////////////////////////////

constexpr Time operator""_ms(unsigned long long int milliseconds)
{
   return Time {milliseconds};
}

constexpr Time operator""_sec(unsigned long long int seconds)
{
   return Time {seconds * 1000};
}

constexpr Time operator""_min(unsigned long long int minutes)
{
   return Time {minutes * 60 * 1000};
}

constexpr Time operator""_min(long double minutes)
{
   return Time {(unsigned long long int)(minutes * 60 * 1000)};
}

constexpr Time operator""_hour(unsigned long long int hours)
{
   return Time {hours * 60 * 60 * 1000};
}

constexpr Time operator""_hour(long double hours)
{
   return Time {(unsigned long long int)(hours * 60 * 60 * 1000)};
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////

#endif // _UNITS_TIME_HPP_
