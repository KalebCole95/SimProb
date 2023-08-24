//!
//! @file   charger.cpp
//! @date   08/22/2023
//! @author Kaleb Cole (kalebcole95@gmail.com)
//!
//! @brief
//!
//!
//!

#include "charger.hpp"

#include <algorithm>

namespace chargers
{
   bool chargerArray::charge(unsigned int id)
   {
      std::list<unsigned int>::iterator it = std::find(_chargingQueue.begin(), _chargingQueue.end(), id);

      if(it == _chargingQueue.end())
      {
         _chargingQueue.push_back(id);
      }

      if(std::distance(_chargingQueue.begin(), it) <= chargerCount)
      {
         return true;
      }

      return false;
   }

   void chargerArray::leave(unsigned int id)
   {
      _chargingQueue.remove(id);
   }

   unsigned int chargerArray::getPos(unsigned int id)
   {
      std::list<unsigned int>::iterator it = std::find(_chargingQueue.begin(), _chargingQueue.end(), id);
      return std::distance(_chargingQueue.begin(), it);
   }

   unsigned int chargerArray::queueSize()
   {
      return _chargingQueue.size();
   }

} // namespace chargers