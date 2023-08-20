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

////////////////////////////////////////////////////////////////////////////////

class Time
{
public:
   explicit constexpr Time(unsigned long long int seconds = 0)
         : seconds(seconds)
   {
   }

   friend bool operator==(const Time &lhs, const Time &rhs) { return lhs.seconds == rhs.seconds; }
   friend bool operator!=(const Time &lhs, const Time &rhs) { return !(lhs == rhs); }
   friend bool operator<(const Time &lhs, const Time &rhs) { return lhs.seconds < rhs.seconds; }
   friend bool operator<=(const Time &lhs, const Time &rhs) { return (lhs < rhs || lhs == rhs); }
   friend bool operator>(const Time &lhs, const Time &rhs) { return (rhs < lhs); }
   friend bool operator>=(const Time &lhs, const Time &rhs) { return (lhs > rhs || lhs == rhs); }

   friend Time operator+(const Time &lhs, const Time &rhs)
   {
      Time result;
      result.seconds = lhs.seconds + rhs.seconds;
      return result;
   }

   friend Time operator-(const Time &lhs, const Time &rhs)
   {
      Time result;
      result.seconds = lhs.seconds - rhs.seconds;
      return result;
   }

   Time &operator+=(const Time &rhs)
   {
      this->seconds += rhs.seconds;
      return *this;
   }

   Time &operator-=(const Time &rhs)
   {
      this->seconds -= rhs.seconds;
      return *this;
   }

protected:
   unsigned long long seconds;
};

////////////////////////////////////////////////////////////////////////////////

constexpr Time operator""_sec(unsigned long long int seconds)
{
   return Time {seconds};
}

constexpr Time operator""_min(unsigned long long int minutes)
{
   return Time {minutes * 60};
}

constexpr Time operator""_min(long double minutes)
{
   return Time {(unsigned long long int)(minutes * 60)};
}

constexpr Time operator""_hour(unsigned long long int hours)
{
   return Time {hours * 60 * 60};
}

constexpr Time operator""_hour(long double hours)
{
   return Time {(unsigned long long int)(hours * 60 * 60)};
}

////////////////////////////////////////////////////////////////////////////////

#endif // _UNITS_TIME_HPP_
