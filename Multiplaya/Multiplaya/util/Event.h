#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

/**
 * The Event enum, passed from Observable to Observer.
 * Is used in two ways: by controller by the actual game.
 */
enum Event {
	// Controller specific events.
	START_GAME,
	STOP_GAME,
	EXIT_GAME,
	PAUSE_GAME,
	RESUME_GAME,
	SHOW_JOIN,
	SHOW_MAIN_MENU,
	// Game mechanics events
	BULLET_ADDED,
	BULLET_DELETED,
	SEND_BULLET,
	CHARACTER_ADDED,
	CHARACTER_DELETED,
	CHARACTER_DIED,
	CHARACTER_KILLED,
	CONNECT_SERVER
};

#endif