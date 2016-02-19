// This is an interface to whatever qudio system we want to use, be it fmod, wwise, directsound, whatever
class IAudioSystem
{
public:
	virtual bool Init() = 0;
	virtual bool Destroy() = 0;
};