#ifndef OBSERVABLE_H
#define OBSERVABLE_H

// Other headers
#include <set>

// Observer interface
#include "Observer.h"

namespace mp 
{
	/**
	 * Observable class.  Holds data supporting the Observer
	 *  pattern.
	 */
	class Observable
	{
		public:
			void addObserver(Observer* observer);
			void removeObserver(Observer* observer);
			void notifyObservers(Event e, void* object);
		protected:
			Observable() {};
			virtual ~Observable() {};
		private:
			std::set<Observer*> observers;
	};
}
#endif // OBSERVABLE_H
