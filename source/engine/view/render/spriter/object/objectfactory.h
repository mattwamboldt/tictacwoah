#ifndef EXAMPLEOBJECTFACTORY_H
#define EXAMPLEOBJECTFACTORY_H

#include <spriterengine/override/objectfactory.h>

namespace SpriterEngine
{

	class SpriterObjectFactory : public ObjectFactory
	{
	public:
		SpriterObjectFactory();
		
		PointInstanceInfo *newPointInstanceInfo() override;

		BoxInstanceInfo *newBoxInstanceInfo(point size) override;

		BoneInstanceInfo *newBoneInstanceInfo(point size) override;
	};
}

#endif // EXAMPLEOBJECTFACTORY_H
