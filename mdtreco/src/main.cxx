#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "StreamReader.h"
#include "EventDecoder.h"
#include "EventWriter.h"

#include "TROOT.h"
#include "TRint.h"
#include "TH1F.h"

int main(int argc, char** argv)
{

  std::string inputDir="/mdt/data";
  unsigned int nevents=1000000;  
  std::string runNum;
  if (argc>=4) {
    nevents = atoi(argv[1]);
    std::string s1(argv[2]);
    std::string s2(argv[3]);
    inputDir=s2+"/run"+s1;
    runNum=s1;
  }    
  else if (argc==3) {
    nevents = atoi(argv[1]);
    std::string s1(argv[2]);  
    //inputDir="/mdt/data/run"+s1;
    inputDir="/mdt/data/run"+s1;
    runNum=s1;
  }
  else if (argc==2) {
    nevents = atoi(argv[1]);
  }
  else {
    inputDir=inputDir+"/run1";
    runNum="1"; 
  }

  if (nevents==0) nevents=10000000;
  unsigned int nperblock=50;
  std::cout << "Reading data from dir: " << inputDir << std::endl;
  std::cout << "Please wait...." << std::endl;
  /// tdc event shifts
  int shifts[6]={0,0,0,0,0,0};
  int bestShifts[6]={0,0,0,0,0,0};
  float bestRMS[6]={999.,999.,999.,999.,999.,999.};

  for ( unsigned int itdc=0 ; itdc<6 ; ++itdc ) {

    /// run the pre-analysis to re-align the tdc
    if ( itdc==2 || itdc==3 ) continue; 
    
    for (int sh=-12 ; sh<12 ; sh++) {
      /// test a shift
      shifts[itdc]=sh;
      StreamReader* stream_tmp = new StreamReader(inputDir);
      EventDecoder* decoder_tmp = new EventDecoder();
      std::string outFile_tmp="reco_tmp.root";
      EventWriter* writer_tmp = new EventWriter(outFile_tmp.c_str());

      int j=0;
      while (j<50) {
	j++;
	/// get the shift for each tdc
	bool readEvents = stream_tmp->readBlock(nperblock,shifts);
	
	if ( !readEvents ) {
	  break;
	}
	
	/// get the events from the event builder
	EventMap emap;
	stream_tmp->getEvents(emap);
	
	/// loop on the events and decode them
	for ( auto it : emap ) {
	  decoder_tmp->decodeEvent(it.second);
	  writer_tmp->fillTree(it.first,decoder_tmp->getEventHits());
	 	  
	}   
      }

      
      float rms=9999.;
      if (itdc==0 || itdc==1) { 
	TH1F* h = writer_tmp->getHisto(3,4);
	rms = h->GetRMS();
	///std::cout << "AAAAAA " << itdc<< " " << rms << " " << sh << std::endl;
      }
      else if  (itdc==4 || itdc==5) {
	TH1F* h = writer_tmp->getHisto(6,7);
	rms = h->GetRMS();
	///std::cout << "AAAAAA " << itdc << " " << rms << " " << sh << std::endl;
      }
      
      if (rms<bestRMS[itdc]) {
	bestRMS[itdc]=rms;
	bestShifts[itdc]=sh;
	//std::cout << itdc<< " " << rms << " " << sh << std::endl;
      }
      
      delete writer_tmp;
      delete stream_tmp;
      delete decoder_tmp;

    }
    
  }

  for (unsigned int i=0 ; i<6 ; i++ ) {
    std::cout << bestShifts[i] << std::endl;
  }
  
  std::cout << "============================================================" << std::endl;
  int i=0;
  unsigned int nblocks=nevents/nperblock;
  std::cout << nblocks << std::endl;
  unsigned int ievent=0;
  StreamReader stream(inputDir);
  EventDecoder decoder;
  std::string outFile="reco_run"+runNum+".root";
  EventWriter writer(outFile.c_str());

  
  while (i<nblocks) {
    i++;
    //std::cout << std::endl;
    //std::cout << ">>>>>>>>>>>>>>>>>>>>>>> Reading a new block of events ! " << std::endl;
    bool readEvents = stream.readBlock(nperblock,bestShifts);

    if ( !readEvents ) {
      std::cout << ">>>>>>>>>>>>>>>>>>>>> Input is finished: terminating ! nevents processed: " <<  ievent << std::endl;
      return 0;
    }
    
    /// get the events from the event builder
    EventMap emap;
    stream.getEvents(emap);

    /// loop on the events and decode them
    for ( auto it : emap ) {
      //      std::cout << "Decoding event number " << it.first << std:: endl;
      decoder.decodeEvent(it.second);
      writer.fillTree(it.first,decoder.getEventHits());

      ievent++;

      if ( ievent%1000==0 ) {
	    std::cout << "Events processed: " << ievent << std::endl;
      }
      
    }

    
  }

  std::cout << ">>>>>>>>>>>>>>>>>>>>> Terminating ! nevents processed: " <<  ievent << std::endl;
  
  return 0;
}
