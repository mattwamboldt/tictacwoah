#include "objectfactory.h"

#include "sdlpointinstanceinfo.h"
#include "sdlboxinstanceinfo.h"
#include "sdlboneinstanceinfo.h"
#include "sdlsoundobjectinforeference.h"

namespace SpriterEngine
{

	SpriterObjectFactory::SpriterObjectFactory()
	{
	}

	PointInstanceInfo * SpriterObjectFactory::newPointInstanceInfo()
	{
		return new SdlPointInstanceInfo();
	}

	BoxInstanceInfo * SpriterObjectFactory::newBoxInstanceInfo(point size)
	{
		return new SdlBoxInstanceInfo(size);
	}

	BoneInstanceInfo * SpriterObjectFactory::newBoneInstanceInfo(point size)
	{
		return new SdlBoneInstanceInfo(size);
	}

}