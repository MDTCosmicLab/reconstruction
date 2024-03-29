#include "MdtHit.h"

MdtHit::MdtHit(uint32_t bcid, uint32_t tdc, uint32_t channel,
	       uint32_t coarse, uint32_t fine, bool isLeading) :
  m_bcid(bcid),
  m_tdc(tdc),
  m_channel(channel),
  m_coarse(coarse),
  m_fine(fine),
  m_isLeading(isLeading)
{
  m_time=coarse*25.+fine*25./32.;
  /// set initially the charge to zero
  m_charge=0.0;
}

MdtHit::~MdtHit()
{

}

void MdtHit::setIdentifier(uint32_t chamber, uint32_t layer, uint32_t tube)
{
  m_chamber=chamber;
  m_layer=layer;
  m_tube=tube;
}
