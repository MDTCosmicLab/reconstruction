#include "EventDecoder.h"

#include <iostream>
#include <utility>

EventDecoder::EventDecoder()
{
}

EventDecoder::~EventDecoder()
{
}

void EventDecoder::decodeEvent(Event *event)
{

  // map between the channel number and the leading hit pointer
  // valid for each tdc
  std::map<uint16_t, MdtHit *> leadingHitMap;
  /// clear the event
  for (unsigned int i = 0; i < m_eventHits.size(); ++i)
    delete m_eventHits[i];
  m_eventHits.clear();

  /// loop on the TDC
  for (auto it : *event)
  {

    uint32_t tdcId = it.first;
    uint32_t bcid = 0;
    leadingHitMap.clear();

    for (unsigned int i = 0; i < it.second.size(); ++i)
    {

      uint32_t dw = it.second[i];
      m_amtReadOut.decodeWord(dw);
      if (m_amtReadOut.is_BOT())
      {
        bcid = m_amtReadOut.bcId();
      }
      else if (m_amtReadOut.is_TSM())
      {

        uint16_t chan = m_amtReadOut.channel();
        uint16_t coarse = m_amtReadOut.coarse();
        uint16_t fine = m_amtReadOut.fine();
        bool leading = m_amtReadOut.isLeading();
        //if ( coarse*25.+fine*25./32. > 3000.) {
        //  	std::cout << ">>> Single Meas: 0x" << std::hex << dw << std::dec
        //		  << " chan: " << chan << " coarse: "
        //		  << coarse << " fine: " << fine << " leading: " << leading << " time: " <<  coarse*25.+fine*25./32. << std::endl;
        //}

        uint16_t chamber, layer, tube;
        m_cabling.getIdentifier(tdcId, chan, chamber, layer, tube);

        MdtHit *hit = new MdtHit(bcid, tdcId, chan, coarse, fine, leading);
        hit->setIdentifier(chamber, layer, tube);
        m_eventHits.push_back(hit);
        // if it's a leading edge add it to the map
        if (leading && leadingHitMap.find(chan) == leadingHitMap.end())
        {
          leadingHitMap.insert(std::make_pair(chan, hit));
        }
        // if it's a trailing edge hit look for the corresponding leading and set the charge
        else if (!leading)
        {
          std::map<uint16_t, MdtHit *>::iterator itHit = leadingHitMap.find(chan);
          if (itHit != leadingHitMap.end())
          {
            float charge = hit->time() - (*itHit).second->time();
            if (charge < 0)
            {
              //      std::cout << ">>> ERROR: found trailing edge with time smaller than leading edge" << std::endl;
            }
            else
            {
              (*itHit).second->setCharge(charge);
            }
          }
        }
      }
    }
  }
}
