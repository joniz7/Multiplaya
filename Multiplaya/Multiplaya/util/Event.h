////////////////////////////////////////////////////////////
/// Event enum passed from Observable to Observer
////////////////////////////////////////////////////////////
#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

enum Event {
	// Controller specific events.
	START_GAME,
	STOP_GAME,
	EXIT_GAME,
	PAUSE_GAME,
	RESUME_GAME,
	SHOW_HOST,
	SHOW_JOIN,
	SHOW_MAIN_MENU,
	SHOW_SETTINGS,
	// Game mechanics events
	BULLET_ADDED,
	BULLET_DELETED,
	CHARACTER_ADDED,
	CHARACTER_DELETED,
	CONNECT_SERVER
};

#endif