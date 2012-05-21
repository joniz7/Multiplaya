////////////////////////////////////////////////////////////
/// Observer interface. Contains method that will be called
/// from Observable
////////////////////////////////////////////////////////////
#ifndef OBSERVER_H
#define OBSERVER_H

#include "Event.h"

namespace mp
{
	class Observer
	{
		public:
			/// This method will be called when Observable notifies 
			/// its observers
			virtual void notify(Event e, void* object) = 0;
	};
}
#endif // OBSERVER_H
