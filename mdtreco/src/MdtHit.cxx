#include "MdtHit.h"

MdtHit::MdtHit(uint32_t tdc, uint32_t channel, uint32_t tdcCounts, uint32_t adcCounts, bool isLeading) :
  m_tdc(tdc),
  m_channel(channel),
  m_tdcCounts(tdcCounts),
  m_adcCounts(adcCounts),
  m_isLeading(isLeading)
{

}

MdtHit::~MdtHit()
{

}
