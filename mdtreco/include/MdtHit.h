#ifndef MDTHIT_H
#define MDTHIT_H

class MdtHit
{

 public:

  MdtHit(uint32_t tdc, uint32_t channel, uint32_t tdcCounts, uint32_t adcCounts, bool isLeading);

  ~MdtHit();

  uint32_t tdc() {return m_tdc;}
  uint32_t channel() {return m_channel;}
  uint32_t tdcCounts() {return m_tdcCounts;}
  uint32_t adcCounts() {return m_adcCounts;}
  bool isLeading() {return m_isLeading;}
  
 private:

  uint32_t m_tdc;
  uint32_t m_channel;
  uint32_t m_leadingCounts;
  uint32_t m_trailingCounts;
  bool     m_isLeading;
};

#endif
