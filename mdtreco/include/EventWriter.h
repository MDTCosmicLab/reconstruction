#ifndef EVENTWRITER_H
#define EVENTWRITER_H

#include "TTree.h"
#include "TFile.h"
#include <string>
#include <stdint.h>
#include "MdtHit.h"

class EventWriter
{

 public:

  EventWriter(std::string fileName);
  ~EventWriter();

  void bookTree();
  void clearTree();

  void fillTree(uint32_t evNum, std::vector<MdtHit*>& hits);

  
 private:

  /// file pointer
  TFile* m_outFile;
  /// tree pointer
  TTree* m_tree;

  /// tree variables
  uint32_t m_eventNumber;
  uint32_t m_nhits;
  std::vector<UInt_t> m_bcid;
  std::vector<UInt_t> m_tdc;
  std::vector<UInt_t> m_channel;
  std::vector<UInt_t> m_coarse;
  std::vector<UInt_t> m_fine;
  std::vector<UInt_t> m_chamber;
  std::vector<UInt_t> m_layer;
  std::vector<UInt_t> m_tube;
  std::vector<bool> m_leading;
  std::vector<float>    m_time;
  std::vector<float>    m_charge;
  
};



#endif
