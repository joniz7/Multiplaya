////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "Observable.h"

namespace mp 
{
	/**
	 * Adds supplied observer to the set of observers.
	 *
	 * @param observer - Observer to add to our list.
	 */
	void Observable::addObserver(Observer* observer) {
		observers.insert(observer);
	}

	/** 
	 * Removes observer from the set of observers
	 *
	 * @param observer - Observer to remove from our list.
	 */
	void Observable::removeObserver(Observer* observer) {
		observers.erase(observer);
	}

	/**
	 * Calls the notify() method of all our observers.
	 *
	 * @param e - The event that we want to pass along to our observers.
	 * @param object - optional data we want to pass along as well.
	 */
	void Observable::notifyObservers(Event e, void* object) {
		std::set<Observer*>::iterator it;
		// Call notify method for every observer
		for (it = observers.begin(); it != observers.end(); it++) {
			(*it)->notify(e, object);
		}
	}
}