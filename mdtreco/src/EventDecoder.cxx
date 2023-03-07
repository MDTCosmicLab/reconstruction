#include "EventDecoder.h"

#include <iostream>

EventDecoder::EventDecoder()
{

}

EventDecoder::~EventDecoder()
{

}

void EventDecoder::decodeEvent(Event* event)
{

  /// clear the event
  for ( unsigned int i=0 ; i<m_eventHits.size() ; ++i ) delete m_eventHits[i]; 
  m_eventHits.clear();
  
  /// loop on the TDC
  for ( auto it : *event ) {

    uint32_t tdcId = it.first;

    for ( unsigned int i=0 ; i<it.second.size() ; ++i ) {

      uint32_t dw = it.second[i];
      m_amtReadOut.decodeWord(dw);
      
      if (m_amtReadOut.is_TSM() ) {

	uint16_t chan   = m_amtReadOut.channel();
	uint16_t coarse = m_amtReadOut.coarse();
	uint16_t fine   = m_amtReadOut.fine();
	bool leading    = m_amtReadOut.isLeading();
	
	std::cout << ">>> Single Meas: " << std::hex << dw << std::dec
		  << " chan: " << chan << " coarse: "
		  << coarse << " fine: " << fine << " leading: " << leading << std::endl;

	MdtHit* hit = new MdtHit(tdcId,chan,coarse,fine,leading);
	m_eventHits.push_back(hit);
      }
      
    }
    
  }

  
}
