#ifndef SFMLPOINTINSTANCEINFO_H
#define SFMLPOINTINSTANCEINFO_H

#include <spriterengine/objectinfo/pointinstanceinfo.h>

namespace SpriterEngine
{

	class SdlPointInstanceInfo : public PointInstanceInfo
	{
	public:
		SdlPointInstanceInfo();
		void render() override;

	private:
		int size;
	};

}

#endif // SFMLPOINTINSTANCEINFO_H
