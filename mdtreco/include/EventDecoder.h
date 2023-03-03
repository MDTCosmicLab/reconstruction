#ifndef EVENTDECODER_H
#define EVENTDECODER_H

#include <vector>

#include "EventBuilder.h"
#include "MdtAmtReadOut.h"
#include "MdtHit.h"

class EventDecoder
{

 public:
  EventDecoder();
  ~EventDecoder();

  void decodeEvent(Event* event);
  
 private:

  MdtAmtReadOut m_amtReadOut;
  
  std::vector<MdtHit*> m_eventHits;
  
};

#endif
