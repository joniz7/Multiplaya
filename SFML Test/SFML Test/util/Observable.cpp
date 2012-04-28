////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "Observable.h"

////////////////////////////////////////////////////////////
/// Observable class.  Holds data supporting the Observer
//  pattern.
////////////////////////////////////////////////////////////

namespace mp 
{
	////////////////////////////////////////////////////////////
	// Adds observer to the set of observers
	//
	// observer		- Class implementing Observer interface
	////////////////////////////////////////////////////////////
	void Observable::addObserver(Observer* observer) {
		observers.insert(observer);
	}

	////////////////////////////////////////////////////////////
	// Removess observer from the set of observers
	//
	// observer		- Class implementing Observer interface
	////////////////////////////////////////////////////////////
	void Observable::removeObserver(Observer* observer) {
		observers.erase(observer);
	}

	////////////////////////////////////////////////////////////
	// Calls all the observer's notify method
	//
	// observer		- Class implementing Observer interface
	////////////////////////////////////////////////////////////
	void Observable::notify(std::string e, void* object) {
		std::set<Observer*>::iterator it;
		// Call notify method for every observer
		for (it = observers.begin(); it != observers.end(); it++) {
			(*it)->notify(e, object);
		}
	}
}