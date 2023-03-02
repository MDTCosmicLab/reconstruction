#include <iostream>
#include <vector>
#include <string>

#include "StreamReader.h"

int main(int argc, char** argv)
{

  StreamReader stream;
  
  stream.readBlock(10);

  std::cout << "Completed events: " << stream.completedEvents() << std::endl;

  EventMap emap;
  stream.getEvents(emap);

  
  
  return 0;
}
