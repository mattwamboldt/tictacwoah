#ifndef COMMANDEVENTS_H
#define COMMANDEVENTS_H

#include <app\event\ievent.h>

// These events all represent changes requested by a view

// Requested to fill a grid space with the given player
class SelectEvent : public BaseEvent
{
public:
	SelectEvent(int x, int y, int player) : X(x), Y(y), Player(player) {}
	virtual const EventType& GetType() { return Type; }
	virtual const char* GetName() const { return "SelectEvent"; }

	static EventType Type;
	int X;
	int Y;
	int Player;
};

class RestartEvent : public BaseEvent
{
public:
	virtual const EventType& GetType() { return Type; }
	virtual const char* GetName() const { return "RestartEvent"; }

	static EventType Type;
};

// Events from the board to the world
class BoardClearedEvent : public BaseEvent
{
public:
	virtual const EventType& GetType() { return Type; }
	virtual const char* GetName() const { return "BoardClearedEvent"; }

	static EventType Type;
};

class StateChangeEvent : public BaseEvent
{
public:
	StateChangeEvent(int id, int state) : Id(id), State(state) {}
	virtual const EventType& GetType() { return Type; }
	virtual const char* GetName() const { return "StateChangeEvent"; }

	static EventType Type;
	int Id;
	int State;
};

class GameResultEvent : public BaseEvent
{
public:
	GameResultEvent(int winner, int linestart, int lineend) : Winner(winner), LineStart(linestart), LineEnd(lineend) {}
	virtual const EventType& GetType() { return Type; }
	virtual const char* GetName() const { return "GameResultEvent"; }

	static EventType Type;
	int Winner;
	int LineStart;
	int LineEnd;
};

class InvalidMoveEvent : public BaseEvent
{
public:
	virtual const EventType& GetType() { return Type; }
	virtual const char* GetName() const { return "InvalidMoveEvent"; }

	static EventType Type;
};

#endif
