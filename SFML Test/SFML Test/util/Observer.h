////////////////////////////////////////////////////////////
/// Observer interface. Contains method that will be called
/// from Observable
////////////////////////////////////////////////////////////
#ifndef OBSERVER_H
#define OBSERVER_H

namespace mp
{
	class Observer
	{
		public:
			virtual void notify() = 0;
	};
}
#endif // OBSERVER_H
