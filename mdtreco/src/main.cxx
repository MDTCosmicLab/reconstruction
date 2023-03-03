#include <iostream>
#include <vector>
#include <string>

#include "StreamReader.h"
#include "EventDecoder.h"

int main(int argc, char** argv)
{

  StreamReader stream;
  EventDecoder decoder;
  
  stream.readBlock(10);

  std::cout << "Completed events: " << stream.completedEvents() << std::endl;

  /// get the events from the event builder
  EventMap emap;
  stream.getEvents(emap);

  /// loop on the events and decode them
  for ( auto it : emap ) {
    std::cout << "Decoding event number " << it.first << std:: endl;
    decoder.decodeEvent(it.second);
  }
  
  return 0;
}
