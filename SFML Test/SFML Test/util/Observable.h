////////////////////////////////////////////////////////////
/// Observable class.  Holds data supporting the Observer
///  pattern.
////////////////////////////////////////////////////////////
#ifndef OBSERVABLE_H
#define OBSERVABLE_H

// Other headers
#include <set>
#include <string>

// Observer interface
#include "Observer.h"

namespace mp 
{
	class Observable
	{
		public:
			void addObserver(Observer* observer);
			void removeObserver(Observer* observer);
			void notify(std::string e, void* object);
		protected:
			Observable() {};
			virtual ~Observable() {};
		private:
			std::set<Observer*> observers;
	};
}
#endif // OBSERVABLE_H
