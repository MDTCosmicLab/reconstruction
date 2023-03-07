#ifndef EVENTWRITER_H
#define EVENTWRITER_H

#include "TTree.h"
#include <string>
#include <stdint.h>

class EventWriter
{

 public:

  EventWriter(std::string fileName);
  ~EventWriter();

  void bookTree();
  void clearTree();
    
 private:

  /// tree pointer
  TTree* m_tree;

  /// tree variables
  uint32_t m_eventNumber;
  std::vector<uint32_t> m_tdcId;
  std::vector<uint32_t> m_channel;
  std::vector<uint32_t> m_coarse;
  std::vector<uint32_t> m_fine;
  std::vector<float>    m_time;
  
};



#endif
