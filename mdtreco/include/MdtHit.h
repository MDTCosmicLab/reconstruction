#ifndef MDTHIT_H
#define MDTHIT_H

#include <stdint.h>

class MdtHit
{

 public:

  MdtHit(uint32_t bcid, uint32_t tdc, uint32_t channel,
	 uint32_t coarse, uint32_t fine, bool isLeading);

  ~MdtHit();

  uint32_t bcid()    {return m_bcid;}
  uint32_t tdc()     {return m_tdc;}
  uint32_t channel() {return m_channel;}
  uint32_t coarse()  {return m_coarse;}
  uint32_t fine()    {return m_fine;}
  uint32_t chamber() {return m_chamber;}
  uint32_t layer()   {return m_layer;}
  uint32_t tube()    {return m_tube;}

  float time()   {return m_time;}
  float charge() {return m_charge;}
  bool isLeading() {return m_isLeading;}

  /// set the asd charge 
  void setCharge(float charge) {m_charge=charge;}
  void setIdentifier(uint32_t chamber, uint32_t layer, uint32_t tube);
  
 private:

  uint32_t m_bcid;
  uint32_t m_tdc;
  uint32_t m_channel;
  uint32_t m_coarse;
  uint32_t m_fine;
  uint32_t m_chamber;
  uint32_t m_layer;
  uint32_t m_tube;
  float m_time;
  float m_charge;
  bool  m_isLeading;
};

#endif
