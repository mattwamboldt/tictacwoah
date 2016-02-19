#ifndef CORE_TIMER_H
#define CORE_TIMER_H

// A generic timer used to check when a certain amount of time passes
// Used for repeated delayed actions in gameplay
class Timer
{
public:
	Timer(int ticks) : mTicks(ticks), mTicksRemaining(-1) {}

	// Decrements the timer and returns the amount remaining
	int Tick();

	// Resets the timer to the amount set in the constructor 
	int Reset() { mTicksRemaining = mTicks; }

	int Clear() { mTicksRemaining = -1; }

private:
	int mTicks;
	int mTicksRemaining;
};

#endif