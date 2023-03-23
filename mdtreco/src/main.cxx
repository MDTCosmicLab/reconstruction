#include <iostream>
#include <vector>
#include <string>

#include "StreamReader.h"
#include "EventDecoder.h"
#include "EventWriter.h"

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

  std::cout << "Reading data from dir: " << inputDir << std::endl;

  StreamReader stream(inputDir);
  EventDecoder decoder;
  std::string outFile="reco_run"+runNum+".root";
  EventWriter writer(outFile.c_str());

  int i=0;
  unsigned int nblocks=nevents/10;
  std::cout << nblocks << std::endl;
  while (i<nblocks) {
    i++;
    stream.readBlock(10);
    
    //std::cout << "Completed events: " << stream.completedEvents() << std::endl;
    
    /// get the events from the event builder
    EventMap emap;
    stream.getEvents(emap);
    
    /// loop on the events and decode them
    for ( auto it : emap ) {
      std::cout << "Decoding event number " << it.first << std:: endl;
      decoder.decodeEvent(it.second);
      writer.fillTree(it.first,decoder.getEventHits());
    }

    
  }
  
  return 0;
}
