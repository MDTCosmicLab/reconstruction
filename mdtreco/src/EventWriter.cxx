#include "EventWriter.h"

#include <iostream>

EventWriter::EventWriter(std::string fileName)
{

  m_outFile = new TFile(fileName.c_str(),"RECREATE");
  bookTree();
  
}

EventWriter::~EventWriter()
{
  m_tree->Write();

  m_outFile->Close();
  
}

void EventWriter::fillTree(uint32_t evNum , std::vector<MdtHit*>& hits)
{

  m_eventNumber = evNum;
  std::cout << "Filling the tree with hits: " << hits.size() << std::endl;
  unsigned int nleading=0;

  for ( auto hit : hits ) {

    m_bcid.push_back(hit->bcid());
    m_tdc.push_back(hit->tdc());
    m_channel.push_back(hit->channel());
    m_coarse.push_back(hit->coarse());
    m_fine.push_back(hit->fine());
    m_chamber.push_back(hit->chamber());
    m_layer.push_back(hit->layer());
    m_tube.push_back(hit->tube());
    m_time.push_back(hit->time());
    m_charge.push_back(hit->charge());
    m_leading.push_back(hit->isLeading());
    if (hit->isLeading() ) nleading++;

    

  }

  m_nhits=nleading;
  
  m_tree->Fill();
  clearTree();
}

void EventWriter::bookTree()
{

  m_tree=new TTree("mdt","Analysis of the MDT data");

  m_tree->Branch("eventNumber",&m_eventNumber);
  m_tree->Branch("nhits",&m_nhits);
  m_tree->Branch("bcid",&m_bcid);
  m_tree->Branch("tdc",&m_tdc);
  m_tree->Branch("channel",&m_channel);
  m_tree->Branch("coarse",&m_coarse);
  m_tree->Branch("fine",&m_fine);
  m_tree->Branch("chamber",&m_chamber);
  m_tree->Branch("layer",&m_layer);
  m_tree->Branch("tube",&m_tube);
  m_tree->Branch("time",&m_time);
  m_tree->Branch("charge",&m_charge);
  m_tree->Branch("leading",&m_leading);

}

void EventWriter::clearTree()
{
  m_eventNumber=0;
  m_nhits=0;
  m_bcid.clear();
  m_tdc.clear();
  m_channel.clear();
  m_coarse.clear();
  m_fine.clear();
  m_chamber.clear();
  m_layer.clear();
  m_tube.clear();
  m_time.clear();  
  m_charge.clear();  
  m_leading.clear();  
}
