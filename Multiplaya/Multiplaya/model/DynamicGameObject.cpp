#include "DynamicGameObject.h"

namespace mp
{
	DynamicGameObject::DynamicGameObject()
	{
		deletionScheduled = false;
	}

	void DynamicGameObject::scheduleDeletion(Event e)
	{
		if (!deletionScheduled)
		{
			// notify observers that object want to be deleted, put in generic deletionlist
			notifyObservers(e, this);
			deletionScheduled = true; 
		}		
	}
}