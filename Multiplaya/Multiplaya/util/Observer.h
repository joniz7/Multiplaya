////////////////////////////////////////////////////////////
/// Observer interface. Contains method that will be called
/// from Observable
////////////////////////////////////////////////////////////
#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include "Event.h"

namespace mp
{
	class Observer
	{
		public:
			virtual void notify(Event e, void* object) = 0;
	};
}
#endif // OBSERVER_H
