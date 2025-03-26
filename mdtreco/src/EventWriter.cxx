#include "EventWriter.h"

#include <iostream>
#include <string>

EventWriter::EventWriter(std::string fileName)
{

  m_outFile = new TFile(fileName.c_str(),"RECREATE");
  bookTree();

  std::string hname;
  for (unsigned int i=0 ; i<8 ; i++) {
    for (unsigned int j=i+1 ; j<9 ; j++ ) {
      std::string l1 = std::to_string(i+1);
      std::string l2 = std::to_string(j+1);
      hname = "tubediff_"+l1+"_"+l2;
      m_tubeDiff[i][j]=new TH1F(hname.c_str(),hname.c_str(),34,-17.,17.);
    }
  }

  
}

void EventWriter::fillHistos()
{

  //  std::cout << ">>>>> in fillHistos " <<  m_tube.size() << std::endl;
  for ( unsigned int il=1 ; il<=8 ; il++ )  {
    for ( unsigned int jl=il+1 ; jl<=9 ; jl++ )  {
      for (unsigned int ih=0 ; ih<m_tube.size() ; ih++)  {
	if ( (m_leading.at(ih)!=1) || (m_charge.at(ih)<40) || (m_charge.at(ih)>250.) || (m_time.at(ih)<700)
	     || (m_time.at(ih)>1600) ) continue;
	unsigned int layer1 = (m_chamber.at(ih)-1)*3+m_layer.at(ih);
	if (layer1==il) {
	  for (unsigned int jh=0 ; jh<m_tube.size() ; jh++)  {
	    if ( (m_leading.at(jh)!=1) || (m_charge.at(jh)<40) || (m_charge.at(jh)>250.) || (m_time.at(jh)<700)
	     || (m_time.at(jh)>1600)) continue;
	    unsigned int layer2 = (m_chamber.at(jh)-1)*3+m_layer.at(jh);
	    if (layer2==jl) {
	      m_tubeDiff[il-1][jl-1]->Fill(1.*( ((int) m_tube.at(ih))-((int) m_tube.at(jh))));
	    }
	  }
	}
      }
    }
  }
}

TH1F* EventWriter::getHisto(unsigned int i, unsigned int j) {
  //std::cout << m_tubeDiff[i-1][j-1]->GetEntries() << std::endl;
  return m_tubeDiff[i-1][j-1];
}


EventWriter::~EventWriter()
{
  m_tree->Write();

  m_outFile->Close();
  //std::cout << "Closing output file" << std::endl;
}

void EventWriter::fillTree(uint32_t evNum , std::vector<MdtHit*>& hits)
{

  m_eventNumber = evNum;
  //  std::cout << "Filling the tree with hits: " << hits.size() << std::endl;
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

  fillHistos();
  
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
