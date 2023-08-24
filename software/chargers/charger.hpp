//!
//! @file   charger.hpp
//! @date   08/22/2023
//! @author Kaleb Cole (kalebcole95@gmail.com)
//!
//! @brief
//!
//!
//!

#ifndef _CHARGERS_CHARGER_HPP_
#define _CHARGERS_CHARGER_HPP_

#include <list>

namespace chargers
{
   class chargerArray
   {
   public:
      chargerArray(unsigned int chargerCount)
            : chargerCount(chargerCount)
      {
      }

      bool charge(unsigned int id);
      void leave(unsigned int id);

      unsigned int getPos(unsigned int id);
      unsigned int queueSize();

      const unsigned int chargerCount;

   protected:
      std::list<unsigned int> _chargingQueue = {};
   };
} // namespace chargers

#endif // _CHARGERS_CHARGER_HPP_