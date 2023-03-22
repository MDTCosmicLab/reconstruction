#ifndef MDTCABLING_H
#define MDTCABLING_H

#include <map>

class MdtCabling
{

 public:

  MdtCabling();
  ~MdtCabling();

  /// get chamber , layer and tube from TDC and channel
  bool getIdentifier(uint16_t tdc, uint16_t channel, uint16_t& chamber, uint16_t& layer, uint16_t& tube);
  
 private:

  /// map between the AMT channel number and the tube number with the convention 10*layer+tube
  std::map<uint8_t,uint8_t> m_amtMap;

  void add(uint8_t online, uint8_t offline) {m_amtMap.insert(std::make_pair(online,offline)); }
  
};


#endif
