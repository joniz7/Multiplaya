#ifndef OBSERVER_H
#define OBSERVER_H

#include "Event.h"

namespace mp
{
	/**
	 * Observer interface. Classes that implement this interface
	 * can register themselves as Observers of other classes,
	 * and recieves events they send to the notify() method.
	 */
	class Observer
	{
		public:
			/// This method will be called when Observable notifies 
			/// its observers
			virtual void notify(Event e, void* object) = 0;
	};
}
#endif // OBSERVER_H
