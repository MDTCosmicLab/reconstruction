#ifndef STREAMREADER_H
#define STREAMREADER_H

#include <string>
#include <fstream>
#include "MdtAmtReadOut.h"
#include "EventBuilder.h"

#include <vector>


class StreamReader {

 public:

  StreamReader(std::string indir);
  
  ~StreamReader();

  bool readBlock(unsigned int nev);

  unsigned int completedEvents() {return m_eventBuilder.completedEvents();}

  void getEvents(EventMap& eventMap) {return m_eventBuilder.getEvents(eventMap);}
  
 private:

  std::vector<std::string> m_fileNames;
  std::vector<std::ifstream*> m_inputFiles;

  MdtAmtReadOut m_amtReadOut;

  EventBuilder m_eventBuilder;
  
  uint32_t getNextWord(std::ifstream* infile);
  
};


#endif
