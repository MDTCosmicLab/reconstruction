#include "StreamReader.h"

#include "stdlib.h"
#include <iostream>

StreamReader::StreamReader() 
{
  
  m_fileNames={"/home/srosati/data/tdc1.dat","/home/srosati/data/tdc2.dat","/home/srosati/data/tdc3.dat","/home/srosati/data/tdc4.dat","/home/srosati/data/tdc5.dat","/home/srosati/data/tdc6.dat"};

  // open the readout streams
  for ( int i=0 ; i<6 ; i++ ) {
    std::ifstream* infile = new std::ifstream();
    infile->open(m_fileNames[i]);
    if (!(*infile)) {
      std::cout << "ERROR file " << m_fileNames[i] << " does not exist" << std::endl;
    } else {
      m_inputFiles.push_back(infile);
    }
  }

}

StreamReader::~StreamReader()
{
  
}


bool StreamReader::readBlock(unsigned int nev)
{

  uint32_t dataWord,evcount;
  std::vector<uint32_t> tdcData;
  bool readTdcData;
  uint8_t tdcId;
  
  /// read blocks of nev events from the streams and build the events
  /// loop on the input streams
  for ( uint32_t ifile=0 ; ifile<6 ; ++ifile ) {

    unsigned int nread=0;
    while ( nread<nev ) {

      dataWord = getNextWord(m_inputFiles[ifile]);
      /// look for a TDC header
      m_amtReadOut.decodeWord(dataWord);
      if ( m_amtReadOut.is_BOT() ) {
	tdcData.clear();
	tdcData.push_back(dataWord);
	evcount = m_amtReadOut.ecnt();
	tdcId = m_amtReadOut.tdcId();
	std::cout << ">> file number: " << ifile << " tdc number: " << m_amtReadOut.tdcId() << " bcId: " << m_amtReadOut.bcId() <<
	  " ecnt: " << m_amtReadOut.ecnt() << std::endl;

	/// read all tdc words up to the EOT
	readTdcData=true;
	while ( readTdcData ) {
	  dataWord = getNextWord(m_inputFiles[ifile]);
	  tdcData.push_back(dataWord);
	  m_amtReadOut.decodeWord(dataWord);
	  if (m_amtReadOut.is_EOT()) {
	    readTdcData=false;
	  }
	}
      }
      /// add the fragment to the event builder
      if (tdcData.size()>0) {
	m_eventBuilder.addTdcFragment(evcount,ifile,tdcData);
      }
      nread++;	
    }
    
  }


  return true;
}

uint32_t StreamReader::getNextWord(std::ifstream* infile)
{
  std::string line,word;
  uint32_t dataWord=0;
  std::size_t found = 0;

  std::getline(*infile,line);
  found = line.find("0x"); 
  word = line.substr(found,found+10);
  dataWord = (uint32_t)strtol(word.c_str(),NULL,0);      

  return dataWord;
}


