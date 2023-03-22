#ifndef EVENTBUILDER_H
#define EVENTBUILDER_H

#include <map>
#include <vector>
#include <stdint.h>
#include <list>

typedef std::map< uint32_t, std::vector< uint32_t > > Event;
typedef std::map< uint32_t , Event* > EventMap;

class EventBuilder {

 public:

  EventBuilder();
  ~EventBuilder();

  bool addTdcFragment(uint32_t evcount, uint32_t tdcId, std::vector<uint32_t>& data);

  void getEvents(EventMap& events);

  unsigned int completedEvents() {return m_listOfFullEvents.size();}
  
 private:

  EventMap m_eventMap;

  std::list<uint32_t> m_listOfFullEvents;
  
};


#endif
