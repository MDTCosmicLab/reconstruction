#ifndef EVENTDECODER_H
#define EVENTDECODER_H

#include <vector>

#include "MdtAmtReadout.h"
#include "MdtHit.h"

class EventDecoder
{

 public:
  EventDecoder();
  ~EventDecoder();

 private:

  MdtAmtReadOut m_amtReadout;
  
  std::vector<MdtHit*> m_eventHits;
  
};

#endif
