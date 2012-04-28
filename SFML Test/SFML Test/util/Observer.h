////////////////////////////////////////////////////////////
/// Observer interface. Contains method that will be called
/// from Observable
////////////////////////////////////////////////////////////
#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

namespace mp
{
	class Observer
	{
		public:
			virtual void notify(std::string e, void* object) = 0;
	};
}
#endif // OBSERVER_H
