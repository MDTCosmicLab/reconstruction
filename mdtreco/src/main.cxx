#include <iostream>
#include <vector>
#include <string>

#include "StreamReader.h"
#include "EventDecoder.h"
#include "EventWriter.h"

int main(int argc, char** argv)
{

  std::cout << "input " << argc << " " << *argv[1] << std::endl;

  std::string inputDir;
  if (argc==2) {
    //    inputDir="/mdt/data/run"+*argv[1];
    inputDir="/mdt/data/run9";
  }

  std::cout << "Reading data from dir: " << inputDir << std::endl;

  StreamReader stream(inputDir);
  EventDecoder decoder;
  EventWriter writer("out.root");

  int i=0;
  while (i<100) {
    i++;
    stream.readBlock(10);
    
    std::cout << "Completed events: " << stream.completedEvents() << std::endl;
    
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
