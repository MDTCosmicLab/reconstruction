#include "EventBuilder.h"

#include <iostream>

EventBuilder::EventBuilder()
{

}

EventBuilder::~EventBuilder()
{

}

/// get the list of completed events and remove them from the list
void EventBuilder::getEvents(EventMap& emap)
{
  
  for ( std::list<uint32_t>::iterator it = m_listOfFullEvents.begin() ;
	it != m_listOfFullEvents.end() ; ++it) {

    uint32_t evnum = *it;
    EventMap::iterator itmap = m_eventMap.find(evnum);
    if ( itmap == m_eventMap.end() ) {
      std::cout << "ERROR completed event not found ev. number: " << evnum << std::endl;
      return;
    }
      
    emap.insert(make_pair((*itmap).first,(*itmap).second));

    /// now remove the event from the list and from the map
    //    delete (*itmap).second;
    
    //    std::cout << (*itmap).second->size() << std::endl;

    m_eventMap.erase(itmap);

    //    std::cout << (*itmap).second->size() << std::endl;

  }

  m_listOfFullEvents.clear();

  return;
}



/// add a tdc fragment to the event
bool EventBuilder::addTdcFragment(uint32_t evcount, uint32_t tdcId, std::vector<uint32_t>& data)
{

  /// check if the event is already existing in the map
  EventMap::const_iterator it = m_eventMap.find(evcount);
  if ( it != m_eventMap.end() ) {

    Event* event = (*it).second;
    
    /// check if the tdc is already existing in the map
    Event::const_iterator it_tdc = event->find(tdcId);
    if (it_tdc != (event->end())) {
      std::cout << "ERROR: the tdc number " << tdcId << " has already been found for event " << evcount << std::endl;
      return false;
    }
    /// add the tdc data
    else {
      event->insert(make_pair(tdcId,data));
      std::cout << "New tdc inserted, number, size " << tdcId << " " << event->size() << std::endl; 
      // check if the event is completed
      if ( event->size() == 6 ) {
	/// add the event to the list of completed events
	m_listOfFullEvents.push_back(evcount);

	std::cout << "New event added, size: " << m_listOfFullEvents.size() << std::endl; 
      }
    }
    
  }
  /// the event does not exist in the map yet
  else {
    Event* event = new Event();
    event->insert(make_pair(tdcId,data));
    std::cout << "First tdc inserted, size " << event->size() << std::endl; 
    m_eventMap.insert( make_pair(evcount , event ) );
  }
  
  return true;
}
