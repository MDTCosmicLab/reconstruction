#include "MdtCabling.h"

#include <iostream>

MdtCabling::MdtCabling()
{

  /// initialize the map: first number is the AMT channel, second number is 10*layer+tube
  
  // first layer
  add(16,11);
  add(18,12);
  add(20,13);
  add(22,14);
  add(23,15);
  add(21,16);
  add(19,17);
  add(17,18);
  // second layer
  add(8,21);
  add(10,22);
  add(12,23);
  add(14,24);
  add(15,25);
  add(13,26);
  add(11,27);
  add(9,28);
  // third layer
  add(0,31);
  add(2,32);
  add(4,33);
  add(6,34);
  add(7,35);
  add(5,36);
  add(3,37);
  add(1,38);
  
}

MdtCabling::~MdtCabling()
{ }

bool MdtCabling::getIdentifier(uint16_t tdc, uint16_t channel, uint16_t& chamber,uint16_t& layer, uint16_t& tube)
{

  if ( tdc>6 || tdc<1 ) {
    std::cout << "ERROR tdc val " << tdc << std::endl;
    return false;
  }

  if ( channel>23 || channel<0 ) {
    std::cout << "ERROR channel val " << channel << std::endl;
    return false;
  }

  chamber=(uint16_t) (tdc)/2+(tdc)%2;

  //  std::cout << tdc << " " << chamber << " " << (tdc-1-(chamber-1)*2) << std::endl;
  
  uint16_t tmp = (uint16_t) m_amtMap.find(channel)->second;
  layer = tmp/10;
  tube = tmp-layer*10 + (tdc-1-(chamber-1)*2)*8;
  
  return true;
}
