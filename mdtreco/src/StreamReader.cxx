#include "StreamReader.h"

#include "stdlib.h"
#include <iostream>

StreamReader::StreamReader(std::string indir) 
{
  
  m_fileNames={indir+"/tdc1.dat",indir+"/tdc2.dat",indir+"/tdc3.dat",
	       indir+"/tdc4.dat",indir+"/tdc5.dat",indir+"/tdc6.dat"};

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
    uint16_t tdcId;
  
    /// read blocks of nev events from the streams and build the events
    /// loop on the input streams
    for ( uint32_t ifile=0 ; ifile<6 ; ++ifile ) {

        unsigned int nread=0;
        while ( nread<nev ) {

            dataWord = getNextWord(m_inputFiles[ifile]);
            if (dataWord==0xffffffff) {
	            return false;
	        }
            /// look for a TDC header
            m_amtReadOut.decodeWord(dataWord);
            //std::cout << "Word: 0x" << std::hex << dataWord << std::dec << std::endl;
            if ( m_amtReadOut.is_BOT() ) {
	            tdcData.clear();
	            tdcData.push_back(dataWord);
	            evcount = m_amtReadOut.ecnt();
	            tdcId = m_amtReadOut.tdcId();
    	            std::cout << ">> found a new BOT file number: " << ifile << " tdc number: " << m_amtReadOut.tdcId() << " bcId: " << m_amtReadOut.bcId() << " ecnt: " << m_amtReadOut.ecnt() << std::endl;

	            /// read all tdc words up to the EOT
	            readTdcData=true;
                //std::cout << "Reading all data words, tdc " << tdcId << " event " << evcount 
                  //  << std::endl;
                bool foundTWC=false;
	            while ( readTdcData ) {
	                dataWord = getNextWord(m_inputFiles[ifile]);
                    //std::cout << "0x" << std::hex << dataWord << std::dec << std::endl;
	                if (dataWord==0xffffffff) {
	                    return false;
	                }
	        
	                m_amtReadOut.decodeWord(dataWord);
                    /// word after the header can be only data or TWC or EOT
                    if (m_amtReadOut.is_TSM()) {
                        tdcData.push_back(dataWord);
                    }
                    else if (m_amtReadOut.is_TWC()) {
                        tdcData.push_back(dataWord);
                        foundTWC=true;
                    }
                    else if (foundTWC && m_amtReadOut.is_EOT()) {
                        // good closure of the TDC data
                        tdcData.push_back(dataWord);
                        readTdcData=false;
                    }
                    /// if the end of tdc is found without TWC, data are not good
	                else if (m_amtReadOut.is_EOT()) {
                            //tdcData.clear();
	                    readTdcData=false;
	                }
                    else {
                        //tdcData.clear();
                        //readTdcData=false;
                    }
                }
            }
            /// add the fragment to the event builder
            //std::cout << "Total fragment size: " << tdcData.size() << std::endl;
            if (tdcData.size()>0) {
	            if (m_eventBuilder.addTdcFragment(evcount,ifile+1,tdcData)) {
                    nread++;
                }
            }	
        }
    
    }

  return true;
}

uint32_t StreamReader::getNextWord(std::ifstream* infile)
{
  std::string line,word;
  uint32_t dataWord=0;
  std::size_t found = 0;

  if(std::getline(*infile,line)) {
    found = line.find("0x"); 
    word = line.substr(found,found+10);
    dataWord = (uint32_t)strtol(word.c_str(),NULL,0);      
  }
  else {
    dataWord=0xffffffff;
  }
  
  return dataWord;
}


