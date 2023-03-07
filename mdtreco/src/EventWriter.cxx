#include "EventWriter.h"

EventWriter::EventWriter(std::string fileName)
{

}

EventWriter::~EventWriter()
{ }

void EventWriter::bookTree()
{

  m_tree=new TTree("mdt","Analysis of the MDT data");

  m_tree->Branch("eventNumber",&m_eventNumber);
  m_tree->Branch("tdc",&m_channel,"tdc/i");
  m_tree->Branch("channel",&m_channel,"channel/i");

}
